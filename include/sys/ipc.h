/* sys/ipc.h (emx+gcc) */

#ifndef _SYS_IPC_H
#define _SYS_IPC_H

#if !defined (_KEY_T)
#define _KEY_T
typedef long key_t;
#endif

#if !defined (_IPC_PERM)
#define _IPC_PERM
struct ipc_perm
{
  unsigned short uid;
  unsigned short gid;
  unsigned short cuid;
  unsigned short cgid;
  unsigned short mode;
  unsigned short seq;
  key_t key;
};
#endif

#if !defined (IPC_CREAT)
#define IPC_CREAT   0x0200
#define IPC_EXCL    0x0400
#define IPC_NOWAIT  0x0800
#define IPC_ALLOC   0x8000

#define IPC_PRIVATE (key_t)0

#define IPC_RMID    0
#define IPC_SET     1
#define IPC_STAT    2
#endif

#endif /* not SYS_IPC_H */
