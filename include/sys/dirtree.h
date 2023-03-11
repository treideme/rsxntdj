/* sys/dirtree.h (emx+gcc) */

#ifndef _SYS_DIRTREE_H
#define _SYS_DIRTREE_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (_TIME_T)
#define _TIME_T
typedef unsigned long time_t;
#endif

struct _dt_node
{
  struct _dt_node *next;   /* Pointer to next entry of same level */
  struct _dt_node *sub;    /* Pointer to next level (child) */
  char *name;              /* Name */
  long size;               /* File size */
  long user;               /* Available for user */
  time_t mtime;            /* Timestamp for last update */
  unsigned char attr;      /* Attributes */
};


struct _dt_tree
{
  struct _dt_node *tree;
  char *strings;
};

#define _DT_TREE     0x4000
#define _DT_NOCPDIR  0x8000

void _dt_free (struct _dt_tree *dt);
struct _dt_tree *_dt_read (__const__ char *dir, __const__ char *mask,
    unsigned flags);
void _dt_sort (struct _dt_tree *dt, __const__ char *spec);
int _dt_split (__const__ char *src, char *dir, char *mask);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_DIRTREE_H */
