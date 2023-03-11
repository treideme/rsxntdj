#ifndef _LMBROWSR_H
#define _LMBROWSR_H
#ifdef __cplusplus
extern "C" {
#endif
#define BROWSER_ROLE_PDC 1
#define BROWSER_ROLE_BDC 2
typedef struct _BROWSER_STATISTICS {
	LARGE_INTEGER StatisticsStartTime;
	LARGE_INTEGER NumberOfServerAnnouncements;
	LARGE_INTEGER NumberOfDomainAnnouncements;
	ULONG NumberOfElectionPackets;
	ULONG NumberOfMailslotWrites;
	ULONG NumberOfGetBrowserServerListRequests;
	ULONG NumberOfServerEnumerations;
	ULONG NumberOfDomainEnumerations;
	ULONG NumberOfOtherEnumerations;
	ULONG NumberOfMissedServerAnnouncements;
	ULONG NumberOfMissedMailslotDatagrams;
	ULONG NumberOfMissedGetBrowserServerListRequests;
	ULONG NumberOfFailedServerAnnounceAllocations;
	ULONG NumberOfFailedMailslotAllocations;
	ULONG NumberOfFailedMailslotReceives;
	ULONG NumberOfFailedMailslotWrites;
	ULONG NumberOfFailedMailslotOpens;
	ULONG NumberOfDuplicateMasterAnnouncements;
LARGE_INTEGER NumberOfIllegalDatagrams;
} BROWSER_STATISTICS,*PBROWSER_STATISTICS,*LPBROWSER_STATISTICS;
typedef struct _BROWSER_STATISTICS_100 {
	LARGE_INTEGER StartTime;
	LARGE_INTEGER NumberOfServerAnnouncements;
	LARGE_INTEGER NumberOfDomainAnnouncements;
	ULONG NumberOfElectionPackets;
	ULONG NumberOfMailslotWrites;
	ULONG NumberOfGetBrowserServerListRequests;
	LARGE_INTEGER NumberOfIllegalDatagrams;
} BROWSER_STATISTICS_100,*PBROWSER_STATISTICS_100;
typedef struct _BROWSER_STATISTICS_101 {
	LARGE_INTEGER StartTime;
	LARGE_INTEGER NumberOfServerAnnouncements;
	LARGE_INTEGER NumberOfDomainAnnouncements;
	ULONG NumberOfElectionPackets;
	ULONG NumberOfMailslotWrites;
	ULONG NumberOfGetBrowserServerListRequests;
	LARGE_INTEGER NumberOfIllegalDatagrams;
	ULONG NumberOfMissedServerAnnouncements;
	ULONG NumberOfMissedMailslotDatagrams;
	ULONG NumberOfMissedGetBrowserServerListRequests;
	ULONG NumberOfFailedServerAnnounceAllocations;
	ULONG NumberOfFailedMailslotAllocations;
	ULONG NumberOfFailedMailslotReceives;
	ULONG NumberOfFailedMailslotWrites;
	ULONG NumberOfFailedMailslotOpens;
	ULONG NumberOfDuplicateMasterAnnouncements;
} BROWSER_STATISTICS_101,*PBROWSER_STATISTICS_101;

NET_API_STATUS WINAPI I_BrowserServerEnum(LPTSTR,LPTSTR,LPTSTR,DWORD,PBYTE*,DWORD,PDWORD,PDWORD,DWORD,LPTSTR,PDWORD);
NET_API_STATUS I_BrowserQueryOtherDomains(LPTSTR,PBYTE*,PDWORD,PDWORD);
NET_API_STATUS I_BrowserResetNetlogonState(LPTSTR);
NET_API_STATUS I_BrowserSetNetlogonState(LPWSTR,LPWSTR,LPWSTR,DWORD);
NET_API_STATUS I_BrowserQueryStatistics(LPTSTR,LPBROWSER_STATISTICS*);
NET_API_STATUS I_BrowserResetStatistics(LPTSTR);
WORD I_BrowserServerEnumForXactsrv(LPTSTR,LPTSTR,ULONG,USHORT,PVOID,WORD,DWORD,PDWORD,PDWORD,DWORD,LPTSTR,PWORD);
NET_API_STATUS I_BrowserDebugTrace(PWCHAR,PCHAR);
#ifdef __cplusplus
}
#endif
#endif 
