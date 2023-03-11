#ifndef _LMCONFIG_H
#define _LMCONFIG_H
#ifdef __cplusplus
extern "C" {
#endif
#define REVISED_CONFIG_APIS
typedef struct _CONFIG_INFO_0 {
	LPTSTR cfgi0_key;
	LPTSTR cfgi0_data;
} CONFIG_INFO_0,*PCONFIG_INFO_0,*LPCONFIG_INFO_0;
NET_API_STATUS WINAPI NetConfigGet(LPTSTR,LPTSTR,LPTSTR,PBYTE*);
NET_API_STATUS WINAPI NetConfigGetAll(LPTSTR,LPTSTR,PBYTE*);
NET_API_STATUS WINAPI NetConfigSet(LPTSTR,LPTSTR,LPTSTR,DWORD,DWORD,PBYTE,DWORD);
#ifdef __cplusplus
}
#endif
#endif 
