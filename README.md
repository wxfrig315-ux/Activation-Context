# Activation-Context — SxS Activation Context Hijacker

A Windows console tool that hijacks the **Activation Context** of a running
process in order to redirect its future DLL loads to an arbitrary path.

The Activation Context is the runtime object the Windows loader builds from an
application's SxS (Side-by-Side) manifest. It controls how COM classes, window
classes, and — most interestingly — **DLL redirections** (`<file name="..."
loadFrom="..."/>`) are resolved. Every process holds one default context
(`PEB->ActivationContextData`), and every thread keeps a stack of additional
contexts (`TEB->ActivationContextStack`).

`Activation-Context` provides two hijacking modes, selected automatically after
inspecting the target's main thread:

- **process (PEB)** — maps a forged Activation Context into the target and
  overwrites `PEB->ActivationContextData` (offset `0x2F8`, x64), making the
  attacker-controlled manifest the process-wide default context.
- **thread (TEB)** — when the main thread already runs a custom Activation
  Context, the tool forges a frame-list wrapper (`'Flst'` magic) with a valid
  cookie sequence, pushes it onto the victim's activation stack, and patches
  `TEB->ActivationContextStack` (offset `0x290`).

There are no command line arguments, no interactive prompts, and no
configuration files. The target process, the DLL to redirect, and the alias
name are hardcoded in `main.cpp` and configured by editing the source and
rebuilding.

---

## Features

- Extracts the target's embedded manifest (`RT_MANIFEST` resource #1) directly
  from its on-disk image; falls back to a stock `asInvoker` manifest when
  the target has none.
- Injects an SxS DLL-redirection element,
  `<file name="alias.dll" hash="optional" loadFrom="C:\path\real.dll"/>`,
  right before the closing `</assembly>` tag, and saves the resulting manifest
  to `%TEMP%\<pid>.manifest`.
- Builds a genuine Activation Context locally with `CreateActCtxW`, then dumps
  the in-memory `ACTIVATION_CONTEXT_DATA` blob from the resulting handle.
- Detects whether the target's main thread carries a custom Activation Context
  and chooses the PEB or TEB hijacking path accordingly.
- Forges the thread-level frame list (`RtlActivationContextFrame` +
  `FrameListWrapper`, magic `0x74736c46`) and derives a valid 64-bit activation
  cookie from the victim's `NextCookieSequenceNumber` / `StackId`.
- Works entirely through native APIs — `NtOpenProcess`, `NtOpenThread`,
  `NtAllocateVirtualMemory`, `NtReadVirtualMemory`, `NtWriteVirtualMemory`,
  `NtQueryInformationProcess/Thread`, and `RtlAdjustPrivilege`. No
  `CreateRemoteThread`, no shellcode, no injected DLL image.
- Optional `SeDebugPrivilege` (privilege 20) enablement via `RtlAdjustPrivilege`.

---

## Requirements

- **Windows 11 24H2 (x64)** for the offsets hardcoded in the code —
  `PEB + 0x2F8`, `TEB + 0x290`, `TEB + 0x298`. Other builds work only after
  re-verifying/adjusting these offsets.
- A toolchain able to build the bundled `.slnx` solution:
  - **Visual Studio 2026** (MSVC toolset `v145`, `VCProjectVersion 18.0`), or
  - any MSBuild capable of driving the same project.
- Windows SDK 10 (headers, `ntdll.lib` is linked via
  `#pragma comment(lib, "ntdll.lib")`).
- C++20 (`stdcpp20`), Unicode character set, x64 architecture only — the build
  is not portable to x86 because the PEB/TEB offsets are 64-bit-specific.

---

## Build instructions

### Option A — Visual Studio (IDE)

1. Open `Activation-Context.slnx` in Visual Studio 2026.
2. Select the `Release | x64` configuration.
3. Build the solution (**Build > Build Solution**).

The resulting executable is produced in the standard `$(OutDir)` for the
configuration, e.g. `x64\Release\Activation-Context.exe`.

> The project is configured as a **console application** (`Subsystem: Console`,
> C++20, Unicode). Note that the `Debug | x64` configuration is set to
> `DynamicLibrary` (a quirk of the checked-in `.vcxproj`); flip its
> `ConfigurationType` to `Application` if you want a Debug x64 binary.

### Option B — MSBuild (CLI)

```powershell
# From the solution directory
msbuild Activation-Context.slnx /p:Configuration=Release /p:Platform=x64
```

---

## Usage

Configure the target in `main.cpp`, rebuild, and run the binary from an
**elevated** console when `enable_debug` is set:

```cpp
DWORD pid = get_process_id_by_name(L"Loader-dll-example.exe");
sxs_hijack(
    pid,                      // target process (looked up by image name)
    L"C:\\Test\\hijack.dll",  // target_dll  — the real DLL the loader should resolve (loadFrom)
    L"dst_dll.dll",           // dummy_dll   — alias name written into the manifest (file name)
    true);                    // enable_debug — enable SeDebugPrivilege
```

Parameter notes:

- **pid** — resolved by `get_process_id_by_name` from the image name. Make sure
  the target is running *before* launching the tool; a failed lookup returns
  PID `0` and the run will misbehave.
- **target_dll** — absolute path of the DLL the redirected load must land on.
- **dummy_dll** — the alias file name embedded in the manifest. The
  redirection only kicks in when the target requests *this* name and had not
  already loaded it earlier in the process.
- **enable_debug** — when `true`, `RtlAdjustPrivilege` enables
  `SeDebugPrivilege`; required to open processes outside your session.

Example run (`Release | x64`), against a target whose main thread carries a
custom Activation Context:

```text
[+] Temporary file written to: C:\Users\me\AppData\Local\Temp\4212.manifest
[+] SeDebugPrivilege enabled.
[+] Manifest file path exist.
[+] Local Activation Context created.
[-] Looking for the remote process main thread...
[+] Main thread detected. TID: 5892
        [-] Handle to main thread opened.
[!] Main thread has a custom AC enabled. Hijacking thread's AC stack.
[+] Memory successfully allocated.
[+] AC data successfully written in the remote process.
[+] TEB->ACTIVATION_CONTEXT_STACK patched. Process completed.
```

Same tool, target without a custom context (PEB path):

```text
[!] Main thread does not have a custom AC enabled.Hijacking main AC of the process.
[+] Remote process PEB base address obtained.
[+] Memory successfully allocated.
[+] Activation Context mapped in the remote process.
[+] PEB successfully patched.
```

After the patch, any **subsequent** DLL resolution in the target that matches
the alias is served from `loadFrom`. Modules already loaded keep their original
resolution.

---

## Technical notes

| Offset (x64) | Meaning |
|---|---|
| `PEB + 0x2F8` | `PEB->ActivationContextData` — process-wide default context |
| `TEB + 0x290` | `TEB->ActivationContextStack` (`ACTIVATION_CONTEXT_STACK`) |
| `TEB + 0x298` | `FrameListCache` `Flink/Blink` target of the forged wrapper |

- The local `CreateActCtxW` handle is walked (`handle + 3 pointers`) to the
  in-memory context data; its region is measured with `VirtualQuery`, copied
  out, and page-aligned so the frame-list block can be appended behind it.
- The thread-level payload appends a `FrameListWrapper`: magic `'Flst'`
  (`0x74736c46`), `num_elements = 1`,
  `not_num_elements = 0xFFFFFFFE00000000`, one activation frame with
  `flags = 0x28`, plus the 528-byte Activation Context handle data snapshot
  whose internal pointers are rewritten to the remote allocation.
- The forged activation cookie is derived from the victim TEB:
  `NextCookieSequenceNumber | ((StackId & 0x0FFFFFFF) << 32) | 0x1000000000000000`,
  and `NextCookieSequenceNumber` is bumped by one in the patched stack.
- `TEB_INTERNAL` / SxS structure definitions come from
  **System Informer (PHNT)** (`ntpebteb.h`, `ntsxs.h`) and carry matching
  `static_assert` layout checks (e.g. `sizeof(TEB_INTERNAL) == 0x1878` on
  24H2 x64).

---

## Permissions and safety notes

- **Elevation.** Opening another user's process and writing its address space
  requires `SeDebugPrivilege`; run the tool as **Administrator** and keep
  `enable_debug = true` in that scenario.
- **State requirements.** The redirection only applies to loads that happen
  after the patch; DLLs the target has already resolved are untouched.
- **Residue.** The tampered manifest stays behind at `%TEMP%\<pid>.manifest`
  until cleaned up manually. The tool does not touch the target's on-disk
  image.
- **Layout fragility.** Offsets and structure sizes are pinned to the Win11
  24H2 x64 layout by `static_assert`s; mismatches fail the build rather than
  silently corrupting a target.
- **Responsible use only.** Hijacking another process's Activation Context is
  code-injection adjacent behavior. Use it exclusively against systems you own
  or are explicitly authorized to test (your own lab, red-team engagement with
  written authorization, etc.).

---

## Project layout

- `main.cpp` — entry point; hardcoded target configuration (`pid`, DLL paths,
  `enable_debug`).
- `activation-context.cpp` / `activation-context.h` — the two core routines,
  `sxs_hijack()` (orchestrates manifest tampering, local Activation Context
  creation, TEB inspection, payload writing) and `hijack_process()` (PEB-mode
  allocation and patching); also `FrameListWrapper`,
  `RtlActivationContextFrame`, and the fallback `asInvoker` manifest bytes.
- `utils.cpp` / `utils.h` — helpers: `get_process_id_by_name`,
  `get_process_path`, `get_main_thread_id` (Toolhelp32 snapshots),
  `extract_manifest` (RT_MANIFEST resource), `add_hijack_actctx` (manifest
  redirection injection), `save_data_to_file`, `align_to_mempage`.
- `ntsxs.h` — SxS structures (`ACTIVATION_CONTEXT_DATA`,
  `ACTIVATION_CONTEXT`, `ACTIVATION_CONTEXT_STACK`,
  `RTL_ACTIVATION_CONTEXT_STACK_FRAME`), from System Informer.
- `ntpebteb.h` — `TEB_INTERNAL` and PEB layout definitions with
  `static_assert` offsets, from System Informer.
- `Activation-Context.slnx`, `Activation-Context.vcxproj` — Visual Studio
  solution and project (x86/x64, C++20, Unicode).
