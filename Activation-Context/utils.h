#pragma once
#include<Windows.h>
#include<string>
#include<iostream>
#include<vector>
#include <TlHelp32.h>
#include <map>
#include<sstream>
#include<fstream>

DWORD get_main_thread_id(DWORD pid);
DWORD align_to_mempage(DWORD size);
DWORD get_process_id_by_name(const std::wstring& processName);
std::wstring get_process_path(DWORD pid);
std::vector<BYTE> extract_manifest(std::wstring file_path);
std::vector<BYTE> add_hijack_actctx(std::wstring dummy_dll_name, std::wstring target_dll_load, std::vector<BYTE> manifest);
BOOL save_data_to_file(std::vector<BYTE> manifest, std::wstring file_path);
