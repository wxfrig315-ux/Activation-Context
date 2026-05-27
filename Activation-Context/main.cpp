#include "activation-context.h"


//void sxs_hijack(DWORD pid, std::wstring target_dll, std::wstring dummy_dll, bool enable_debug)
int main()
{
	DWORD pid = get_process_id_by_name(L"Loader-dll-example.exe");
	sxs_hijack(pid, L"C:\\Test\\hijack.dll",
		L"dst_dll.dll",
	
		true);
	return 0;
}