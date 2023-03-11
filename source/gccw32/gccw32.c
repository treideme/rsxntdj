#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <process.h>
#include <string.h>

static void add_environment (char * entry, char * env, char * rsxnt, char *subtree)
{
    char *old = getenv (env);
    
    strcpy (entry, env);
    strcat (entry, "=");
    strcat (entry, rsxnt);
    strcat (entry, subtree);
    if (old)
    {
        strcat(entry, ";");
        strcat(entry, old);
    }
    putenv (entry);
}

int main (int argc, char ** argv)
{
    char * rsxntdj = getenv ("RSXNTDJ");
    if (rsxntdj)
    {
        char lib[1024], c[1024];
        
        add_environment(lib, "LIBRARY_PATH", rsxntdj, "\\lib");
	add_environment(c, "C_INCLUDE_PATH", rsxntdj, "\\include");
	add_environment(c, "C_INCLUDE_PATH", rsxntdj, "\\include\\win32");
	//add_environment(c, "C_INCLUDE_PATH", rsxntdj, "\\include\\mssdk\\original");
	//add_environment(c, "C_INCLUDE_PATH", rsxntdj, "\\include\\mssdk");
	add_environment(c, "C_INCLUDE_PATH", rsxntdj, "\\include\\win32\\anders");
	add_environment(c, "CPLUS_INCLUDE_PATH", rsxntdj, "\\include");
	add_environment(c, "CPLUS_INCLUDE_PATH", rsxntdj, "\\include\\win32");
	//add_environment(c, "CPLUS_INCLUDE_PATH", rsxntdj, "\\include\\mssdk\\original");
	//add_environment(c, "CPLUS_INCLUDE_PATH", rsxntdj, "\\include\\mssdk");
	add_environment(c, "CPLUS_INCLUDE_PATH", rsxntdj, "\\include\\win32\\anders");

        argv[0] = "gcc";
        return spawnvp (P_WAIT, "gcc.exe", argv);
    }
    else
    {
        char error[] = "set rsxntdj environment\r\n";
        write (1, error, sizeof(error)-1);
        return 1;
    }
}

