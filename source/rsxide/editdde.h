#define NCHAR_DDE 128
#define NCHAR_DDE_NAME 64
#define NCHAR_DDE_PATH 512

extern char dde_name[];
extern char dde_editor[];
extern char dde_service[];
extern char dde_topic[];
extern char dde_fileopen[];
extern char dde_goto[];
extern char dde_markline[];

#define EDIT_PFE32      0
#define EDIT_VIW        1
#define EDIT_WINWORD    2

struct dde_editor {
    char *dde_name;
    char *dde_editor;
    char *dde_service;
    char *dde_topic;
    char *dde_fileopen;
    char *dde_goto;
    char *dde_markline;
};

extern struct dde_editor dde_editors[];

BOOL EditDdeConnect     (void);
BOOL EditDdeFileOpen    (LPSTR, LPSTR);
int  EditDdeMarkLine    (long);
int  EditDdeDisconnect  (void);
BOOL connect_editor (BOOL init);
int  EditDdeError (LPSTR, LPSTR, long);

