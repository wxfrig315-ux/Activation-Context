#pragma once
/*
 * Process and Thread Environment Block support functions
 *
 * This file is part of System Informer.
 */

#ifndef _NTPEBTEB_H
#define _NTPEBTEB_H

//#include <ntsxs.h>
#include "ntsxs.h"

#ifdef ACTCTX_COMPATIBILITY_ELEMENT_TYPE
#undef ACTCTX_COMPATIBILITY_ELEMENT_TYPE
#endif
typedef struct _RTL_USER_PROCESS_PARAMETERS* PRTL_USER_PROCESS_PARAMETERS;
typedef struct _RTL_CRITICAL_SECTION* PRTL_CRITICAL_SECTION;
typedef struct _SILO_USER_SHARED_DATA* PSILO_USER_SHARED_DATA;
typedef struct _LEAP_SECOND_DATA* PLEAP_SECOND_DATA;
typedef struct _PEB_LDR_DATA PEB_LDR_DATA, * PPEB_LDR_DATA;

// PEB->AppCompatFlags
#define KACF_OLDGETSHORTPATHNAME 0x00000001
#define KACF_VERSIONLIE_NOT_USED 0x00000002
#define KACF_GETTEMPPATH_NOT_USED 0x00000004
#define KACF_GETDISKFREESPACE 0x00000008
#define KACF_FTMFROMCURRENTAPT 0x00000020
#define KACF_DISALLOWORBINDINGCHANGES 0x00000040
#define KACF_OLE32VALIDATEPTRS 0x00000080
#define KACF_DISABLECICERO 0x00000100
#define KACF_OLE32ENABLEASYNCDOCFILE 0x00000200
#define KACF_OLE32ENABLELEGACYEXCEPTIONHANDLING 0x00000400
#define KACF_RPCDISABLENDRCLIENTHARDENING 0x00000800
#define KACF_RPCDISABLENDRMAYBENULL_SIZEIS 0x00001000
#define KACF_DISABLEALLDDEHACK_NOT_USED 0x00002000
#define KACF_RPCDISABLENDR61_RANGE 0x00004000
#define KACF_RPC32ENABLELEGACYEXCEPTIONHANDLING 0x00008000
#define KACF_OLE32DOCFILEUSELEGACYNTFSFLAGS 0x00010000
#define KACF_RPCDISABLENDRCONSTIIDCHECK 0x00020000
#define KACF_USERDISABLEFORWARDERPATCH 0x00040000
#define KACF_OLE32DISABLENEW_WMPAINT_DISPATCH 0x00100000
#define KACF_ADDRESTRICTEDSIDINCOINITIALIZESECURITY 0x00200000
#define KACF_ALLOCDEBUGINFOFORCRITSECTIONS 0x00400000
#define KACF_OLEAUT32ENABLEUNSAFELOADTYPELIBRELATIVE 0x00800000
#define KACF_ALLOWMAXIMIZEDWINDOWGAMMA 0x01000000
#define KACF_DONOTADDTOCACHE 0x80000000

// PEB->ApiSetMap
typedef struct _API_SET_NAMESPACE
{
    ULONG Version;
    ULONG Size;
    ULONG Flags;
    ULONG Count;
    ULONG EntryOffset;
    ULONG HashOffset;
    ULONG HashFactor;
} API_SET_NAMESPACE, * PAPI_SET_NAMESPACE;

// private
typedef struct _API_SET_HASH_ENTRY
{
    ULONG Hash;
    ULONG Index;
} API_SET_HASH_ENTRY, * PAPI_SET_HASH_ENTRY;

// private
typedef struct _API_SET_NAMESPACE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset;
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY, * PAPI_SET_NAMESPACE_ENTRY;

// private
typedef struct _API_SET_VALUE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY, * PAPI_SET_VALUE_ENTRY;

// PEB->TelemetryCoverageHeader
typedef struct _TELEMETRY_COVERAGE_HEADER
{
    UCHAR MajorVersion;
    UCHAR MinorVersion;
    struct
    {
        USHORT TracingEnabled : 1;
        USHORT Reserved1 : 15;
    };
    ULONG HashTableEntries;
    ULONG HashIndexMask;
    ULONG TableUpdateVersion;
    ULONG TableSizeInBytes;
    ULONG LastResetTick;
    ULONG ResetRound;
    ULONG Reserved2;
    ULONG RecordedCount;
    ULONG Reserved3[4];
    ULONG HashTable[ANYSIZE_ARRAY];
} TELEMETRY_COVERAGE_HEADER, * PTELEMETRY_COVERAGE_HEADER;

typedef struct _WER_RECOVERY_INFO
{
    ULONG Length;
    PVOID Callback;
    PVOID Parameter;
    HANDLE Started;
    HANDLE Finished;
    HANDLE InProgress;
    LONG LastError;
    BOOL Successful;
    ULONG PingInterval;
    ULONG Flags;
} WER_RECOVERY_INFO, * PWER_RECOVERY_INFO;

typedef struct _WER_FILE
{
    USHORT Flags;
    WCHAR Path[MAX_PATH];
} WER_FILE, * PWER_FILE;

typedef struct _WER_MEMORY
{
    PVOID Address;
    ULONG Size;
} WER_MEMORY, * PWER_MEMORY;

typedef struct _WER_GATHER
{
    PVOID Next;
    USHORT Flags;
    union
    {
        WER_FILE File;
        WER_MEMORY Memory;
    } v;
} WER_GATHER, * PWER_GATHER;

typedef struct _WER_METADATA
{
    PVOID Next;
    WCHAR Key[64];
    WCHAR Value[128];
} WER_METADATA, * PWER_METADATA;

typedef struct _WER_RUNTIME_DLL
{
    PVOID Next;
    ULONG Length;
    PVOID Context;
    WCHAR CallbackDllPath[MAX_PATH];
} WER_RUNTIME_DLL, * PWER_RUNTIME_DLL;

typedef struct _WER_DUMP_COLLECTION
{
    PVOID Next;
    ULONG ProcessId;
    ULONG ThreadId;
} WER_DUMP_COLLECTION, * PWER_DUMP_COLLECTION;

typedef struct _WER_HEAP_MAIN_HEADER
{
    WCHAR Signature[16];
    LIST_ENTRY Links;
    HANDLE Mutex;
    PVOID FreeHeap;
    ULONG FreeCount;
} WER_HEAP_MAIN_HEADER, * PWER_HEAP_MAIN_HEADER;

#ifndef RESTART_MAX_CMD_LINE
#define RESTART_MAX_CMD_LINE 1024
#endif

typedef struct _WER_PEB_HEADER_BLOCK
{
    LONG Length;
    WCHAR Signature[16];
    WCHAR AppDataRelativePath[64];
    WCHAR RestartCommandLine[RESTART_MAX_CMD_LINE];
    WER_RECOVERY_INFO RecoveryInfo;
    PWER_GATHER Gather;
    PWER_METADATA MetaData;
    PWER_RUNTIME_DLL RuntimeDll;
    PWER_DUMP_COLLECTION DumpCollection;
    LONG GatherCount;
    LONG MetaDataCount;
    LONG DumpCount;
    LONG Flags;
    WER_HEAP_MAIN_HEADER MainHeader;
    PVOID Reserved;
} WER_PEB_HEADER_BLOCK, * PWER_PEB_HEADER_BLOCK;

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

typedef _Function_class_(PS_POST_PROCESS_INIT_ROUTINE)
VOID NTAPI PS_POST_PROCESS_INIT_ROUTINE(
    VOID
);
typedef PS_POST_PROCESS_INIT_ROUTINE* PPS_POST_PROCESS_INIT_ROUTINE;

#ifndef FLS_MAXIMUM_AVAILABLE
#define FLS_MAXIMUM_AVAILABLE 128
#endif
#ifndef TLS_MINIMUM_AVAILABLE
#define TLS_MINIMUM_AVAILABLE 64
#endif
#ifndef TLS_EXPANSION_SLOTS
#define TLS_EXPANSION_SLOTS 1024
#endif

/**
 * Process Environment Block (PEB) structure.
 *
 * @remarks https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb
 */

#ifdef _WIN64
static_assert(FIELD_OFFSET(PEB, SessionId) == 0x2C0, "FIELD_OFFSET(PEB, SessionId) is incorrect");
//static_assert(sizeof(PEB) == 0x7B0, "Size of PEB is incorrect"); // REDSTONE3
//static_assert(sizeof(PEB) == 0x7B8, "Size of PEB is incorrect"); // REDSTONE4
//static_assert(sizeof(PEB) == 0x7C8, "Size of PEB is incorrect"); // REDSTONE5 // 19H1
#else
static_assert(FIELD_OFFSET(PEB, SessionId) == 0x1D4, "FIELD_OFFSET(PEB, SessionId) is incorrect");
//static_assert(sizeof(PEB) == 0x468, "Size of PEB is incorrect"); // REDSTONE3
//static_assert(sizeof(PEB) == 0x470, "Size of PEB is incorrect"); // REDSTONE4
//static_assert(sizeof(PEB) == 0x480, "Size of PEB is incorrect"); // REDSTONE5 // 19H1
static_assert(sizeof(PEB) == 0x488, "Size of PEB is incorrect"); // WIN11
#endif

#define GDI_BATCH_BUFFER_SIZE 310

/**
 * The GDI_TEB_BATCH structure is used to store information about GDI batch operations.
 */
typedef struct _GDI_TEB_BATCH
{
    ULONG Offset;
    ULONG_PTR HDC;
    ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
} GDI_TEB_BATCH, * PGDI_TEB_BATCH;

#define TEB_ACTIVE_FRAME_CONTEXT_FLAG_EXTENDED (0x00000001)

/**
 * The TEB_ACTIVE_FRAME_CONTEXT structure is used to store information about an active frame context.
 */
typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
    ULONG Flags;
    PCSTR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, * PTEB_ACTIVE_FRAME_CONTEXT;

/**
 * The TEB_ACTIVE_FRAME_CONTEXT_EX structure extends TEB_ACTIVE_FRAME_CONTEXT with additional information.
 */
typedef struct _TEB_ACTIVE_FRAME_CONTEXT_EX
{
    TEB_ACTIVE_FRAME_CONTEXT BasicContext;
    PCSTR SourceLocation;
} TEB_ACTIVE_FRAME_CONTEXT_EX, * PTEB_ACTIVE_FRAME_CONTEXT_EX;

#define TEB_ACTIVE_FRAME_FLAG_EXTENDED (0x00000001)

/**
 * The TEB_ACTIVE_FRAME structure is used to store information about an active frame.
 */
typedef struct _TEB_ACTIVE_FRAME
{
    ULONG Flags;
    struct _TEB_ACTIVE_FRAME* Previous;
    PTEB_ACTIVE_FRAME_CONTEXT Context;
} TEB_ACTIVE_FRAME, * PTEB_ACTIVE_FRAME;

/**
 * The TEB_ACTIVE_FRAME_EX structure extends TEB_ACTIVE_FRAME with additional information.
 */
typedef struct _TEB_ACTIVE_FRAME_EX
{
    TEB_ACTIVE_FRAME BasicFrame;
    PVOID ExtensionIdentifier;
} TEB_ACTIVE_FRAME_EX, * PTEB_ACTIVE_FRAME_EX;

#define STATIC_UNICODE_BUFFER_LENGTH 261
#define WIN32_CLIENT_INFO_LENGTH 62

// private
typedef enum tagOLETLSFLAGS
{
    OLETLS_LOCALTID = 0x01, // This TID is in the current process.
    OLETLS_UUIDINITIALIZED = 0x02, // This Logical thread is init'd.
    OLETLS_INTHREADDETACH = 0x04, // This is in thread detach.
    OLETLS_CHANNELTHREADINITIALZED = 0x08,// This channel has been init'd
    OLETLS_WOWTHREAD = 0x10, // This thread is a 16-bit WOW thread.
    OLETLS_THREADUNINITIALIZING = 0x20, // This thread is in CoUninitialize.
    OLETLS_DISABLE_OLE1DDE = 0x40, // This thread can't use a DDE window.
    OLETLS_APARTMENTTHREADED = 0x80, // This is an STA apartment thread
    OLETLS_MULTITHREADED = 0x100, // This is an MTA apartment thread
    OLETLS_IMPERSONATING = 0x200, // This thread is impersonating
    OLETLS_DISABLE_EVENTLOGGER = 0x400, // Prevent recursion in event logger
    OLETLS_INNEUTRALAPT = 0x800, // This thread is in the NTA
    OLETLS_DISPATCHTHREAD = 0x1000, // This is a dispatch thread
    OLETLS_HOSTTHREAD = 0x2000, // This is a host thread
    OLETLS_ALLOWCOINIT = 0x4000, // This thread allows inits
    OLETLS_PENDINGUNINIT = 0x8000, // This thread has pending uninit
    OLETLS_FIRSTMTAINIT = 0x10000,// First thread to attempt an MTA init
    OLETLS_FIRSTNTAINIT = 0x20000,// First thread to attempt an NTA init
    OLETLS_APTINITIALIZING = 0x40000, // Apartment Object is initializing
    OLETLS_UIMSGSINMODALLOOP = 0x80000,
    OLETLS_MARSHALING_ERROR_OBJECT = 0x100000, // since WIN8
    OLETLS_WINRT_INITIALIZE = 0x200000, // This thread called RoInitialize
    OLETLS_APPLICATION_STA = 0x400000,
    OLETLS_IN_SHUTDOWN_CALLBACKS = 0x800000,
    OLETLS_POINTER_INPUT_BLOCKED = 0x1000000,
    OLETLS_IN_ACTIVATION_FILTER = 0x2000000, // since WINBLUE
    OLETLS_ASTATOASTAEXEMPT_QUIRK = 0x4000000,
    OLETLS_ASTATOASTAEXEMPT_PROXY = 0x8000000,
    OLETLS_ASTATOASTAEXEMPT_INDOUBT = 0x10000000,
    OLETLS_DETECTED_USER_INITIALIZED = 0x20000000, // since RS3
    OLETLS_BRIDGE_STA = 0x40000000, // since RS5
    OLETLS_NAINITIALIZING = 0x80000000UL // since 19H1
} OLETLSFLAGS, * POLETLSFLAGS;

// private
typedef struct tagSOleTlsData
{
    PVOID ThreadBase;
    PVOID SmAllocator;
    ULONG ApartmentID;
    OLETLSFLAGS Flags;
    LONG TlsMapIndex;
    PVOID* TlsSlot;
    ULONG ComInits;
    ULONG OleInits;
    ULONG Calls;
    PVOID ServerCall; // previously CallInfo (before TH1)
    PVOID CallObjectCache; // previously FreeAsyncCall (before TH1)
    PVOID ContextStack; // previously FreeClientCall (before TH1)
    PVOID ObjServer;
    ULONG TIDCaller;
    // ... (other fields are version-dependant)
} SOleTlsData, * PSOleTlsData;

/**
 * Thread Environment Block (TEB) structure.
 *
 * @remarks https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-teb
 */


typedef struct _TEB_INTERNAL
{
    //
    // Thread Information Block (TIB) contains the thread's stack, base and limit addresses, the current stack pointer, and the exception list.
    //
    NT_TIB NtTib;

    //
    // Reserved.
    //
    PVOID EnvironmentPointer;

    //
    // Client ID for this thread.
    //
    CLIENT_ID ClientId;

    //
    // A handle to an active Remote Procedure Call (RPC) if the thread is currently involved in an RPC operation.
    //
    PVOID ActiveRpcHandle;

    //
    // A pointer to the __declspec(thread) local storage array.
    //
    PVOID ThreadLocalStoragePointer;

    //
    // A pointer to the Process Environment Block (PEB), which contains information about the process.
    //
    PPEB ProcessEnvironmentBlock;

    //
    // The previous Win32 error value for this thread.
    //
    ULONG LastErrorValue;

    //
    // The number of critical sections currently owned by this thread.
    //
    ULONG CountOfOwnedCriticalSections;

    //
    // Reserved.
    //
    PVOID CsrClientThread;

    //
    // Reserved.
    //
    PVOID Win32ThreadInfo;

    //
    // Reserved.
    //
    ULONG User32Reserved[26];

    //
    // Reserved.
    //
    ULONG UserReserved[5];

    //
    // Reserved.
    //
    PVOID WOW32Reserved;

    //
    // The LCID of the current thread. (Kernel32!GetThreadLocale)
    //
    LCID CurrentLocale;

    //
    // Reserved.
    //
    ULONG FpSoftwareStatusRegister;

    //
    // Reserved.
    //
    PVOID ReservedForDebuggerInstrumentation[16];

#ifdef _WIN64
    //
    // Reserved.
    //
    PVOID SystemReserved1[25];

    //
    // Per-thread fiber local storage. (Teb->HasFiberData)
    //
    PVOID HeapFlsData;

    //
    // Reserved.
    //
    ULONG_PTR RngState[4];
#else
    //
    // Reserved.
    //
    PVOID SystemReserved1[26];
#endif

    //
    // Placeholder compatibility mode. (ProjFs and Cloud Files)
    //
    CHAR PlaceholderCompatibilityMode;

    //
    // Indicates whether placeholder hydration is always explicit.
    //
    BOOLEAN PlaceholderHydrationAlwaysExplicit;

    //
    // Reserved.
    //
    CHAR PlaceholderReserved[10];

    //
    // The process ID (PID) that the current COM server thread is acting on behalf of.
    //
    ULONG ProxiedProcessId;

    //
    // Pointer to the activation context stack for the current thread.
    //
    ACTIVATION_CONTEXT_STACK ActivationStack;

    //
    // Opaque operation on behalf of another user or process.
    //
    UCHAR WorkingOnBehalfTicket[8];

    //
    // The last exception status for the current thread.
    //
    NTSTATUS ExceptionCode;

    //
    // Pointer to the activation context stack for the current thread.
    //
    PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;

    //
    // The stack pointer (SP) of the current system call or exception during instrumentation.
    //
    ULONG_PTR InstrumentationCallbackSp;

    //
    // The program counter (PC) of the previous system call or exception during instrumentation.
    //
    ULONG_PTR InstrumentationCallbackPreviousPc;

    //
    // The stack pointer (SP) of the previous system call or exception during instrumentation.
    //
    ULONG_PTR InstrumentationCallbackPreviousSp;

#ifdef _WIN64
    //
    // The miniversion ID of the current transacted file operation.
    //
    ULONG TxFsContext;
#endif

    //
    // Indicates the state of the system call or exception instrumentation callback.
    //
    BOOLEAN InstrumentationCallbackDisabled;

#ifdef _WIN64
    //
    // Indicates the state of alignment exceptions for unaligned load/store operations.
    //
    BOOLEAN UnalignedLoadStoreExceptions;
#endif

#ifndef _WIN64
    //
    // SpareBytes.
    //
    UCHAR SpareBytes[23];

    //
    // The miniversion ID of the current transacted file operation.
    //
    ULONG TxFsContext;
#endif

    //
    // Reserved for GDI.
    //
    GDI_TEB_BATCH GdiTebBatch;
    CLIENT_ID RealClientId;
    HANDLE GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID GdiThreadLocalInfo;

    //
    // Reserved for User32.
    //
    ULONG_PTR Win32ClientInfo[WIN32_CLIENT_INFO_LENGTH];

    //
    // Reserved for opengl32.dll
    //
    PVOID glDispatchTable[233];
    ULONG_PTR glReserved1[29];
    PVOID glReserved2;
    PVOID glSectionInfo;
    PVOID glSection;
    PVOID glTable;
    PVOID glCurrentRC;
    PVOID glContext;

    //
    // The previous status value for this thread.
    //
    NTSTATUS LastStatusValue;

    //
    // A static string for use by the application.
    //
    UNICODE_STRING StaticUnicodeString;

    //
    // A static buffer for use by the application.
    //
    WCHAR StaticUnicodeBuffer[STATIC_UNICODE_BUFFER_LENGTH];

    //
    // The maximum stack size and indicates the base of the stack.
    //
    PVOID DeallocationStack;

    //
    // Data for Thread Local Storage. (TlsGetValue)
    //
    PVOID TlsSlots[TLS_MINIMUM_AVAILABLE];

    //
    // Reserved.
    //
    LIST_ENTRY TlsLinks;

    //
    // Reserved for NTVDM.
    //
    PVOID Vdm;

    //
    // Reserved.
    //
    PVOID ReservedForNtRpc;

    //
    // Reserved.
    //
    PVOID DbgSsReserved[2];

    //
    // The error mode for the current thread. (GetThreadErrorMode)
    //
    ULONG HardErrorMode;

    //
    // Reserved.
    //
#ifdef _WIN64
    PVOID Instrumentation[11];
#else
    PVOID Instrumentation[9];
#endif

    //
    // Reserved.
    //
    GUID ActivityId;

    //
    // The service creating the thread (svchost).
    //
    PVOID SubProcessTag;

    //
    // Reserved.
    //
    PVOID PerflibData;

    //
    // Reserved.
    //
    PVOID EtwTraceData;

    //
    // The address of a socket handle during a blocking socket operation. (WSAStartup)
    //
    HANDLE WinSockData;

    //
    // The number of function calls accumulated in the current GDI batch. (GdiSetBatchLimit)
    //
    ULONG GdiBatchCount;

    //
    // The preferred processor for the current thread. (SetThreadIdealProcessor/SetThreadIdealProcessorEx)
    //
    union
    {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        ULONG IdealProcessorValue;
        struct
        {
            UCHAR ReservedPad0;
            UCHAR ReservedPad1;
            UCHAR ReservedPad2;
            UCHAR IdealProcessor;
        };
    };

    //
    // The minimum size of the stack available during any stack overflow exceptions. (SetThreadStackGuarantee)
    //
    ULONG GuaranteedStackBytes;

    //
    // Reserved.
    //
    PVOID ReservedForPerf;

    //
    // Per-thread COM/OLE state
    //
    PSOleTlsData ReservedForOle;

    ULONG WaitingOnLoaderLock;
    PVOID SavedPriorityState;
    ULONG_PTR ReservedForCodeCoverage;
    PVOID ThreadPoolData;
    PVOID* TlsExpansionSlots;
#ifdef _WIN64
    PVOID ChpeV2CpuAreaInfo; // CHPEV2_CPUAREA_INFO // previously DeallocationBStore
    PVOID Unused; // previously BStoreLimit
#endif
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    PVOID NlsCache;
    PVOID pShimData;
    ULONG HeapData;
    HANDLE CurrentTransactionHandle;
    PTEB_ACTIVE_FRAME ActiveFrame;

    //
    // Reserved for FLS (RtlProcessFlsData).
    //
    PVOID FlsData;

    PVOID PreferredLanguages;
    PVOID UserPrefLanguages;
    PVOID MergedPrefLanguages;
    ULONG MuiImpersonation;

    union
    {
        USHORT CrossTebFlags;
        USHORT SpareCrossTebBits : 16;
    };
    union
    {
        USHORT SameTebFlags;
        struct
        {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SkipFileAPIBrokering : 1;
        };
    };

    PVOID TxnScopeEnterCallback;
    PVOID TxnScopeExitCallback;
    PVOID TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    PVOID ResourceRetValue;
    PVOID ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
    ULONGLONG LastSleepCounter; // Win11
    ULONG SpinCallCount;
    ULONGLONG ExtendedFeatureDisableMask;
    PVOID SchedulerSharedDataSlot; // 24H2
    PVOID HeapWalkContext;
    GROUP_AFFINITY PrimaryGroupAffinity;
    ULONG Rcu[2];
} TEB_INTERNAL, * PTEB_INTERNAL;

#ifdef _WIN64
//static_assert(sizeof(TEB) == 0x1850, "Size of TEB is incorrect"); // WIN11
static_assert(sizeof(TEB_INTERNAL)  == 0x1878, "Size of TEB is incorrect"); // 24H2
#else
//static_assert(sizeof(TEB) == 0x1018, "Size of TEB is incorrect"); // WIN11
static_assert(sizeof(TEB) == 0x1038, "Size of TEB is incorrect"); // 24H2
#endif

#endif