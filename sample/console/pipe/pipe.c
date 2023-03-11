/*

  This demo runs a pipe read and a pipe write process

  Uses: pipe(), dup(), dup2(), fcntl() and wait()

*/

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <process.h>
#include <errno.h>
#include <sys/wait.h>

#define STDIN_FILE_NO 0
#define STDOUT_FILE_NO 1
#define READ_PORT 0
#define WRITE_PORT 1

static int last_pipe_input;

static int pexecute (char *program, char *arg, int not_last)
{
  int pid;
  int pdes[2], org_stdin = STDIN_FILE_NO, org_stdout = STDOUT_FILE_NO;
  int input_desc = last_pipe_input;
  int output_desc = STDOUT_FILE_NO;

  /* If this isn't the last process, make a pipe for its output,
     and record it as waiting to be the input to the next process.  */

  if (not_last)
    {
      if (pipe (pdes) < 0)
        perror ("pipe");
      output_desc = pdes[WRITE_PORT];
      last_pipe_input = pdes[READ_PORT];
    }
  else
    last_pipe_input = STDIN_FILE_NO;

  if (input_desc != STDIN_FILE_NO)
    {
      org_stdin = dup (STDIN_FILE_NO);
      dup2 (input_desc, STDIN_FILE_NO);
      close (input_desc); 
      fcntl (org_stdin, F_SETFD, 1);
    }
  if (output_desc != STDOUT_FILE_NO)
    {
      org_stdout = dup (STDOUT_FILE_NO);
      dup2 (output_desc, STDOUT_FILE_NO);
      close (output_desc);
      fcntl (org_stdout, F_SETFD, 1);
    }
  if (not_last)
    {
      fcntl (pdes[WRITE_PORT], F_SETFD, 1);
      fcntl (pdes[READ_PORT], F_SETFD, 1);
    }

  pid = spawnlp (P_NOWAIT, program, arg, NULL);

  if (input_desc != STDIN_FILE_NO)
    {
      dup2 (org_stdin, STDIN_FILE_NO);
      close (org_stdin);
    }
  if (output_desc != STDOUT_FILE_NO)
    {
      dup2 (org_stdout, STDOUT_FILE_NO);
      close (org_stdout);
    }

  if (pid == -1)
    {
      perror (program);
      exit (-1);
    }

  return pid;
}

struct run_cmds {
    char    *program;
    char    *args;
    int     pid;
    int     retcode;
    int     signal;
};

static int execute (struct run_cmds *runcmds, int no_of_procs)
{
    int i;

    last_pipe_input = STDIN_FILE_NO;

    for (i = 0; i < no_of_procs; ++i)
    {
        runcmds[i].pid = pexecute (
                            runcmds[i].program,
                            runcmds[i].args,
                            (i + 1 < no_of_procs) );
    }

    for (i = 0; i < no_of_procs; )
    {
        int j, status, pid;

        pid = wait (& status);

        while (pid < 0 && errno == EINTR) /* only EMX */
            pid = wait (&status);

        if (pid < 0)
        {
            perror ("wait");
            exit (1);
        }

        for (j = 0; j < no_of_procs; j++)
        {
            if (runcmds[j].pid == pid)
	    {
                i++;

                if (WIFEXITED (status))
                {
                    runcmds[j].retcode = WEXITSTATUS (status);
                    runcmds[j].signal = 0;
                }
                else if (WIFSIGNALED (status))
                {
                    runcmds[j].retcode = -1;
                    runcmds[j].signal = WTERMSIG (status);
                }
                else
                {
                    runcmds[j].retcode = -1;
                    runcmds[j].signal = WSTOPSIG (status);
                }
                break;
	    }
        }
    }

    return (0);
}

int main (int argc, const char * const *argv)
{
    static struct run_cmds runcmds[] =
    {
        { "pipew.exe", NULL, 0, 0, 0},
        { "piper.exe", NULL, 0, 0, 0},
    };
    static int no_of_progs = sizeof (runcmds) / sizeof (struct run_cmds);
    int i;

    execute (runcmds, no_of_progs);

    for (i = 0; i < no_of_progs; ++i)
        fprintf(stderr, "pid %d retc %d signal %d\n",
                        runcmds[i].pid,
                        runcmds[i].retcode,
                        runcmds[i].signal);

    return 0;
}
