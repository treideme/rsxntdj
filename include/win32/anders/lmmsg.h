#ifndef _LMMSG_H
#define _LMMSG_H
#ifdef __cplusplus
extern "C" {
#endif
#define MSGNAME_NOT_FORWARDED 0
#define MSGNAME_FORWARDED_TO 4
#define MSGNAME_FORWARDED_FROM 16
typedef struct _MSG_INFO_0 { LPTSTR msgi0_name; }MSG_INFO_0,*PMSG_INFO_0,*LPMSG_INFO_0;
typedef struct _MSG_INFO_1 {
	LPTSTR msgi1_name;
	DWORD msgi1_forward_flag;
	LPTSTR msgi1_forward;
}MSG_INFO_1,*PMSG_INFO_1,*LPMSG_INFO_1;
NET_API_STATUS WINAPI NetMessageBufferSend(LPTSTR,LPTSTR,LPTSTR,PBYTE,DWORD);
NET_API_STATUS WINAPI NetMessageNameAdd(LPTSTR,LPTSTR);
NET_API_STATUS WINAPI NetMessageNameDel(LPTSTR,LPTSTR);
NET_API_STATUS WINAPI NetMessageNameEnum(LPTSTR,DWORD,PBYTE*,DWORD,PDWORD,PDWORD,PDWORD);
NET_API_STATUS WINAPI NetMessageNameGetInfo(LPTSTR,LPTSTR,DWORD,PBYTE*);
#ifdef __cplusplus
}
#endif
#endif 
