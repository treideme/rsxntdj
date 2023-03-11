#ifndef _COMMCTRL_H
#define _COMMCTRL_H
#include <prsht.h>
#ifdef __cplusplus
extern "C" {
#endif
#define DRAGLISTMSGSTRING TEXT("commctrl_DragListMsg")
#define ANIMATE_CLASSW	L"SysAnimate32"
#define ANIMATE_CLASSA	"SysAnimate32"
#define HOTKEY_CLASSA	"msctls_hotkey32"
#define HOTKEY_CLASSW	L"msctls_hotkey32"
#define PROGRESS_CLASSA	"msctls_progress32"
#define PROGRESS_CLASSW	L"msctls_progress32"
#define STATUSCLASSNAMEA	"msctls_statusbar32"
#define STATUSCLASSNAMEW	L"msctls_statusbar32"
#define TOOLBARCLASSNAMEW	L"ToolbarWindow32"
#define TOOLBARCLASSNAMEA	"ToolbarWindow32"
#define TOOLTIPS_CLASSW	L"tooltips_class32"
#define TOOLTIPS_CLASSA	"tooltips_class32"
#define TRACKBAR_CLASSA	"msctls_trackbar32"
#define TRACKBAR_CLASSW	L"msctls_trackbar32"
#define UPDOWN_CLASSA	"msctls_updown32"
#define UPDOWN_CLASSW	L"msctls_updown32"
#define WC_LISTVIEWA	"SysListView32"
#define WC_LISTVIEWW	L"SysListView32"
#define WC_TABCONTROLA	"SysTabControl32"
#define WC_TABCONTROLW	L"SysTabControl32"
#define WC_TREEVIEWA	"SysTreeView32"
#define WC_TREEVIEWW	L"SysTreeView32"
#define WC_HEADERA	"SysHeader32"
#define WC_HEADERW 	L"SysHeader32"
#define LVM_FIRST 0x1000
#define TV_FIRST 0x1100
#define HDM_FIRST 0x1200
#define ACM_OPENA	(WM_USER+100)
#define ACM_PLAY	(WM_USER+101)
#define ACM_STOP	(WM_USER+102)
#define ACM_OPENW	(WM_USER+103)
#define ACN_START	1
#define ACN_STOP	2
#define DL_BEGINDRAG	1157
#define DL_CANCELDRAG	1160
#define DL_DRAGGING	1158
#define DL_DROPPED	1159
#define DL_CURSORSET	0
#define DL_STOPCURSOR	1
#define DL_COPYCURSOR	2
#define DL_MOVECURSOR	3
#define CCS_TOP	1
#define CCS_NOMOVEY	2
#define CCS_BOTTOM	3
#define CCS_NORESIZE	4
#define CCS_NOPARENTALIGN	8
#define CCS_ADJUSTABLE	32
#define CCS_NODIVIDER	64
#define CMB_MASKED	2
#define MINSYSCOMMAND	SC_SIZE
#define SBT_OWNERDRAW	0x1000
#define SBT_NOBORDERS	256
#define SBT_POPOUT	512
#define SBT_RTLREADING	1024
#define SB_SETTEXTA	(WM_USER+1)
#define SB_SETTEXTW	(WM_USER+11)
#define SB_GETTEXTA	(WM_USER+2)
#define SB_GETTEXTW	(WM_USER+13)
#define SB_GETTEXTLENGTHA	(WM_USER+3)
#define SB_GETTEXTLENGTHW	(WM_USER+12)
#define SB_SETPARTS	(WM_USER+4)
#define SB_GETPARTS	(WM_USER+6)
#define SB_GETBORDERS	(WM_USER+7)
#define SB_SETMINHEIGHT	(WM_USER+8)
#define SB_SIMPLE	(WM_USER+9)
#define SB_GETRECT	(WM_USER+10)
#define MSGF_COMMCTRL_BEGINDRAG	0x4200
#define MSGF_COMMCTRL_SIZEHEADER	0x4201
#define MSGF_COMMCTRL_DRAGSELECT	0x4202
#define MSGF_COMMCTRL_TOOLBARCUST	0x4203
#define ILC_COLOR 0
#define ILC_COLOR4 4
#define ILC_COLOR8 8
#define ILC_COLOR16 16
#define ILC_COLOR24 24
#define ILC_COLOR32 32
#define ILC_COLORDDB 254
#define ILC_MASK 1
#define ILC_PALETTE 2048
#define ILD_BLEND25 2
#define ILD_BLEND50 4
#define ILD_SELECTED 4
#define ILD_BLEND 4
#define ILD_FOCUS 2
#define ILD_MASK 16
#define ILD_NORMAL 0
#define ILD_TRANSPARENT 1
#define HDS_HORZ	0
#define HDS_BUTTONS	2
#define HDS_HIDDEN	8
#define NM_FIRST	0
#define NM_LAST	(-99)
#define LVN_FIRST	(-100)
#define LVN_LAST	(-199)
#define HDN_FIRST	(-300)
#define HDN_LAST	(-399)
#define TVN_FIRST	(-400)
#define TVN_LAST	(-499)
#define TTN_FIRST	(-520)
#define TTN_LAST	(-549)
#define TCN_FIRST	(-550)
#define TCN_LAST	(-580)
#define CDN_FIRST	(-601)
#define CDN_LAST	(-699)
#define TBN_FIRST	(-700)
#define TBN_LAST	(-720)
#define UDN_FIRST	(-721)
#define UDN_LAST	(-740)
#define HDI_WIDTH	1
#define HDI_HEIGHT	1
#define HDI_TEXT	2
#define HDI_FORMAT	4
#define HDI_LPARAM	8
#define HDI_BITMAP	16
#define HDF_LEFT	0
#define HDF_RIGHT	1
#define HDF_CENTER	2
#define HDF_JUSTIFYMASK3
#define HDF_RTLREADING	4
#define HDF_OWNERDRAW	0x8000
#define HDF_STRING	0x4000
#define HDF_BITMAP	0x2000
#define HDM_GETITEMCOUNT	HDM_FIRST
#define HDM_INSERTITEMA	(HDM_FIRST+1)
#define HDM_INSERTITEMW	(HDM_FIRST+10)
#define HDM_DELETEITEM	(HDM_FIRST+2)
#define HDM_GETITEMA	(HDM_FIRST+3)
#define HDM_GETITEMW	(HDM_FIRST+11)
#define HDM_SETITEMA	(HDM_FIRST+4)
#define HDM_SETITEMW	(HDM_FIRST+12)
#define HDM_LAYOUT	(HDM_FIRST+5)
#define HHT_NOWHERE	1
#define HHT_ONHEADER	2
#define HHT_ONDIVIDER	4
#define HHT_ONDIVOPEN	8
#define HHT_ABOVE	256
#define HHT_BELOW	512
#define HHT_TORIGHT	1024
#define HHT_TOLEFT	2048
#define HDM_HITTEST	(HDM_FIRST+6)
#define HDN_ITEMCHANGINGA	(HDN_FIRST-0)
#define HDN_ITEMCHANGINGW	(HDN_FIRST-20)
#define HDN_ITEMCHANGEDA	(HDN_FIRST-1)
#define HDN_ITEMCHANGEDW	(HDN_FIRST-21)
#define HDN_ITEMCLICKA	(HDN_FIRST-2)
#define HDN_ITEMCLICKW	(HDN_FIRST-22)
#define HDN_ITEMDBLCLICKA	(HDN_FIRST-3)
#define HDN_ITEMDBLCLICKW	(HDN_FIRST-23)
#define HDN_DIVIDERDBLCLICKA	(HDN_FIRST-5)
#define HDN_DIVIDERDBLCLICKW	(HDN_FIRST-25)
#define HDN_BEGINTRACKA	(HDN_FIRST-6)
#define HDN_BEGINTRACKW	(HDN_FIRST-26)
#define HDN_ENDTRACKA	(HDN_FIRST-7)
#define HDN_ENDTRACKW	(HDN_FIRST-27)
#define HDN_TRACKA	(HDN_FIRST-8)
#define HDN_TRACKW	(HDN_FIRST-28)
#define CMB_MASKED 2
#define TBSTATE_CHECKED	1
#define TBSTATE_PRESSED	2
#define TBSTATE_ENABLED	4
#define TBSTATE_HIDDEN	8
#define TBSTATE_INDETERMINATE	16
#define TBSTATE_WRAP	32
#define TBSTYLE_BUTTON	0
#define TBSTYLE_SEP	1
#define TBSTYLE_CHECK	2
#define TBSTYLE_GROUP	4
#define TBSTYLE_CHECKGROUP	(TBSTYLE_GROUP|TBSTYLE_CHECK)
#define TBSTYLE_TOOLTIPS	256
#define TBSTYLE_WRAPABLE	512
#define TBSTYLE_ALTDRAG	1024
#define TB_ENABLEBUTTON	(WM_USER+1)
#define TB_CHECKBUTTON	(WM_USER+2)
#define TB_PRESSBUTTON	(WM_USER+3)
#define TB_HIDEBUTTON	(WM_USER+4)
#define TB_INDETERMINATE	(WM_USER+5)
#define TB_ISBUTTONENABLED	(WM_USER+9)
#define TB_ISBUTTONCHECKED	(WM_USER+10)
#define TB_ISBUTTONPRESSED	(WM_USER+11)
#define TB_ISBUTTONHIDDEN	(WM_USER+12)
#define TB_ISBUTTONINDETERMINATE	(WM_USER+13)
#define TB_SETSTATE	(WM_USER+17)
#define TB_GETSTATE	(WM_USER+18)
#define TB_ADDBITMAP	(WM_USER+19)
#define HINST_COMMCTRL	((HINSTANCE)-1)
#define IDB_STD_SMALL_COLOR	0
#define IDB_STD_LARGE_COLOR	1
#define IDB_VIEW_SMALL_COLOR	4
#define IDB_VIEW_LARGE_COLOR	5
#define STD_CUT	0
#define STD_COPY	1
#define STD_PASTE	2
#define STD_UNDO	3
#define STD_REDOW	4
#define STD_DELETE	5
#define STD_FILENEW	6
#define STD_FILEOPEN	7
#define STD_FILESAVE	8
#define STD_PRINTPRE	9
#define STD_PROPERTIES	10
#define STD_HELP	11
#define STD_FIND	12
#define STD_REPLACE	13
#define STD_PRINT	14
#define VIEW_LARGEICONS	0
#define VIEW_SMALLICONS	1
#define VIEW_LIST	2
#define VIEW_DETAILS	3
#define VIEW_SORTNAME	4
#define VIEW_SORTSIZE	5
#define VIEW_SORTDATE	6
#define VIEW_SORTTYPE	7
#define VIEW_PARENTFOLDER	8
#define VIEW_NETCONNECT	9
#define VIEW_NETDISCONNECT	10
#define VIEW_NEWFOLDER	11
#define TB_ADDBUTTONS	(WM_USER+20)
#define TB_INSERTBUTTON	(WM_USER+21)
#define TB_DELETEBUTTON	(WM_USER+22)
#define TB_GETBUTTON	(WM_USER+23)
#define TB_BUTTONCOUNT	(WM_USER+24)
#define TB_COMMANDTOINDEX	(WM_USER+25)
#define TB_SAVERESTOREA	(WM_USER+26)
#define TB_SAVERESTOREW	(WM_USER+76)
#define TB_CUSTOMIZE	(WM_USER+27)
#define TB_ADDSTRINGA	(WM_USER+28)
#define TB_ADDSTRINGW	(WM_USER+77)
#define TB_GETITEMRECT	(WM_USER+29)
#define TB_BUTTONSTRUCTSIZE	(WM_USER+30)
#define TB_SETBUTTONSIZE	(WM_USER+31)
#define TB_SETBITMAPSIZE	(WM_USER+32)
#define TB_AUTOSIZE	(WM_USER+33)
#define TB_GETTOOLTIPS	(WM_USER+35)
#define TB_SETTOOLTIPS	(WM_USER+36)
#define TB_SETPARENT	(WM_USER+37)
#define TB_SETROWS	(WM_USER+39)
#define TB_GETROWS	(WM_USER+40)
#define TB_SETCMDID	(WM_USER+42)
#define TB_CHANGEBITMAP	(WM_USER+43)
#define TB_GETBITMAP	(WM_USER+44)
#define TB_GETBUTTONTEXTA	(WM_USER+45)
#define TB_GETBUTTONTEXTW	(WM_USER+75)
#define TB_REPLACEBITMAP	(WM_USER+46)
#define TBBF_LARGE 1
#define TB_GETBITMAPFLAGS	(WM_USER+41)
#define TBN_GETBUTTONINFOA	(TBN_FIRST-0)
#define TBN_GETBUTTONINFOW	(TBN_FIRST-20)
#define TBN_BEGINDRAG	(TBN_FIRST-1)
#define TBN_ENDDRAG	(TBN_FIRST-2)
#define TBN_BEGINADJUST	(TBN_FIRST-3)
#define TBN_ENDADJUST	(TBN_FIRST-4)
#define TBN_RESET	(TBN_FIRST-5)
#define TBN_QUERYINSERT	(TBN_FIRST-6)
#define TBN_QUERYDELETE	(TBN_FIRST-7)
#define TBN_TOOLBARCHANGE	(TBN_FIRST-8)
#define TBN_CUSTHELP	(TBN_FIRST-9)
#define TTS_ALWAYSTIP	1
#define TTS_NOPREFIX	2
#define TTF_IDISHWND	1
#define TTF_CENTERTIP	2
#define TTF_RTLREADING	4
#define TTF_SUBCLASS	16
#define TTDT_AUTOMATIC	0
#define TTDT_RESHOW	1
#define TTDT_AUTOPOP	2
#define TTDT_INITIAL	3
#define TTM_ACTIVATE	(WM_USER+1)
#define TTM_SETDELAYTIME	(WM_USER+3)
#define TTM_ADDTOOLA	(WM_USER+4)
#define TTM_ADDTOOLW	(WM_USER+50)
#define TTM_DELTOOLA	(WM_USER+5)
#define TTM_DELTOOLW	(WM_USER+51)
#define TTM_NEWTOOLRECTA	(WM_USER+6)
#define TTM_NEWTOOLRECTW	(WM_USER+52)
#define TTM_RELAYEVENT	(WM_USER+7)
#define TTM_GETTOOLINFOA	(WM_USER+8)
#define TTM_GETTOOLINFOW	(WM_USER+53)
#define TTM_SETTOOLINFOA	(WM_USER+9)
#define TTM_SETTOOLINFOW	(WM_USER+54)
#define TTM_HITTESTA	(WM_USER+10)
#define TTM_HITTESTW	(WM_USER+55)
#define TTM_GETTEXTA	(WM_USER+11)
#define TTM_GETTEXTW	(WM_USER+56)
#define TTM_UPDATETIPTEXTA	(WM_USER+12)
#define TTM_UPDATETIPTEXTW	(WM_USER+57)
#define TTM_GETTOOLCOUNT	(WM_USER +13)
#define TTM_ENUMTOOLSA	(WM_USER+14)
#define TTM_ENUMTOOLSW	(WM_USER+58)
#define TTM_GETCURRENTTOOLA	(WM_USER+15)
#define TTM_GETCURRENTTOOLW	(WM_USER+59)
#define TTM_WINDOWFROMPOINT	(WM_USER+16)
#define TTN_NEEDTEXTA	(TTN_FIRST-0)
#define TTN_NEEDTEXTW	(TTN_FIRST-10)
#define TTN_SHOW	(TTN_FIRST-1)
#define TTN_POP	(TTN_FIRST-2)
#define UD_MAXVAL	0x7fff
#define UD_MINVAL	(-UD_MAXVAL)
#define UDN_DELTAPOS (UDN_FIRST-1)
#define UDS_WRAP	1
#define UDS_SETBUDDYINT	2
#define UDS_ALIGNRIGHT	4
#define UDS_ALIGNLEFT	8
#define UDS_AUTOBUDDY	16
#define UDS_ARROWKEYS	32
#define UDS_HORZ	64
#define UDS_NOTHOUSANDS	128
#define UDM_SETRANGE	(WM_USER+101)
#define UDM_GETRANGE	(WM_USER+102)
#define UDM_SETPOS	(WM_USER+103)
#define UDM_GETPOS	(WM_USER+104)
#define UDM_SETBUDDY	(WM_USER+105)
#define UDM_GETBUDDY	(WM_USER+106)
#define UDM_SETACCEL	(WM_USER+107)
#define UDM_GETACCEL	(WM_USER+108)
#define UDM_SETBASE	(WM_USER+109)
#define UDM_GETBASE	(WM_USER+110)
#define SB_SETTEXTA	(WM_USER+1)
#define SB_SETTEXTW	(WM_USER+11)
#define SB_GETTEXTA	(WM_USER+2)
#define SB_GETTEXTW	(WM_USER+13)
#define SB_GETTEXTLENGTHA	(WM_USER+3)
#define SB_GETTEXTLENGTHW	(WM_USER+12)
#define SB_SETPARTS	(WM_USER+4)
#define SB_GETPARTS	(WM_USER+6)
#define SB_GETBORDERS	(WM_USER+7)
#define SB_SETMINHEIGHT	(WM_USER+8)
#define SB_SIMPLE	(WM_USER+9)
#define SB_GETRECT	(WM_USER+10)
#define SBT_OWNERDRAW	0x1000
#define SBT_NOBORDERS	256
#define SBT_POPOUT	512
#define SBT_RTLREADING	1024
#define TBS_AUTOTICKS	1
#define TBS_VERT	2
#define TBS_HORZ	0
#define TBS_TOP	4
#define TBS_BOTTOM	0
#define TBS_LEFT	4
#define TBS_RIGHT	0
#define TBS_BOTH	8
#define TBS_NOTICKS	16
#define TBS_ENABLESELRANGE	32
#define TBS_FIXEDLENGTH	64
#define TBS_NOTHUMB	128
#define TBM_GETPOS	(WM_USER)
#define TBM_GETRANGEMIN	(WM_USER+1)
#define TBM_GETRANGEMAX	(WM_USER+2)
#define TBM_GETTIC	(WM_USER+3)
#define TBM_SETTIC	(WM_USER+4)
#define TBM_SETPOS	(WM_USER+5)
#define TBM_SETRANGE	(WM_USER+6)
#define TBM_SETRANGEMIN	(WM_USER+7)
#define TBM_SETRANGEMAX	(WM_USER+8)
#define TBM_CLEARTICS	(WM_USER+9)
#define TBM_SETSEL	(WM_USER+10)
#define TBM_SETSELSTART	(WM_USER+11)
#define TBM_SETSELEND	(WM_USER+12)
#define TBM_GETPTICS	(WM_USER+14)
#define TBM_GETTICPOS	(WM_USER+15)
#define TBM_GETNUMTICS	(WM_USER+16)
#define TBM_GETSELSTART	(WM_USER+17)
#define TBM_GETSELEND	(WM_USER+18)
#define TBM_CLEARSEL	(WM_USER+19)
#define TBM_SETTICFREQ	(WM_USER+20)
#define TBM_SETPAGESIZE	(WM_USER+21)
#define TBM_GETPAGESIZE	(WM_USER+22)
#define TBM_SETLINESIZE	(WM_USER+23)
#define TBM_GETLINESIZE	(WM_USER+24)
#define TBM_GETTHUMBRECT	(WM_USER+25)
#define TBM_GETCHANNELRECT	(WM_USER+26)
#define TBM_SETTHUMBLENGTH	(WM_USER+27)
#define TBM_GETTHUMBLENGTH	(WM_USER+28)
#define TB_LINEUP	0
#define TB_LINEDOWN	1
#define TB_PAGEUP	2
#define TB_PAGEDOWN	3
#define TB_THUMBPOSITION	4
#define TB_THUMBTRACK	5
#define TB_TOP	6
#define TB_BOTTOM	7
#define TB_ENDTRACK	8
#define HOTKEYF_SHIFT	1
#define HOTKEYF_CONTROL	2
#define HOTKEYF_ALT	4
#define HOTKEYF_EXT	8
#define HKCOMB_NONE	1
#define HKCOMB_S	2
#define HKCOMB_C	4
#define HKCOMB_A	8
#define HKCOMB_SC	16
#define HKCOMB_SA	32
#define HKCOMB_CA	64
#define HKCOMB_SCA	128
#define HKM_SETHOTKEY	(WM_USER+1)
#define HKM_GETHOTKEY	(WM_USER+2)
#define HKM_SETRULES	(WM_USER+3)
#define PBM_SETRANGE	(WM_USER+1)
#define PBM_SETPOS	(WM_USER+2)
#define PBM_DELTAPOS	(WM_USER+3)
#define PBM_SETSTEP	(WM_USER+4)
#define PBM_STEPIT	(WM_USER+5)
#define LVS_ICON	0
#define LVS_REPORT	1
#define LVS_SMALLICON	2
#define LVS_LIST	3
#define LVS_TYPEMASK	3
#define LVS_SINGLESEL	4
#define LVS_SHOWSELALWAYS	8
#define LVS_SORTASCENDING	16
#define LVS_SORTDESCENDING	32
#define LVS_SHAREIMAGELISTS	64
#define LVS_NOLABELWRAP	128
#define LVS_AUTOARRANGE	256
#define LVS_EDITLABELS	512
#define LVS_NOSCROLL	0x2000
#define LVS_TYPESTYLEMASK	0xfc00
#define LVS_ALIGNTOP	0
#define LVS_ALIGNLEFT	0x800
#define LVS_ALIGNMASK	0xc00
#define LVS_OWNERDRAWFIXED	0x400
#define LVS_NOCOLUMNHEADER	0x4000
#define LVS_NOSORTHEADER	0x8000
#define LVSIL_NORMAL	0
#define LVSIL_SMALL	1
#define LVSIL_STATE	2
#define LVM_GETBKCOLOR	LVM_FIRST
#define LVM_SETBKCOLOR	(LVM_FIRST+1)
#define LVM_GETIMAGELIST	(LVM_FIRST+2)
#define LVM_SETIMAGELIST	(LVM_FIRST+3)
#define LVM_GETITEMCOUNT	(LVM_FIRST+4)
#define LVIF_TEXT	1
#define LVIF_IMAGE	2
#define LVIF_PARAM	4
#define LVIF_STATE	8
#define LVIS_FOCUSED	1
#define LVIS_SELECTED	2
#define LVIS_CUT	4
#define LVIS_DROPHILITED	8
#define LVIS_OVERLAYMASK	0xF00
#define LVIS_STATEIMAGEMASK	0xF000
#define LPSTR_TEXTCALLBACKW	((LPWSTR)-1)
#define LPSTR_TEXTCALLBACKA	((LPSTR)-1)
#define I_IMAGECALLBACK	(-1)
#define LVM_GETITEMA	(LVM_FIRST+5)
#define LVM_GETITEMW	(LVM_FIRST+75)
#define LVM_SETITEMA	(LVM_FIRST+6)
#define LVM_SETITEMW	(LVM_FIRST+76)
#define LVM_INSERTITEMA	(LVM_FIRST+7)
#define LVM_INSERTITEMW	(LVM_FIRST+77)
#define LVM_DELETEITEM	(LVM_FIRST+8)
#define LVM_DELETEALLITEMS	(LVM_FIRST+9)
#define LVM_GETCALLBACKMASK	(LVM_FIRST+10)
#define LVM_SETCALLBACKMASK	(LVM_FIRST+11)
#define LVNI_ALL	0
#define LVNI_FOCUSED	1
#define LVNI_SELECTED	2
#define LVNI_CUT	4
#define LVNI_DROPHILITED	8
#define LVNI_ABOVE	256
#define LVNI_BELOW	512
#define LVNI_TOLEFT	1024
#define LVNI_TORIGHT	2048
#define LVM_GETNEXTITEM	(LVM_FIRST+12)
#define LVFI_PARAM	1
#define LVFI_STRING	2
#define LVFI_PARTIAL	8
#define LVFI_WRAP	32
#define LVFI_NEARESTXY	64
#define LVIF_DI_SETITEM	0x1000
#define LVM_FINDITEMA	(LVM_FIRST+13)
#define LVM_FINDITEMW	(LVM_FIRST+83)
#define LVIR_BOUNDS	0
#define LVIR_ICON	1
#define LVIR_LABEL	2
#define LVIR_SELECTBOUNDS	3
#define LVM_GETITEMRECT	(LVM_FIRST+14)
#define LVM_SETITEMPOSITION	(LVM_FIRST+15)
#define LVM_GETITEMPOSITION	(LVM_FIRST+16)
#define LVM_GETSTRINGWIDTHA	(LVM_FIRST+17)
#define LVM_GETSTRINGWIDTHW	(LVM_FIRST+87)
#define LVHT_NOWHERE	1
#define LVHT_ONITEMICON	2
#define LVHT_ONITEMLABEL	4
#define LVHT_ONITEMSTATEICON	8
#define LVHT_ONITEM	(LVHT_ONITEMICON|LVHT_ONITEMLABEL|LVHT_ONITEMSTATEICON)
#define LVHT_ABOVE	8
#define LVHT_BELOW	16
#define LVHT_TORIGHT	32
#define LVHT_TOLEFT	64
#define LVM_HITTEST	(LVM_FIRST+18)
#define LVM_ENSUREVISIBLE	(LVM_FIRST+19)
#define LVM_SCROLL	(LVM_FIRST+20)
#define LVM_REDRAWITEMS	(LVM_FIRST+21)
#define LVA_DEFAULT	0
#define LVA_ALIGNLEFT	1
#define LVA_ALIGNTOP	2
#define LVA_SNAPTOGRID	5
#define LVM_ARRANGE	(LVM_FIRST+22)
#define LVM_EDITLABELA	(LVM_FIRST+23)
#define LVM_EDITLABELW	(LVM_FIRST+118)
#define LVM_GETEDITCONTROL	(LVM_FIRST+24)
#define LVCF_FMT	1
#define LVCF_WIDTH	2
#define LVCF_TEXT	4
#define LVCF_SUBITEM	8
#define LVCFMT_LEFT	0
#define LVCFMT_RIGHT	1
#define LVCFMT_CENTER	2
#define LVCFMT_JUSTIFYMASK	3
#define LVM_GETCOLUMNA	(LVM_FIRST+25)
#define LVM_GETCOLUMNW	(LVM_FIRST+95)
#define LVM_SETCOLUMNA	(LVM_FIRST+26)
#define LVM_SETCOLUMNW	(LVM_FIRST+96)
#define LVM_INSERTCOLUMNA	(LVM_FIRST+27)
#define LVM_INSERTCOLUMNW	(LVM_FIRST+97)
#define LVM_DELETECOLUMN	(LVM_FIRST+28)
#define LVM_GETCOLUMNWIDTH	(LVM_FIRST+29)
#define LVSCW_AUTOSIZE	(-1)
#define LVSCW_AUTOSIZE_USEHEADER	(-2)
#define LVM_SETCOLUMNWIDTH	(LVM_FIRST+30)
#define LVM_CREATEDRAGIMAGE	(LVM_FIRST+33)
#define LVM_GETVIEWRECT	(LVM_FIRST+34)
#define LVM_GETTEXTCOLOR	(LVM_FIRST+35)
#define LVM_SETTEXTCOLOR	(LVM_FIRST+36)
#define LVM_GETTEXTBKCOLOR	(LVM_FIRST+37)
#define LVM_SETTEXTBKCOLOR	(LVM_FIRST+38)
#define LVM_GETTOPINDEX	(LVM_FIRST+39)
#define LVM_GETCOUNTPERPAGE	(LVM_FIRST+40)
#define LVM_GETORIGIN	(LVM_FIRST+41)
#define LVM_GETORIGIN	(LVM_FIRST+41)
#define LVM_UPDATE	(LVM_FIRST+42)
#define LVM_SETITEMSTATE	(LVM_FIRST+43)
#define LVM_GETITEMSTATE	(LVM_FIRST+44)
#define LVM_GETITEMTEXTA	(LVM_FIRST+45)
#define LVM_GETITEMTEXTW	(LVM_FIRST+115)
#define LVM_SETITEMTEXTA	(LVM_FIRST+46)
#define LVM_SETITEMTEXTW	(LVM_FIRST+116)
#define LVM_SETITEMCOUNT	(LVM_FIRST+47)
#define LVM_SORTITEMS	(LVM_FIRST+48)
#define LVM_SETITEMPOSITION32	(LVM_FIRST+49)
#define LVM_GETSELECTEDCOUNT	(LVM_FIRST+50)
#define LVM_GETITEMSPACING	(LVM_FIRST+51)
#define LVM_GETISEARCHSTRINGA	(LVM_FIRST+52)
#define LVM_GETISEARCHSTRINGW	(LVM_FIRST+117)
#define LVN_ITEMCHANGING	LVN_FIRST
#define LVN_ITEMCHANGED	(LVN_FIRST-1)
#define LVN_INSERTITEM	(LVN_FIRST-2)
#define LVN_DELETEITEM	(LVN_FIRST-3)
#define LVN_DELETEALLITEMS	(LVN_FIRST-4)
#define LVN_BEGINLABELEDITA	(LVN_FIRST-5)
#define LVN_BEGINLABELEDITW	(LVN_FIRST-75)
#define LVN_ENDLABELEDITA	(LVN_FIRST-6)
#define LVN_ENDLABELEDITW	(LVN_FIRST-76)
#define LVN_COLUMNCLICK	(LVN_FIRST-8)
#define LVN_BEGINDRAG	(LVN_FIRST-9)
#define LVN_BEGINRDRAG	(LVN_FIRST-11)
#define LVN_GETDISPINFOA	(LVN_FIRST-50)
#define LVN_GETDISPINFOW	(LVN_FIRST-77)
#define LVN_SETDISPINFOA	(LVN_FIRST-51)
#define LVN_SETDISPINFOW	(LVN_FIRST-78)
#define LVN_KEYDOWN	(LVN_FIRST-55)
#define TVS_HASBUTTONS	1
#define TVS_HASLINES	2
#define TVS_LINESATROOT	4
#define TVS_EDITLABELS	8
#define TVS_DISABLEDRAGDROP	16
#define TVS_SHOWSELALWAYS	32
#define TVIF_TEXT	1
#define TVIF_IMAGE	2
#define TVIF_PARAM	4
#define TVIF_STATE	8
#define TVIF_HANDLE	16
#define TVIF_SELECTEDIMAGE	32
#define TVIF_CHILDREN	64
#define TVIS_FOCUSED	1
#define TVIS_SELECTED	2
#define TVIS_CUT	4
#define TVIS_DROPHILITED	8
#define TVIS_BOLD	16
#define TVIS_EXPANDED	32
#define TVIS_EXPANDEDONCE	64
#define TVIS_OVERLAYMASK	0xF00
#define TVIS_STATEIMAGEMASK	0xF000
#define TVIS_USERMASK	0xF000
#define I_CHILDRENCALLBACK	(-1)
#define TVI_ROOT	((HTREEITEM)0xFFFF0000)
#define TVI_FIRST	((HTREEITEM)0xFFFF0001)
#define TVI_LAST	((HTREEITEM)0xFFFF0002)
#define TVI_SORT	((HTREEITEM)0xFFFF0003)
#define TVSIL_NORMAL	0
#define TVSIL_STATE	2
#define TVM_INSERTITEMA	TV_FIRST
#define TVM_INSERTITEMW	(TV_FIRST+50)
#define TVM_DELETEITEM	(TV_FIRST+1)
#define TVM_EXPAND	(TV_FIRST+2)
#define TVM_GETITEMRECT	(TV_FIRST+4)
#define TVM_GETCOUNT	(TV_FIRST+5)
#define TVM_GETINDENT	(TV_FIRST+6)
#define TVM_SETINDENT	(TV_FIRST+7)
#define TVM_GETIMAGELIST	(TV_FIRST+8)
#define TVM_SETIMAGELIST	(TV_FIRST+9)
#define TVM_GETNEXTITEM	(TV_FIRST+10)
#define TVM_SELECTITEM	(TV_FIRST+11)
#define TVM_GETITEMA	(TV_FIRST+12)
#define TVM_GETITEMW	(TV_FIRST+62)
#define TVM_SETITEMA	(TV_FIRST+13)
#define TVM_SETITEMW	(TV_FIRST+63)
#define TVM_EDITLABELA	(TV_FIRST+14)
#define TVM_EDITLABELW	(TV_FIRST+65)
#define TVM_GETEDITCONTROL	(TV_FIRST+15)
#define TVM_GETVISIBLECOUNT	(TV_FIRST+16)
#define TVM_HITTEST	(TV_FIRST+17)
#define TVM_CREATEDRAGIMAGE	(TV_FIRST+18)
#define TVM_SORTCHILDREN	(TV_FIRST+19)
#define TVM_ENSUREVISIBLE	(TV_FIRST+20)
#define TVM_SORTCHILDRENCB	(TV_FIRST+21)
#define TVM_ENDEDITLABELNOW	(TV_FIRST+22)
#define TVM_GETISEARCHSTRINGA	(TV_FIRST+23)
#define TVM_GETISEARCHSTRINGW	(TV_FIRST+64)
#define TVE_COLLAPSE	1
#define TVE_EXPAND	2
#define TVE_TOGGLE	3
#define TVE_COLLAPSERESET	0x8000
#define TVC_UNKNOWN	0
#define TVC_BYMOUSE	1
#define TVC_BYKEYBOARD	2
#define TVGN_ROOT	0
#define TVGN_NEXT	1
#define TVGN_PREVIOUS	2
#define TVGN_PARENT	3
#define TVGN_CHILD	4
#define TVGN_FIRSTVISIBLE	5
#define TVGN_NEXTVISIBLE	6
#define TVGN_PREVIOUSVISIBLE	7
#define TVGN_DROPHILITE	8
#define TVGN_CARET	9
#define TVN_SELCHANGINGA	(TVN_FIRST-1)
#define TVN_SELCHANGINGW	(TVN_FIRST-50)
#define TVN_SELCHANGEDA	(TVN_FIRST-2)
#define TVN_SELCHANGEDW	(TVN_FIRST-51)
#define TVN_GETDISPINFOA	(TVN_FIRST-3)
#define TVN_GETDISPINFOW	(TVN_FIRST-52)
#define TVN_SETDISPINFOA	(TVN_FIRST-4)
#define TVN_SETDISPINFOW	(TVN_FIRST-53)
#define TVN_ITEMEXPANDINGA	(TVN_FIRST-5)
#define TVN_ITEMEXPANDINGW	(TVN_FIRST-54)
#define TVN_ITEMEXPANDEDA	(TVN_FIRST-6)
#define TVN_ITEMEXPANDEDW	(TVN_FIRST-55)
#define TVN_BEGINDRAGA	(TVN_FIRST-7)
#define TVN_BEGINDRAGW	(TVN_FIRST-56)
#define TVN_BEGINRDRAGA	(TVN_FIRST-8)
#define TVN_BEGINRDRAGW	(TVN_FIRST-57)
#define TVN_DELETEITEMA	(TVN_FIRST-9)
#define TVN_DELETEITEMW	(TVN_FIRST-58)
#define TVN_BEGINLABELEDITA	(TVN_FIRST-10)
#define TVN_BEGINLABELEDITW	(TVN_FIRST-59)
#define TVN_ENDLABELEDITA	(TVN_FIRST-11)
#define TVN_ENDLABELEDITW	(TVN_FIRST-60)
#define TVN_KEYDOWN	(TVN_FIRST-12)
#define TVIF_DI_SETITEM	0x1000
#define TVHT_NOWHERE	1
#define TVHT_ONITEMICON	2
#define TVHT_ONITEMLABEL	4
#define TVHT_ONITEM	(TVHT_ONITEMICON|TVHT_ONITEMLABEL|TVHT_ONITEMSTATEICON)
#define TVHT_ONITEMINDENT	8
#define TVHT_ONITEMBUTTON	16
#define TVHT_ONITEMRIGHT	32
#define TVHT_ONITEMSTATEICON	64
#define TVHT_ABOVE	256
#define TVHT_BELOW	512
#define TVHT_TORIGHT	1024
#define TVHT_TOLEFT	2048
#define TCHT_NOWHERE	1
#define TCHT_ONITEMICON	2
#define TCHT_ONITEMLABEL	4
#define TCHT_ONITEM	(TCHT_ONITEMICON|TCHT_ONITEMLABEL)
#define TCS_FORCEICONLEFT	16
#define TCS_FORCELABELLEFT	32
#define TCS_TABS	0
#define TCS_BUTTONS	256
#define TCS_SINGLELINE	0
#define TCS_MULTILINE	512
#define TCS_RIGHTJUSTIFY	0
#define TCS_FIXEDWIDTH	1024
#define TCS_RAGGEDRIGHT	2048
#define TCS_FOCUSONBUTTONDOWN	0x1000
#define TCS_OWNERDRAWFIXED	0x2000
#define TCS_TOOLTIPS	0x4000
#define TCS_FOCUSNEVER	0x8000
#define TCIF_TEXT	1
#define TCIF_IMAGE	2
#define TCIF_RTLREADING	4
#define TCIF_PARAM	8
#define TCM_FIRST	0x1300
#define TCM_GETIMAGELIST	(TCM_FIRST+2)
#define TCM_SETIMAGELIST	(TCM_FIRST+3)
#define TCM_GETITEMCOUNT	(TCM_FIRST+4)
#define TCM_GETITEMA	(TCM_FIRST+5)
#define TCM_GETITEMW	(TCM_FIRST+60)
#define TCM_SETITEMA	(TCM_FIRST+6)
#define TCM_SETITEMW	(TCM_FIRST+61)
#define TCM_INSERTITEMA	(TCM_FIRST+7)
#define TCM_INSERTITEMW	(TCM_FIRST+62)
#define TCM_DELETEITEM	(TCM_FIRST+8)
#define TCM_DELETEALLITEMS	(TCM_FIRST+9)
#define TCM_GETITEMRECT	(TCM_FIRST+10)
#define TCM_GETCURSEL	(TCM_FIRST+11)
#define TCM_SETCURSEL	(TCM_FIRST+12)
#define TCM_HITTEST	(TCM_FIRST+13)
#define TCM_SETITEMEXTRA	(TCM_FIRST+14)
#define TCM_ADJUSTRECT	(TCM_FIRST+40)
#define TCM_SETITEMSIZE	(TCM_FIRST+41)
#define TCM_REMOVEIMAGE	(TCM_FIRST+42)
#define TCM_SETPADDING	(TCM_FIRST+43)
#define TCM_GETROWCOUNT	(TCM_FIRST+44)
#define TCM_GETTOOLTIPS	(TCM_FIRST+45)
#define TCM_SETTOOLTIPS	(TCM_FIRST+46)
#define TCM_GETCURFOCUS	(TCM_FIRST+47)
#define TCM_SETCURFOCUS	(TCM_FIRST+48)
#define TCN_KEYDOWN	TCN_FIRST
#define TCN_SELCHANGE	(TCN_FIRST-1)
#define TCN_SELCHANGING	(TCN_FIRST-2)
#define NM_OUTOFMEMORY (NM_FIRST-1)
#define NM_CLICK (NM_FIRST-2)
#define NM_DBLCLK (NM_FIRST-3)
#define NM_RETURN (NM_FIRST-4)
#define NM_RCLICK (NM_FIRST-5)
#define NM_RDBLCLK (NM_FIRST-6)
#define NM_SETFOCUS (NM_FIRST-7)
#define NM_KILLFOCUS (NM_FIRST-8)
#define SBARS_SIZEGRIP 256

#ifndef RC_INVOKED
typedef struct _COLORMAP {
	COLORREF from;
	COLORREF to;
} COLORMAP,*LPCOLORMAP;
typedef struct {
	UINT uNotification;
	HWND hWnd;
	POINT ptCursor;
} DRAGLISTINFO,*LPDRAGLISTINFO;
typedef struct _TBBUTTON {
	int iBitmap;
	int idCommand;
	BYTE fsState;
	BYTE fsStyle;
	BYTE bReserved[2];
	DWORD dwData;
	int iString;
} TBBUTTON,*PTBBUTTON,*LPTBBUTTON;
typedef const TBBUTTON *LPCTBBUTTON;
typedef struct {
	NMHDR hdr;
	int iItem;
	TBBUTTON tbButton;
	int cchText;
	LPTSTR pszText;
} TBNOTIFY,*LPTBNOTIFY;
typedef struct {
	HKEY hkr;
	LPCTSTR pszSubKey;
	LPCTSTR pszValueName;
} TBSAVEPARAMS;
typedef struct _IMAGEINFO {
	HBITMAP hbmImage;
	HBITMAP hbmMask;
	int Unused1;
	int Unused2;
	RECT rcImage;
} IMAGEINFO;
DECLARE_HANDLE(HIMAGELIST);
typedef struct _HD_ITEMA {
	UINT mask;
	int cxy;
	LPSTR pszText;
	HBITMAP hbm;
	int cchTextMax;
	int fmt;
	LPARAM lParam;
} HD_ITEMA;
typedef struct _HD_ITEMW {
	UINT mask;
	int cxy;
	LPWSTR pszText;
	HBITMAP hbm;
	int cchTextMax;
	int fmt;
	LPARAM lParam;
} HD_ITEMW;
typedef struct _HD_LAYOUT {
	RECT *prc;
	WINDOWPOS *pwpos;
} HD_LAYOUT;
typedef struct _HD_HITTESTINFO {
	POINT pt;
	UINT flags;
	int iItem;
} HD_HITTESTINFO;
typedef struct _HD_NOTIFYA {
	NMHDR hdr;
	int iItem;
	int iButton;
	HD_ITEMA *pitem;
} HD_NOTIFYA;
typedef struct _HD_NOTIFYW {
	NMHDR hdr;
	int iItem;
	int iButton;
	HD_ITEMW *pitem;
} HD_NOTIFYW;
typedef struct tagTBADDBITMAP {
	HINSTANCE hInst;
	UINT nID;
} TBADDBITMAP,*LPTBADDBITMAP;
typedef struct tagTBSAVEPARAMSA {
	HKEY hkr;
	LPCSTR pszSubKey;
	LPCSTR pszValueName;
} TBSAVEPARAMSA;
typedef struct tagTBSAVEPARAMSW {
	HKEY hkr;
	LPCWSTR pszSubKey;
	LPCWSTR pszValueName;
} TBSAVEPARAMSW;
typedef struct {
	HINSTANCE hInstOld;
	UINT nIDOld;
	HINSTANCE hInstNew;
	UINT nIDNew;
	int nButtons;
} TBREPLACEBITMAP,*LPTBREPLACEBITMAP;
typedef struct tagTBNOTIFYA {
	NMHDR hdr;
	int iItem;
	TBBUTTON tbButton;
	int cchText;
	LPSTR pszText;
} TBNOTIFYA,*LPTBNOTIFYA;
typedef struct tagTBNOTIFYW {
	NMHDR hdr;
	int iItem;
	TBBUTTON tbButton;
	int cchText;
	LPWSTR pszText;
} TBNOTIFYW,*LPTBNOTIFYW;
typedef struct tagTOOLINFOA {
	UINT cbSize;
	UINT uFlags;
	HWND hwnd;
	UINT uId;
	RECT rect;
	HINSTANCE hinst;
	LPSTR lpszText;
} TOOLINFOA,*PTOOLINFOA,*LPTOOLINFOA;
typedef struct tagTOOLINFOW {
	UINT cbSize;
	UINT uFlags;
	HWND hwnd;
	UINT uId;
	RECT rect;
	HINSTANCE hinst;
	LPWSTR lpszText;
} TOOLINFOW,*PTOOLINFOW,*LPTOOLINFOW;
typedef struct _TT_HITTESTINFOA {
	HWND hwnd;
	POINT pt;
	TOOLINFOA ti;
} TTHITTESTINFOA,*LPHITTESTINFOA;
typedef struct _TT_HITTESTINFOW {
	HWND hwnd;
	POINT pt;
	TOOLINFOW ti;
} TTHITTESTINFOW,*LPHITTESTINFOW;
typedef struct tagTOOLTIPTEXTA {
	NMHDR hdr;
	LPSTR lpszText;
	char szText[80];
	HINSTANCE hinst;
	UINT uFlags;
} TOOLTIPTEXTA,*LPTOOLTIPTEXTA;
typedef struct tagTOOLTIPTEXTW {
	NMHDR hdr;
	LPWSTR lpszText;
	WCHAR szText[80];
	HINSTANCE hinst;
	UINT uFlags;
} TOOLTIPTEXTW,*LPTOOLTIPTEXTW;
typedef struct _UDACCEL {
	UINT nSec;
	UINT nInc;
} UDACCEL,*LPUDACCEL;
typedef struct _NM_UPDOWN {
	NMHDR hdr;
	int iPos;
	int iDelta;
} NM_UPDOWN,*LPNM_UPDOWN;
typedef struct _LV_ITEMA {
	UINT mask;
	int iItem;
	int iSubItem;
	UINT state;
	UINT stateMask;
	LPSTR pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
} LV_ITEMA;
typedef struct _LV_ITEMW {
	UINT mask;
	int iItem;
	int iSubItem;
	UINT state;
	UINT stateMask;
	LPWSTR pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
} LV_ITEMW;
typedef struct _LV_FINDINFOA {
	UINT flags;
	LPCSTR psz;
	LPARAM lParam;
	POINT pt;
	UINT vkDirection;
} LV_FINDINFOA;
typedef struct _LV_FINDINFOW {
	UINT flags;
	LPCWSTR psz;
	LPARAM lParam;
	POINT pt;
	UINT vkDirection;
} LV_FINDINFOW;
typedef struct _LV_HITTESTINFO {
	POINT pt;
	UINT flags;
	int iItem;
} LV_HITTESTINFO;
typedef struct _LV_COLUMNA {
	UINT mask;
	int fmt;
	int cx;
	LPSTR pszText;
	int cchTextMax;
	int iSubItem;
} LV_COLUMNA;
typedef struct _LV_COLUMNW {
	UINT mask;
	int fmt;
	int cx;
	LPWSTR pszText;
	int cchTextMax;
	int iSubItem;
} LV_COLUMNW;
typedef int(CALLBACK *PFNLVCOMPARE)(LPARAM,LPARAM,LPARAM);
typedef struct _NM_LISTVIEW {
	NMHDR hdr;
	int iItem;
	int iSubItem;
	UINT uNewState;
	UINT uOldState;
	UINT uChanged;
	POINT ptAction;
	LPARAM lParam;
} NM_LISTVIEW,*LPNM_LISTVIEW;
typedef struct _LV_DISPINFOA {
	NMHDR hdr;
	LV_ITEMA item;
} LV_DISPINFOA;
typedef struct _LV_DISPINFOW {
	NMHDR hdr;
	LV_ITEMW item;
} LV_DISPINFOW;
typedef struct _LV_KEYDOWN {
	NMHDR hdr;
	WORD wVKey;
	UINT flags;
} LV_KEYDOWN;
DECLARE_HANDLE(HTREEITEM);
typedef struct _TV_ITEMA {
	UINT mask;
	HTREEITEM hItem;
	UINT state;
	UINT stateMask;
	LPSTR pszText;
	int cchTextMax;
	int iImage;
	int iSelectedImage;
	int cChildren;
	LPARAM lParam;
} TV_ITEMA,*LPTV_ITEMA;
typedef struct _TV_ITEMW {
	UINT mask;
	HTREEITEM hItem;
	UINT state;
	UINT stateMask;
	LPWSTR pszText;
	int cchTextMax;
	int iImage;
	int iSelectedImage;
	int cChildren;
	LPARAM lParam;
} TV_ITEMW,*LPTV_ITEMW;
typedef struct _TV_INSERTSTRUCTA {
	HTREEITEM hParent;
	HTREEITEM hInsertAfter;
	TV_ITEMA item;
} TV_INSERTSTRUCTA,*LPTV_INSERTSTRUCTA;
typedef struct _TV_INSERTSTRUCTW {
	HTREEITEM hParent;
	HTREEITEM hInsertAfter;
	TV_ITEMW item;
} TV_INSERTSTRUCTW,*LPTV_INSERTSTRUCTW;
typedef struct _TV_HITTESTINFO {
	POINT pt;
	UINT flags;
	HTREEITEM hItem;
} TV_HITTESTINFO,*LPTV_HITTESTINFO;
typedef int(CALLBACK *PFNTVCOMPARE)(LPARAM,LPARAM,LPARAM);
typedef struct _TV_SORTCB {
	HTREEITEM hParent;
	PFNTVCOMPARE lpfnCompare;
	LPARAM lParam;
} TV_SORTCB,*LPTV_SORTCB;
typedef struct _NM_TREEVIEWA {
	NMHDR hdr;
	UINT action;
	TV_ITEMA itemOld;
	TV_ITEMA itemNew;
	POINT ptDrag;
} NM_TREEVIEWA,*LPNM_TREEVIEWA;
typedef struct _NM_TREEVIEWW {
	NMHDR hdr;
	UINT action;
	TV_ITEMW itemOld;
	TV_ITEMW itemNew;
	POINT ptDrag;
} NM_TREEVIEWW,*LPNM_TREEVIEWW;
typedef struct _TV_DISPINFOA {
	NMHDR hdr;
	TV_ITEMA item;
} TV_DISPINFOA;
typedef struct _TV_DISPINFOW {
	NMHDR hdr;
	TV_ITEMW item;
} TV_DISPINFOW;
typedef struct _TV_KEYDOWN {
	NMHDR hdr;
	WORD wVKey;
	UINT flags;
} TV_KEYDOWN;
typedef struct _TC_ITEMHEADERA {
	UINT mask;
	UINT lpReserved1;
	UINT lpReserved2;
	LPSTR pszText;
	int cchTextMax;
	int iImage;
} TC_ITEMHEADERA;
typedef struct _TC_ITEMHEADERW {
	UINT mask;
	UINT lpReserved1;
	UINT lpReserved2;
	LPWSTR pszText;
	int cchTextMax;
	int iImage;
} TC_ITEMHEADERW;
typedef struct _TC_ITEMA {
	UINT mask;
	UINT lpReserved1;
	UINT lpReserved2;
	LPSTR pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
} TC_ITEMA;
typedef struct _TC_ITEMW {
	UINT mask;
	UINT lpReserved1;
	UINT lpReserved2;
	LPWSTR pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
} TC_ITEMW;
typedef struct _TC_HITTESTINFO {
	POINT pt;
	UINT flags;
} TC_HITTESTINFO,*LPTC_HITTESTINFO;
typedef struct _TC_KEYDOWN {
	NMHDR hdr;
	WORD wVKey;
	UINT flags;
} TC_KEYDOWN;

#define INDEXTOOVERLAYMASK(i) ((i)<<8)
#define INDEXTOSTATEIMAGEMASK(i) ((i)<<12)
#define HANDLE_WM_NOTIFY(h,w,l,f) (f)((h),(int)(w),(NMHDR*)(l))
#define FORWARD_WM_NOTIFY(h,i,p,f) (LRESULT)(f)((h),WM_NOTIFY,(WPARAM)(int)(i),(LPARAM)(NMHDR*)(p))
#define Animate_Create(w,i,s,hI) CreateWindow(ANIMATE_CLASS,NULL,s,0,0,0,0,w,(HMENU)(i),hI,NULL)
#define Animate_Open(w,f) (BOOL)SendMessage(w,ACM_OPEN,0,(LPARAM)f)
#define Animate_Play(w,f,t,r) (BOOL)SendMessage(w,ACM_PLAY,(r),(LPARAM)MAKELONG(f,t))
#define Animate_Stop(w)	(BOOL)SendMessage(w,ACM_STOP,0,0)
#define Animate_Close(w)	Animate_Open(w,NULL)
#define Animate_Seek(w,f)	Animate_Play(w,f,f,1)
HBITMAP WINAPI CreateMappedBitmap(HINSTANCE,int,UINT,LPCOLORMAP,int);
HWND WINAPI CreateStatusWindowA(LONG,LPCSTR,HWND,UINT);
HWND WINAPI CreateStatusWindowW(LONG,LPCWSTR,HWND,UINT);
HWND WINAPI CreateToolbarEx(HWND,DWORD,UINT,int,HINSTANCE,UINT,LPCTBBUTTON,int,int,int,int,int,UINT);
HWND WINAPI CreateUpDownControl(DWORD,int,int,int,int,HWND,int,HINSTANCE,HWND,int,int,int);
void WINAPI DrawInsert(HWND,HWND,int);
void WINAPI DrawStatusTextA(HDC,LPRECT,LPCSTR,UINT);
void WINAPI DrawStatusTextW(HDC,LPRECT,LPCWSTR,UINT);
void WINAPI GetEffectiveClientRect(HWND,LPRECT,LPINT);
#define Header_GetItemCount(w) (int)SendMessage((w),HDM_GETITEMCOUNT,0,0)
#define Header_InsertItem(w,i,phdi) (int)SendMessage((hwndHD),HDM_INSERTITEM,(WPARAM)(int)(i),(LPARAM)(const HD_ITEM*)(phdi))
#define Header_DeleteItem(w,i) (BOOL)SendMessage((w),HDM_DELETEITEM,(WPARAM)(int)(i),0)
#define Header_GetItem(w,i,phdi) (BOOL)SendMessage((w),HDM_GETITEM,(WPARAM)(int)(i),(LPARAM)(HD_ITEM*)(phdi))
#define Header_SetItem(w,i,phdi) (BOOL)SendMessage((hwndHD),HDM_SETITEM,(WPARAM)(int)(i),(LPARAM)(const HD_ITEM*)(phdi))
#define Header_Layout(w,l) (BOOL)SendMessage((w),HDM_LAYOUT,0,(LPARAM)(HD_LAYOUT*)(l))
int WINAPI ImageList_Add(HIMAGELIST,HBITMAP,HBITMAP);
#define ImageList_AddIcon(l,i) ImageList_ReplaceIcon(l,-1,i)
int WINAPI ImageList_AddMasked(HIMAGELIST,HBITMAP,COLORREF);
BOOL WINAPI ImageList_BeginDrag(HIMAGELIST,int,int,int);
HIMAGELIST WINAPI ImageList_Create(int,int,UINT,int,int);
BOOL WINAPI ImageList_Destroy(HIMAGELIST);
BOOL WINAPI ImageList_DragEnter(HWND,int,int);
BOOL WINAPI ImageList_DragLeave(HWND);
BOOL WINAPI ImageList_DragMove(int,int);
BOOL WINAPI ImageList_DragShowNolock(BOOL);
BOOL WINAPI ImageList_Draw(HIMAGELIST,int,HDC,int,int,UINT);
BOOL WINAPI ImageList_DrawEx(HIMAGELIST,int,HDC,int,int,int,int,COLORREF,COLORREF,UINT);
void WINAPI ImageList_EndDrag(VOID);
#define ImageList_ExtractIcon(h,l,i) ImageList_GetIcon(l,i,0)
COLORREF WINAPI ImageList_GetBkColor(HIMAGELIST);
HIMAGELIST WINAPI ImageList_GetDragImage(LPPOINT,LPPOINT);
HICON WINAPI ImageList_GetIcon(HIMAGELIST,int,UINT);
BOOL WINAPI ImageList_GetIconSize(HIMAGELIST,int*,int*);
int WINAPI ImageList_GetImageCount(HIMAGELIST);
BOOL WINAPI ImageList_GetImageInfo(HIMAGELIST,int,IMAGEINFO*);
#define ImageList_LoadBitmap(h,l,x,G,M) ImageList_LoadImage(h,l,x,G,M,IMAGE_BITMAP,0)
HIMAGELIST WINAPI ImageList_LoadImageA(HINSTANCE,LPCSTR,int,int,COLORREF,UINT,UINT);
HIMAGELIST WINAPI ImageList_LoadImageW(HINSTANCE,LPCWSTR,int,int,COLORREF,UINT,UINT);
HIMAGELIST WINAPI ImageList_Merge(HIMAGELIST,int,HIMAGELIST,int,int,int);
BOOL WINAPI ImageList_Remove(HIMAGELIST,int);
#define ImageList_RemoveAll(l) ImageList_Remove(l,-1)
BOOL WINAPI ImageList_Replace(HIMAGELIST,int,HBITMAP,HBITMAP);
int WINAPI ImageList_ReplaceIcon(HIMAGELIST,int,HICON);
COLORREF WINAPI ImageList_SetBkColor(HIMAGELIST,COLORREF);
BOOL WINAPI ImageList_SetDragCursorImage(HIMAGELIST,int,int,int);
BOOL WINAPI ImageList_SetIconSize(HIMAGELIST,int,int);
BOOL WINAPI ImageList_SetOverlayImage(HIMAGELIST,int,int);
#ifdef _OBJIDL_H
HIMAGELIST WINAPI ImageList_Read(LPSTREAM);
BOOL WINAPI ImageList_Write(HIMAGELIST,LPSTREAM);
#endif
void WINAPI InitCommonControls(void);
int WINAPI LBItemFromPt(HWND,POINT,BOOL);
#define ListView_GetBkColor(w) (COLORREF)SendMessage((w),LVM_GETBKCOLOR,0,0)
#define ListView_GetImageList(w,i) (HIMAGELIST)SendMessage((w),LVM_GETIMAGELIST,(i),0)
#define ListView_GetItemCount(w) (int)SendMessage((w),LVM_GETITEMCOUNT,0,0)
#define ListView_GetItem(w,i) (BOOL)SendMessage((w),LVM_GETITEM,0,(LPARAM)(i))
#define ListView_SetBkColor(w,c) (BOOL)SendMessage((w),LVM_SETBKCOLOR,0,(LPARAM)c)
#define ListView_SetImageList(w,h,i) (HIMAGELIST)(UINT)SendMessage((w),LVM_SETIMAGELIST,(i),(LPARAM)(h))
#define ListView_SetItem(w,i) (BOOL)SendMessage((w),LVM_SETITEM,0,(LPARAM)(const LV_ITEM*)(i))
#define ListView_InsertItem(w,i) (int)SendMessage((w),LVM_INSERTITEM,0,(LPARAM)(const LV_ITEM*)(i))
#define ListView_DeleteItem(w,i) (BOOL)SendMessage((w),LVM_DELETEITEM,i,0)
#define ListView_DeleteAllItems(w) (BOOL)SendMessage((w),LVM_DELETEALLITEMS,0,0)
#define ListView_GetCallbackMask(w) (BOOL)SendMessage((w),LVM_GETCALLBACKMASK,0,0)
#define ListView_SetCallbackMask(w,m) (BOOL)SendMessage((w),LVM_SETCALLBACKMASK,m,0)
#define ListView_GetNextItem(w,i,f) (int)SendMessage((w),LVM_GETNEXTITEM,i,MAKELPARAM((f),0))
#define ListView_FindItem(w,i,p) (int)SendMessage((w), LVM_FINDITEM,i,(LPARAM)(const LV_FINDINFO*)(p))
#define ListView_GetItemRect(w,i,p,c) (BOOL)SendMessage((w),LVM_GETITEMRECT,i,((p)?(((LPRECT)(p))->left=(c),(LPARAM)(LPRECT)(p)):0))
#define ListView_SetItemPosition(w,i,x,y) (BOOL)SendMessage((w),LVM_SETITEMPOSITION,i,MAKELPARAM(x,y))
#define ListView_GetItemPosition(w,i,p) (BOOL)SendMessage((w),LVM_GETITEMPOSITION,i,(LPARAM)p)
#define ListView_GetItemSpacing(w,f) (DWORD)SendMessage((w),LVM_GETITEMSPACING,f,0)
#define ListView_GetStringWidth(w,s) (int)SendMessage((w),LVM_GETSTRINGWIDTH,0,(LPARAM)s)
#define ListView_HitTest(w,p) (int)SendMessage((w),LVM_HITTEST,0,(LPARAM)(LV_HITTESTINFO*)(p))
#define ListView_EnsureVisible(w,i,f) (BOOL)SendMessage((w),LVM_ENSUREVISIBLE,i,MAKELPARAM((f),0))
#define ListView_Scroll(w,dx,dy) (BOOL)SendMessage((w),LVM_SCROLL,dx,dy)
#define ListView_RedrawItems(w,f,l) (BOOL)SendMessage((w),LVM_REDRAWITEMS,f,l)
#define ListView_Arrange(w,c) (BOOL)SendMessage((w),LVM_ARRANGE,c,0)
#define ListView_EditLabel(w,i) (HWND)SendMessage((w),LVM_EDITLABEL,i,0)
#define ListView_GetEditControl(w) (HWND)SendMessage((w),LVM_GETEDITCONTROL,0,0)
#define ListView_GetColumn(w,i,p) (BOOL)SendMessage((w),LVM_GETCOLUMN,i,(LPARAM)(LV_COLUMN*)(p))
#define ListView_SetColumn(w,i,p) (BOOL)SendMessage((w),LVM_SETCOLUMN,i,(LPARAM)(const LV_COLUMN*)(p))
#define ListView_InsertColumn(w,i,p) (int)SendMessage((w),LVM_INSERTCOLUMN,i,(LPARAM)(const LV_COLUMN*)(p))
#define ListView_DeleteColumn(w,i) (BOOL)SendMessage((w),LVM_DELETECOLUMN,i,0)
#define ListView_GetColumnWidth(w,i) (int)SendMessage((w),LVM_GETCOLUMNWIDTH,i,0)
#define ListView_SetColumnWidth(w,i,x) (BOOL)SendMessage((w),LVM_SETCOLUMNWIDTH,i,MAKELPARAM((x),0))
#define ListView_CreateDragImage(w,i,p) (HIMAGELIST)SendMessage((w),LVM_CREATEDRAGIMAGE,i,(LPARAM)(LPPOINT)(p))
#define ListView_GetViewRect(w,p) (BOOL)SendMessage((w),LVM_GETVIEWRECT,0,(LPARAM)(LPRECT)(p))
#define ListView_GetTextColor(w) (COLORREF)SendMessage((w),LVM_GETTEXTCOLOR,0,0)
#define ListView_SetTextColor(w,c) (BOOL)SendMessage((w),LVM_SETTEXTCOLOR,0,(LPARAM)(COLORREF)(c))
#define ListView_GetTextBkColor(w) (COLORREF)SendMessage((w),LVM_GETTEXTBKCOLOR,0,0)
#define ListView_SetTextBkColor(w,c) (BOOL)SendMessage((w),LVM_SETTEXTBKCOLOR,0,(LPARAM)(COLORREF)(c))
#define ListView_GetTopIndex(w) (int)SendMessage((w),LVM_GETTOPINDEX,0,0)
#define ListView_GetCountPerPage(w) (int)SendMessage((w),LVM_GETCOUNTPERPAGE,0,0)
#define ListView_GetOrigin(w,p) (BOOL)SendMessage((w),LVM_GETORIGIN,0,(LPARAM)(POINT*)(p))
#define ListView_GetOrigin(w,p) (BOOL)SendMessage((w),LVM_GETORIGIN,0,(LPARAM)(POINT*)(p))
#define ListView_Update(w,i) (BOOL)SendMessage((w),LVM_UPDATE,i,0)
#define ListView_SetItemState(w,i,d,m) \
{ \
	LV_ITEM _lvi;\
	_lvi.stateMask=m;\
	_lvi.state=d;\
	SendMessage((w),LVM_SETITEMSTATE,i,(LPARAM)(LV_ITEM*)&_lvi);\
}
#define ListView_GetItemState(w,i,m) (UINT)SendMessage((w),LVM_GETITEMSTATE,i,m)
#define ListView_GetItemText(w,i,iS,s,n) \
{ \
	LV_ITEM _lvi;\
	_lvi.iSubItem=iS;\
	_lvi.cchTextMax=n;\
	_lvi.pszText=s;\
	SendMessage((w),LVM_GETITEMTEXT,i,(LPARAM)(LV_ITEM*)&_lvi);\
}
#define ListView_SetItemText(w,i,iS,s) \
{ \
	LV_ITEM _lvi;\
	_lvi.iSubItem=iS;\
	_lvi.pszText=s;\
	SendMessage((w),LVM_SETITEMTEXT,i,(LPARAM)(LV_ITEM*)&_lvi);\
}
#define ListView_SetItemCount(w,n) SendMessage((w),LVM_SETITEMCOUNT,n,0)
#define ListView_SortItems(w,f,l) (BOOL)SendMessage((w),LVM_SORTITEMS,l,(LPARAM)f)
#define ListView_SetItemPosition32(w,i,x,y) \
{ \
	POINT p={x,y}; \
	SendMessage((w),LVM_SETITEMPOSITION32,i,(LPARAM)&p);\
}
#define ListView_GetSelectedCount(w) (UINT)SendMessage((w),LVM_GETSELECTEDCOUNT,0,0)

BOOL WINAPI MakeDragList(HWND);
void WINAPI MenuHelp(UINT,WPARAM,LPARAM,HMENU,HINSTANCE,HWND,PUINT);
BOOL WINAPI ShowHideMenuCtl(HWND,UINT,PINT);
#define TabCtrl_GetItem(w,i,p) (BOOL)SendMessage((w),TCM_GETITEM,i,(LPARAM)(TC_ITEM*)(p))
#define TabCtrl_SetItem(w,i,p) (BOOL)SendMessage((w),TCM_SETITEM,i,(LPARAM)(TC_ITEM*)(p))
#define TabCtrl_InsertItem(w,i,p) (int)SendMessage((w),TCM_INSERTITEM,i,(LPARAM)(const TC_ITEM*)(p))
#define TabCtrl_DeleteItem(w,i) (BOOL)SendMessage((w),TCM_DELETEITEM,i,0)
#define TabCtrl_DeleteAllItems(w) (BOOL)SendMessage((w),TCM_DELETEALLITEMS,0,0)
#define TabCtrl_GetItemRect(w,i,p) (BOOL)SendMessage((w),TCM_GETITEMRECT,i,(LPARAM)(LPRECT)(p))
#define TabCtrl_GetCurSel(w) (int)SendMessage((w),TCM_GETCURSEL,0,0)
#define TabCtrl_SetCurSel(w,i) (int)SendMessage((w),TCM_SETCURSEL,i,0)
#define TabCtrl_HitTest(w,p) (int)SendMessage((w),TCM_HITTEST,0,(LPARAM)(TC_HITTESTINFO*)(p))
#define TabCtrl_SetItemExtra(w,c) (BOOL)SendMessage((w),TCM_SETITEMEXTRA,c,0)
#define TabCtrl_AdjustRect(w,b,p) (int)SendMessage((w),TCM_ADJUSTRECT,b,(LPARAM)(LPRECT)p)
#define TabCtrl_SetItemSize(w,x,y) (DWORD)SendMessage((w),TCM_SETITEMSIZE,0,MAKELPARAM(x,y))
#define TabCtrl_RemoveImage(w,i) (void)SendMessage((w),TCM_REMOVEIMAGE,i,0)
#define TabCtrl_SetPadding(w,x,y) (void)SendMessage((w),TCM_SETPADDING,0,MAKELPARAM(x,y))
#define TabCtrl_GetRowCount(w) (int)SendMessage((w),TCM_GETROWCOUNT,0,0)
#define TabCtrl_GetToolTips(w) (HWND)SendMessage((w),TCM_GETTOOLTIPS,0,0)
#define TabCtrl_SetToolTips(w,t) (void)SendMessage((w),TCM_SETTOOLTIPS,(WPARAM)t,0)
#define TabCtrl_GetCurFocus(w) (int)SendMessage((w),TCM_GETCURFOCUS,0,0)
#define TabCtrl_SetCurFocus(w,i) (void)SendMessage((w),TCM_SETCURFOCUS,i,0)
#define TabCtrl_SetImageList(w,h) (HIMAGELIST)SendMessage((w),TCM_SETIMAGELIST,0,(LPARAM)(UINT)(h))
#define TabCtrl_GetItemCount(w) (int)SendMessage((w),TCM_GETITEMCOUNT,0,0)
#define TreeView_InsertItem(w,i) (HTREEITEM)SendMessage((w),TVM_INSERTITEM,0,(LPARAM)(LPTV_INSERTSTRUCT)(i))
#define TreeView_DeleteItem(w,i) (BOOL)SendMessage((w),TVM_DELETEITEM,0,(LPARAM)(HTREEITEM)(i))
#define TreeView_DeleteAllItems(w) (BOOL)SendMessage((w),TVM_DELETEITEM,0,(LPARAM)TVI_ROOT)
#define TreeView_Expand(w,i,c) (BOOL)SendMessage((w),TVM_EXPAND,c,(LPARAM)(HTREEITEM)(i))
#define TreeView_GetItemRect(w,i,p,c) (*(HTREEITEM*)p=(i),(BOOL)SendMessage((w),TVM_GETITEMRECT,c,(LPARAM)(LPRECT)(p)))
#define TreeView_GetCount(w) (UINT)SendMessage((w),TVM_GETCOUNT,0,0)
#define TreeView_GetIndent(w) (UINT)SendMessage((w),TVM_GETINDENT,0,0)
#define TreeView_SetIndent(w,i) (BOOL)SendMessage((w),TVM_SETINDENT,indent,0)
#define TreeView_GetImageList(w,i) (HIMAGELIST)SendMessage((w),TVM_GETIMAGELIST,i,0)
#define TreeView_SetImageList(w,h,i) (HIMAGELIST)SendMessage((w),TVM_SETIMAGELIST,i,(LPARAM)(HIMAGELIST)(h))
#define TreeView_GetNextItem(w,i,c) (HTREEITEM)SendMessage((w),TVM_GETNEXTITEM,c,(LPARAM)(HTREEITEM)(i))
#define TreeView_GetChild(w,i)	TreeView_GetNextItem(w,i,TVGN_CHILD)
#define TreeView_GetNextSibling(w,i)	TreeView_GetNextItem(w,i,TVGN_NEXT)
#define TreeView_GetPrevSibling(w,i)	TreeView_GetNextItem(w,i,TVGN_PREVIOUS)
#define TreeView_GetParent(w,i)	TreeView_GetNextItem(w,i,TVGN_PARENT)
#define TreeView_GetFirstVisible(w)	TreeView_GetNextItem(w,NULL,TVGN_FIRSTVISIBLE)
#define TreeView_GetNextVisible(w,i)	TreeView_GetNextItem(w,i,TVGN_NEXTVISIBLE)
#define TreeView_GetPrevVisible(w,i)	TreeView_GetNextItem(w,i,TVGN_PREVIOUSVISIBLE)
#define TreeView_GetSelection(w)	TreeView_GetNextItem(w,NULL,TVGN_CARET)
#define TreeView_GetDropHilight(w)	TreeView_GetNextItem(w,NULL,TVGN_DROPHILITE)
#define TreeView_GetRoot(w)	TreeView_GetNextItem(w,NULL,TVGN_ROOT)
#define TreeView_Select(w,i,c) (HTREEITEM)SendMessage((w),TVM_SELECTITEM,c,(LPARAM)(HTREEITEM)(i))
#define TreeView_SelectItem(w,i)	TreeView_Select(w,i,TVGN_CARET)
#define TreeView_SelectDropTarget(w,i)	TreeView_Select(w,i,TVGN_DROPHILITE)
#define TreeView_SelectSetFirstVisible(w,i)	TreeView_Select(w,i,TVGN_FIRSTVISIBLE)
#define TreeView_GetItem(w,i) (BOOL)SendMessage((w),TVM_GETITEM,0,(LPARAM)(TV_ITEM*)(i))
#define TreeView_SetItem(w,i) (BOOL)SendMessage((w),TVM_SETITEM,0,(LPARAM)(const TV_ITEM*)(i))
#define TreeView_EditLabel(w,i) (HWND)SendMessage((w),TVM_EDITLABEL,0,(LPARAM)(HTREEITEM)(i))
#define TreeView_GetEditControl(w) (HWND)SendMessage((w),TVM_GETEDITCONTROL,0,0)
#define TreeView_GetVisibleCount(w) (UINT)SendMessage((w),TVM_GETVISIBLECOUNT,0,0)
#define TreeView_HitTest(w,p) (HTREEITEM)SendMessage((w),TVM_HITTEST,0,(LPARAM)(LPTV_HITTESTINFO)(p))
#define TreeView_CreateDragImage(w,i) (HIMAGELIST)SendMessage((w),TVM_CREATEDRAGIMAGE,0,(LPARAM)(HTREEITEM)(i))
#define TreeView_SortChildren(w,i,r) (BOOL)SendMessage((w),TVM_SORTCHILDREN,r,(LPARAM)(HTREEITEM)(i))
#define TreeView_EnsureVisible(w,i) (BOOL)SendMessage((w),TVM_ENSUREVISIBLE,0,(LPARAM)(HTREEITEM)(i))
#define TreeView_SortChildrenCB(w,s,r) (BOOL)SendMessage((w),TVM_SORTCHILDRENCB,r,(LPARAM)(LPTV_SORTCB)(s))
#define TreeView_EndEditLabelNow(w,f) (BOOL)SendMessage((w),TVM_ENDEDITLABELNOW,f,0)
#define TreeView_GetISearchString(w,s) (BOOL)SendMessage((w),TVM_GETISEARCHSTRING,0,(LPARAM)s)

#ifdef UNICODE
#define ANIMATE_CLASS ANIMATE_CLASSW
#define HOTKEY_CLASS HOTKEY_CLASSW
#define PROGRESS_CLASS PROGRESS_CLASSW
#define STATUSCLASSNAME STATUSCLASSNAMEW
#define TOOLBARCLASSNAME TOOLBARCLASSNAMEW
#define TOOLTIPS_CLASS TOOLTIPS_CLASSW
#define TRACKBAR_CLASS TRACKBAR_CLASSW
#define UPDOWN_CLASS UPDOWN_CLASSW
#define WC_HEADER WC_HEADERW
#define WC_LISTVIEW WC_LISTVIEWW
#define WC_TABCONTROL WC_TABCONTROLW
#define WC_TREEVIEW WC_TREEVIEWW
typedef HD_ITEMW HD_ITEM;
typedef TOOLINFOW TOOLINFO,*PTOOLINFO,*LPTOOLINFO;
typedef TTHITTESTINFOW TTHITTESTINFO,*LPHITTESTINFO;
typedef TOOLTIPTEXTW TOOLTIPTEXT,*LPTOOLTIPTEXT;
typedef TV_ITEMW TV_ITEM,*LPTV_ITEM;
typedef TV_INSERTSTRUCTW TV_INSERTSTRUCT,*LPTV_INSERTSTRUCT;
typedef NM_TREEVIEWW NM_TREEVIEW,*LPNM_TREEVIEW;
#define ACM_OPEN ACM_OPENW
#define SB_GETTEXT	SB_GETTEXTW
#define SB_SETTEXT	SB_SETTEXTW
#define SB_GETTEXTLENGTH	SB_GETTEXTLENGTHW
#define STATUSCLASSNAME         STATUSCLASSNAMEW
#define WC_HEADER WC_HEADERW
#define HDM_INSERTITEM HDM_INSERTITEMW
#define HDM_GETITEM HDM_GETITEMW
#define HDM_SETITEM HDM_SETITEMW
#define HDN_ITEMCHANGING	HDN_ITEMCHANGINGW
#define HDN_ITEMCHANGED	HDN_ITEMCHANGEDW
#define HDN_ITEMCLICK	HDN_ITEMCLICKW
#define HDN_ITEMDBLCLICK	HDN_ITEMDBLCLICKW
#define HDN_DIVIDERDBLCLICK	HDN_DIVIDERDBLCLICKW
#define HDN_BEGINTRACK	HDN_BEGINTRACKW
#define HDN_ENDTRACK	HDN_ENDTRACKW
#define HDN_TRACK	HDN_TRACKW
#define HD_NOTIFY HD_NOTIFYW
#define TOOLBARCLASSNAME TOOLBARCLASSNAMEW
#define TBSAVEPARAMS TBSAVEPARAMSW
#define TB_GETBUTTONTEXT TB_GETBUTTONTEXTW
#define TB_SAVERESTORE TB_SAVERESTOREW
#define TB_ADDSTRING TB_ADDSTRINGW
#define TBN_GETBUTTONINFO TBN_GETBUTTONINFOW
#define TBNOTIFY TBNOTIFYW
#define LPTBNOTIFY LPTBNOTIFYW
#define TOOLTIPS_CLASS TOOLTIPS_CLASSW
#define TTM_ADDTOOL	TTM_ADDTOOLW
#define TTM_DELTOOL	TTM_DELTOOLW
#define TTM_NEWTOOLRECT	TTM_NEWTOOLRECTW
#define TTM_GETTOOLINFO	TTM_GETTOOLINFOW
#define TTM_SETTOOLINFO	TTM_SETTOOLINFOW
#define TTM_HITTEST	TTM_HITTESTW
#define TTM_GETTEXT	TTM_GETTEXTW
#define TTM_UPDATETIPTEXT	TTM_UPDATETIPTEXTW
#define TTM_ENUMTOOLS	TTM_ENUMTOOLSW
#define TTM_GETCURRENTTOOL	TTM_GETCURRENTTOOLW
#define TTN_NEEDTEXT TTN_NEEDTEXTW
#define SB_GETTEXT	SB_GETTEXTW
#define SB_SETTEXT	SB_SETTEXTW
#define SB_GETTEXTLENGTH	SB_GETTEXTLENGTHW
#define TRACKBAR_CLASS TRACKBAR_CLASSW
#define UPDOWN_CLASS UPDOWN_CLASSW
#define PROGRESS_CLASS PROGRESS_CLASSW
#define HOTKEY_CLASS HOTKEY_CLASSW
#define WC_LISTVIEW WC_LISTVIEWW
#define LV_ITEM LV_ITEMW
#define LPSTR_TEXTCALLBACK LPSTR_TEXTCALLBACKW
#define LVM_GETITEM	LVM_GETITEMW
#define LVM_SETITEM LVM_SETITEMW
#define LVM_INSERTITEM LVM_INSERTITEMW
#define LV_FINDINFO LV_FINDINFOW
#define LVM_FINDITEM LVM_FINDITEMW
#define LVM_GETSTRINGWIDTH LVM_GETSTRINGWIDTHW
#define LVM_EDITLABEL LVM_EDITLABELW
#define LV_COLUMN LV_COLUMNW
#define LVM_GETCOLUMN LVM_GETCOLUMNW
#define LVM_SETCOLUMN LVM_SETCOLUMNW
#define LVM_INSERTCOLUMN LVM_INSERTCOLUMNW
#define LVM_GETITEMTEXT LVM_GETITEMTEXTW
#define LVM_SETITEMTEXT LVM_SETITEMTEXTW
#define LVM_GETISEARCHSTRING LVM_GETISEARCHSTRINGW
#define LVN_BEGINLABELEDIT LVN_BEGINLABELEDITW
#define LVN_ENDLABELEDIT LVN_ENDLABELEDITW
#define LVN_GETDISPINFO LVN_GETDISPINFOW
#define LVN_SETDISPINFO LVN_SETDISPINFOW
#define LV_DISPINFO LV_DISPINFOW
#define WC_TREEVIEW WC_TREEVIEWW
#define TVM_INSERTITEM TVM_INSERTITEMW
#define TVM_GETITEM TVM_GETITEMW
#define TVM_SETITEM TVM_SETITEMW
#define TVM_EDITLABEL TVM_EDITLABELW
#define TVM_GETISEARCHSTRING TVM_GETISEARCHSTRINGW
#define TV_DISPINFO TV_DISPINFOW
#define TVN_SELCHANGING TVN_SELCHANGINGW
#define TVN_SELCHANGED TVN_SELCHANGEDW
#define TVN_GETDISPINFO TVN_GETDISPINFOW
#define TVN_SETDISPINFO TVN_SETDISPINFOW
#define TVN_ITEMEXPANDING TVN_ITEMEXPANDINGW
#define TVN_ITEMEXPANDED TVN_ITEMEXPANDEDW
#define TVN_BEGINDRAG TVN_BEGINDRAGW
#define TVN_BEGINRDRAG TVN_BEGINRDRAGW
#define TVN_DELETEITEM TVN_DELETEITEMW
#define TVN_BEGINLABELEDIT TVN_BEGINLABELEDITW
#define TVN_ENDLABELEDIT TVN_ENDLABELEDITW
#define WC_TABCONTROL WC_TABCONTROLW
#define TC_ITEMHEADER TC_ITEMHEADERW
#define TC_ITEM TC_ITEMW
#define TCM_GETITEM TCM_GETITEMW
#define TCM_SETITEM TCM_SETITEMW
#define TCM_INSERTITEM TCM_INSERTITEMW
#define CreateStatusWindow CreateStatusWindowW
#define DrawStatusText DrawStatusTextW
#define ImageList_LoadImage ImageList_LoadImageW
#else
#define ANIMATE_CLASS ANIMATE_CLASSA
#define HOTKEY_CLASS HOTKEY_CLASSA
#define PROGRESS_CLASS PROGRESS_CLASSA
#define STATUSCLASSNAME STATUSCLASSNAMEA
#define TOOLBARCLASSNAME TOOLBARCLASSNAMEA
#define TOOLTIPS_CLASS TOOLTIPS_CLASSA
#define TRACKBAR_CLASS TRACKBAR_CLASSA
#define UPDOWN_CLASS UPDOWN_CLASSA
#define WC_HEADER WC_HEADERA
#define WC_LISTVIEW WC_LISTVIEWA
#define WC_TABCONTROL WC_TABCONTROLA
#define WC_TREEVIEW WC_TREEVIEWA
typedef HD_ITEMA HD_ITEM;
typedef TOOLINFOA TOOLINFO,*PTOOLINFO,*LPTOOLINFO;
typedef TTHITTESTINFOA TTHITTESTINFO,*LPHITTESTINFO;
typedef TOOLTIPTEXTA TOOLTIPTEXT,*LPTOOLTIPTEXT;
typedef TV_ITEMA TV_ITEM,*LPTV_ITEM;
typedef TV_INSERTSTRUCTA TV_INSERTSTRUCT,*LPTV_INSERTSTRUCT;
typedef NM_TREEVIEWA NM_TREEVIEW,*LPNM_TREEVIEW;
#define ACM_OPEN ACM_OPENA
#define SB_GETTEXT	SB_GETTEXTA
#define SB_SETTEXT	SB_SETTEXTA
#define SB_GETTEXTLENGTH	SB_GETTEXTLENGTHA
#define HDM_INSERTITEM HDM_INSERTITEMA
#define HDM_GETITEM HDM_GETITEMA
#define HDM_SETITEM HDM_SETITEMA
#define HDN_ITEMCHANGING	HDN_ITEMCHANGINGA
#define HDN_ITEMCHANGED	HDN_ITEMCHANGEDA
#define HDN_ITEMCLICK	HDN_ITEMCLICKA
#define HDN_ITEMDBLCLICK	HDN_ITEMDBLCLICKA
#define HDN_DIVIDERDBLCLICK	HDN_DIVIDERDBLCLICKA
#define HDN_BEGINTRACK	HDN_BEGINTRACKA
#define HDN_ENDTRACK	HDN_ENDTRACKA
#define HDN_TRACK	HDN_TRACKA
#define HD_NOTIFY HD_NOTIFYA
#define TBSAVEPARAMS TBSAVEPARAMSA
#define TB_GETBUTTONTEXT TB_GETBUTTONTEXTA
#define TB_SAVERESTORE TB_SAVERESTOREA
#define TB_ADDSTRING TB_ADDSTRINGA
#define TBN_GETBUTTONINFO TBN_GETBUTTONINFOA
#define TBNOTIFY TBNOTIFYA
#define LPTBNOTIFY LPTBNOTIFYA
#define TTM_ADDTOOL	TTM_ADDTOOLA
#define TTM_DELTOOL	TTM_DELTOOLA
#define TTM_NEWTOOLRECT	TTM_NEWTOOLRECTA
#define TTM_GETTOOLINFO	TTM_GETTOOLINFOA
#define TTM_SETTOOLINFO	TTM_SETTOOLINFOA
#define TTM_HITTEST	TTM_HITTESTA
#define TTM_GETTEXT	TTM_GETTEXTA
#define TTM_UPDATETIPTEXT	TTM_UPDATETIPTEXTA
#define TTM_ENUMTOOLS	TTM_ENUMTOOLSA
#define TTM_GETCURRENTTOOL TTM_GETCURRENTTOOLA
#define TTN_NEEDTEXT TTN_NEEDTEXTA
#define SB_GETTEXT	SB_GETTEXTA
#define SB_SETTEXT	SB_SETTEXTA
#define SB_GETTEXTLENGTH	SB_GETTEXTLENGTHA
#define LV_ITEM LV_ITEMA
#define LPSTR_TEXTCALLBACK LPSTR_TEXTCALLBACKA
#define LVM_GETITEM	LVM_GETITEMA
#define LVM_SETITEM LVM_SETITEMA
#define LVM_INSERTITEM LVM_INSERTITEMA
#define LV_FINDINFO LV_FINDINFOA
#define LVM_FINDITEM LVM_FINDITEMW
#define LVM_GETSTRINGWIDTH LVM_GETSTRINGWIDTHA
#define LVM_EDITLABEL LVM_EDITLABELA
#define LV_COLUMN LV_COLUMNA
#define LVM_GETCOLUMN LVM_GETCOLUMNA
#define LVM_SETCOLUMN LVM_SETCOLUMNA
#define LVM_INSERTCOLUMN LVM_INSERTCOLUMNA
#define LVM_GETITEMTEXT LVM_GETITEMTEXTA
#define LVM_SETITEMTEXT LVM_SETITEMTEXTA
#define LVM_GETISEARCHSTRING LVM_GETISEARCHSTRINGA
#define LVN_BEGINLABELEDIT LVN_BEGINLABELEDITA
#define LVN_ENDLABELEDIT LVN_ENDLABELEDITA
#define LVN_GETDISPINFO LVN_GETDISPINFOA
#define LVN_SETDISPINFO LVN_SETDISPINFOA
#define LV_DISPINFO LV_DISPINFOA
#define TVM_INSERTITEM TVM_INSERTITEMA
#define TVM_GETITEM TVM_GETITEMA
#define TVM_SETITEM TVM_SETITEMA
#define TVM_EDITLABEL TVM_EDITLABELA
#define TVM_GETISEARCHSTRING TVM_GETISEARCHSTRINGA
#define TV_DISPINFO TV_DISPINFOA
#define TVN_SELCHANGING TVN_SELCHANGINGA
#define TVN_SELCHANGED TVN_SELCHANGEDA
#define TVN_GETDISPINFO TVN_GETDISPINFOA
#define TVN_SETDISPINFO TVN_SETDISPINFOA
#define TVN_ITEMEXPANDING TVN_ITEMEXPANDINGA
#define TVN_ITEMEXPANDED TVN_ITEMEXPANDEDA
#define TVN_BEGINDRAG TVN_BEGINDRAGA
#define TVN_BEGINRDRAG TVN_BEGINRDRAGA
#define TVN_DELETEITEM TVN_DELETEITEMA
#define TVN_BEGINLABELEDIT TVN_BEGINLABELEDITA
#define TVN_ENDLABELEDIT TVN_ENDLABELEDITA
#define TC_ITEMHEADER TC_ITEMHEADERA
#define TC_ITEM TC_ITEMA
#define TCM_GETITEM TCM_GETITEMA
#define TCM_SETITEM TCM_SETITEMA
#define TCM_INSERTITEM TCM_INSERTITEMA
#define CreateStatusWindow CreateStatusWindowA
#define DrawStatusText DrawStatusTextA
#define ImageList_LoadImage ImageList_LoadImageA
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif
