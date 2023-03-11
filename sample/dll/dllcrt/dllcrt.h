#ifndef DLLCRT_H
#define DLLCRT_H

#define DLLOPENFILE_NAME "DllOpenFile"
int DllOpenFile();
typedef int (*DLLOPENFILE) (void);

#define DLLCLOSEFILE_NAME "DllCloseFile"
int DllCloseFile();
typedef int (*DLLCLOSEFILE) (int);

#endif /* DLLCRT_H */
