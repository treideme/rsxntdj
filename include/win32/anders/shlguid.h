#define DEFINE_SHLGUID(n,l,w1,w2) DEFINE_GUID(n,l,w1,w2,0xC0,0,0,0,0,0,0,0x46)
#define SID_SShellBrowser IID_IShellBrowser
extern const GUID CLSID_ShellDesktop;
extern const GUID CLSID_ShellLink;
extern const GUID FMTID_Intshcut;
extern const GUID FMTID_InternetSite;
extern const GUID CGID_Explorer;
extern const GUID CGID_ShellDocView;
extern const GUID IID_INewShortcutHookA;
extern const GUID IID_IShellBrowser;
extern const GUID IID_IShellView;
extern const GUID IID_IContextMenu;
extern const GUID IID_IShellIcon;
extern const GUID IID_IShellFolder;
extern const GUID IID_IShellExtInit;
extern const GUID IID_IShellPropSheetExt;
extern const GUID IID_IPersistFolder;
extern const GUID IID_IExtractIconA;
extern const GUID IID_IShellLinkA;
extern const GUID IID_IShellCopyHookA;
extern const GUID IID_IFileViewerA;
extern const GUID IID_ICommDlgBrowser;
extern const GUID IID_IEnumIDList;
extern const GUID IID_IFileViewerSite;
extern const GUID IID_IContextMenu2;
extern const GUID IID_IShellExecuteHookA;
extern const GUID IID_IPropSheetPage;
extern const GUID IID_INewShortcutHookW;
extern const GUID IID_IFileViewerW;
extern const GUID IID_IShellLinkW;
extern const GUID IID_IExtractIconW;
extern const GUID IID_IShellExecuteHookW;
extern const GUID IID_IShellCopyHookW;
extern const GUID IID_IShellView2;
extern const GUID LIBID_SHDocVw;
extern const GUID IID_IShellExplorer;
extern const GUID DIID_DShellExplorerEvents;
extern const GUID CLSID_ShellExplorer;
extern const GUID IID_ISHItemOC;
extern const GUID DIID_DSHItemOCEvents;
extern const GUID CLSID_SHItemOC;
extern const GUID IID_DHyperLink;
extern const GUID IID_DIExplorer;
extern const GUID DIID_DExplorerEvents;
extern const GUID CLSID_InternetExplorer;
extern const GUID CLSID_StdHyperLink;
extern const GUID CLSID_FileTypes;
extern const GUID CLSID_InternetShortcut;
extern const GUID IID_IUniformResourceLocator;
#ifdef UNICODE
#define IID_IFileViewer	IID_IFileViewerW
#define IID_IShellLink	IID_IShellLinkW
#define IID_IExtractIcon	IID_IExtractIconW
#define IID_IShellCopyHook	IID_IShellCopyHookW
#define IID_IShellExecuteHook	IID_IShellExecuteHookW
#define IID_INewShortcutHook	IID_INewShortcutHookW
#else
#define IID_IFileViewer	IID_IFileViewerA
#define IID_IShellLink	IID_IShellLinkA
#define IID_IExtractIcon	IID_IExtractIconA
#define IID_IShellCopyHook	IID_IShellCopyHookA
#define IID_IShellExecuteHook	IID_IShellExecuteHookA
#define IID_INewShortcutHook	IID_INewShortcutHookA
#endif
