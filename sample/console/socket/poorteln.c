/* poorteln.c (emx+gcc) */

/* rs: written for Win32 sockets and unix socket support */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <process.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#ifdef USE_WINSOCK
/* ************************************************************************* */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock.h>
#define read(a,b,c)  (((a)>2)? recv((a),(b),(c),0) : read((a),(b),(c)))
#define write(a,b,c) (((a)>2)? send((a),(b),(c),0) : write((a),(b),(c)))
#define ioctl(a,b,c) ioctlsocket((a),(b),(c))
/* ************************************************************************* */
#else
/* ************************************************************************* */
#include <io.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SOCKET_ERROR -1
/* ************************************************************************* */
#endif

static void print_error (char * string)
{
#ifdef USE_WINSOCK
  printf("Error in %s; Code = %d\n", string, WSAGetLastError());
#else
  perror(string);
#endif
}

/* **** EASYSOCK.C ****************************************** */

int es_dot_count (const char *src)
{
  int n;

  n = 0;
  while (*src != 0)
    if (*src++ == '.')
      ++n;
  return n;
}


void es_parse_host (struct sockaddr_in *dst, const char *src)
{
  unsigned long ip;

  memset (dst, 0, sizeof (*dst));

  ip = inet_addr (src);
  if (ip != INADDR_NONE && es_dot_count (src) == 3)
    {
      dst->sin_family = AF_INET;
      dst->sin_addr.s_addr = ip;
    }
  else
    {
      struct hostent *host;

      host = gethostbyname (src);
      if (host == NULL)
        {
          fputs ("error: gethostbyname()", stderr);
          exit (1);
        }
      dst->sin_family = host->h_addrtype;
      memcpy (&dst->sin_addr, host->h_addr, host->h_length);
    }
}


void es_parse_port (int *dst, const char *src)
{
  if (isdigit ((unsigned char)src[0]))
    *dst = htons (atoi (src));
  else
    {
      struct servent *serv;

      serv = getservbyname (src, NULL);
      if (serv == NULL)
        {
          fputs ("getservbyname(): Service not found\n", stderr);
          exit (1);
        }
      *dst = serv->s_port;
    }
}


void es_socket (int *ps)
{
  int s;

  s = socket (AF_INET, SOCK_STREAM, 0);
  if (s == SOCKET_ERROR)
    {
      print_error ("socket()");
      exit (1);
    }
  *ps = s;
}


void es_reuse (int s)
{
  int i;

  i = 0;
  if (setsockopt (s, SOL_SOCKET, SO_REUSEADDR,
        (const char *) &i, sizeof (i)) == SOCKET_ERROR)
    {
      print_error ("setsockopt()");
      exit (1);
    }
}



void es_bind_any (int s)
{
  struct sockaddr_in in;

  memset (&in, 0, sizeof (in));
  in.sin_family = AF_INET;
  in.sin_addr.s_addr = INADDR_ANY;
  in.sin_port = 0;
  if (bind (s, (struct sockaddr *)&in, sizeof (in)) == SOCKET_ERROR)
    {
      print_error ("bind()");
      exit (1);
    }
}


void es_connect (int s, const struct sockaddr_in *in)
{
  if (connect (s, (struct sockaddr *)in, sizeof (*in)) == SOCKET_ERROR)
    {
      print_error ("connect()");
      exit (1);
    }
}


void es_getsockname (struct sockaddr_in *in, int s)
{
  int i;

  i = sizeof (*in);
  if (getsockname (s, (struct sockaddr *)in, &i) == SOCKET_ERROR)
    {
      print_error ("getsockname()");
      exit (1);
    }
}

/* ********************************************************** */

static void copy (int from, int to)
{
  int nread, nwritten;
  char *p;
  static char buf[4096];

  while ((nread = read (from, buf, sizeof (buf))) > 0)
    {
      p = buf;
      while (nread > 0)
        {
          nwritten = write (to, p, nread);
          if (nwritten < 0)
            break;
          nread -= nwritten;
          p += nwritten;
        }
    }
}


static void read_socket (void *arg)
{
  copy (*(int *)arg, STDOUT_FILENO);
  exit (1);
}


static void write_socket (void *arg)
{
  copy (STDIN_FILENO, *(int *)arg);
  exit (1);
}

struct sockaddr_emx {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};

int poorteln (char *pszHost, char *pszPort)
{
  struct sockaddr_in in_local, in_server;
  int s_server, port, i;

  es_parse_host (&in_server, pszHost);
  es_parse_port (&port, pszPort);

  in_server.sin_port = port;

  es_socket (&s_server);
  es_reuse (s_server);
  es_bind_any (s_server);
  es_getsockname (&in_local, s_server);

  printf ("Socket handle:         %d\n", s_server);
#ifndef USE_WINSOCK
  printf ("TCP/IP socket handle:  %d\n", _getsockhandle (s_server));
#endif
  printf ("Local port number:     %d\n", ntohs (in_local.sin_port));

  es_connect (s_server, &in_server);

  puts ("connected!");

#if 0
  i = 0;
  if (ioctl (s_server, FIONBIO, (void *)&i) == SOCKET_ERROR)
    print_error ("ioctl(FIONBIO)");
#endif

  setmode (STDIN_FILENO, O_BINARY);
  setmode (STDOUT_FILENO, O_BINARY);

  _beginthread (write_socket, 0, 0x8000, &s_server);
  read_socket (&s_server);

  close (s_server);
  return 0;
}

#ifdef USE_WINSOCK
void myexit ()
{
  WSACleanup();
}
#endif

int main (int argc, char *argv[])
{
  if (argc != 3)
    {
      fputs ("Usage: poorteln <host> <port>\n", stderr);
      return 1;
    }

#ifdef USE_WINSOCK
  {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,0), &wsa);
    atexit (myexit);
  }
#endif

  return poorteln (argv[1], argv[2]);
}
