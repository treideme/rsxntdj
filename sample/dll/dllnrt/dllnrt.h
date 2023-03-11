#ifndef DLLNRT_H
#define DLLNRT_H

int WINAPI Minimum(int, int);
int WINAPI Maximum(int, int);
int WINAPI _sub(int, int);
int WINAPI _add(int, int);

typedef int (*FUNC2) (char *, char *);
int WINAPI callme (FUNC2);

#endif
