/*  spawn.c (rsxnt) -- Copyright (c) 1996-1997 Rainer Schnitker
 *
 *  code for wait()/waitpid()/cwait() for different compilers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <sys/types.h>

#ifdef __EMX__	/***********************************************************/

#include <sys/wait.h>

int do_wait (int wpid)
{
  int status, pid;

  /* pid = waitpid (wpid, &status, 0); */
  pid = wait (&status);

  if (pid != -1)
    {
      printf("wait pid = %d\n", pid);
      if (WIFEXITED (status))
	printf ("Normal process termination, rc=%d\n", WEXITSTATUS (status));
      else if (WIFSIGNALED (status))
	printf ("Process terminated by signal %d\n", WTERMSIG (status));
      else
	printf ("Process stopped by signal %d\n", WSTOPSIG (status));
    }
  else
    perror ("wait");
  return pid;
}
#else /* !__EMX__  *********************************************************/

int do_wait (int wpid)
{
  int status, pid;

  pid = cwait (&status, wpid, WAIT_CHILD);

  if (pid >= 0)
    {
      printf("wait pid = %d\n", pid);
      if ((status & 0xFF) == 0)
	printf ("Normal process termination, rc=%d\n", status >> 8);
      else if ((status >> 8) == 0)
      {
	char * err;

	switch (status & 0xff)
	{
	  case 1: err = "Hard error"; break;
	  case 2: err = "Trap error"; break;
	  case 3: err = "SIGTERM signal"; break;
	  default: err = "unkown error";
	}
	printf ("Process terminated with %s", err);
      }
    }
  else
    perror ("wait");
  return pid;
}
#endif /* !__EMX__  ********************************************************/


int main()
{
  int pid;

  if ((pid = spawnlp (P_NOWAIT, "gcc.exe", "gcc", "-v", NULL)) == -1)
  {
    puts ("error running gcc");
    return 1;
  }

  printf("spawn pid = %d\n", pid);
  fflush (stdout);

  do_wait (pid);

  fflush (stdout);
  return 0;
}
