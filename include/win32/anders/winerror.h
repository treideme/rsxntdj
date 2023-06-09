#ifndef _WINERROR_H
#define _WINERROR_H
#define ERROR_SUCCESS 0L
#define NO_ERROR 0L
#define ERROR_INVALID_FUNCTION 1L
#define ERROR_FILE_NOT_FOUND 2L
#define ERROR_PATH_NOT_FOUND 3L
#define ERROR_TOO_MANY_OPEN_FILES 4L
#define ERROR_ACCESS_DENIED 5L
#define ERROR_INVALID_HANDLE 6L
#define ERROR_ARENA_TRASHED 7L
#define ERROR_NOT_ENOUGH_MEMORY 8L
#define ERROR_INVALID_BLOCK 9L
#define ERROR_BAD_ENVIRONMENT 10L
#define ERROR_BAD_FORMAT 11L
#define ERROR_INVALID_ACCESS 12L
#define ERROR_INVALID_DATA 13L
#define ERROR_OUTOFMEMORY 14L
#define ERROR_INVALID_DRIVE 15L
#define ERROR_CURRENT_DIRECTORY 16L
#define ERROR_NOT_SAME_DEVICE 17L
#define ERROR_NO_MORE_FILES 18L
#define ERROR_WRITE_PROTECT 19L
#define ERROR_BAD_UNIT 20L
#define ERROR_NOT_READY 21L
#define ERROR_BAD_COMMAND 22L
#define ERROR_CRC 23L
#define ERROR_BAD_LENGTH 24L
#define ERROR_SEEK 25L
#define ERROR_NOT_DOS_DISK 26L
#define ERROR_SECTOR_NOT_FOUND 27L
#define ERROR_OUT_OF_PAPER 28L
#define ERROR_WRITE_FAULT 29L
#define ERROR_READ_FAULT 30L
#define ERROR_GEN_FAILURE 31L
#define ERROR_SHARING_VIOLATION 32L
#define ERROR_LOCK_VIOLATION 33L
#define ERROR_WRONG_DISK 34L
#define ERROR_SHARING_BUFFER_EXCEEDED 36L
#define ERROR_HANDLE_EOF 38L
#define ERROR_HANDLE_DISK_FULL 39L
#define ERROR_NOT_SUPPORTED 50L
#define ERROR_REM_NOT_LIST 51L
#define ERROR_DUP_NAME 52L
#define ERROR_BAD_NETPATH 53L
#define ERROR_NETWORK_BUSY 54L
#define ERROR_DEV_NOT_EXIST 55L
#define ERROR_TOO_MANY_CMDS 56L
#define ERROR_ADAP_HDW_ERR 57L
#define ERROR_BAD_NET_RESP 58L
#define ERROR_UNEXP_NET_ERR 59L
#define ERROR_BAD_REM_ADAP 60L
#define ERROR_PRINTQ_FULL 61L
#define ERROR_NO_SPOOL_SPACE 62L
#define ERROR_PRINT_CANCELLED 63L
#define ERROR_NETNAME_DELETED 64L
#define ERROR_NETWORK_ACCESS_DENIED 65L
#define ERROR_BAD_DEV_TYPE 66L
#define ERROR_BAD_NET_NAME 67L
#define ERROR_TOO_MANY_NAMES 68L
#define ERROR_TOO_MANY_SESS 69L
#define ERROR_SHARING_PAUSED 70L
#define ERROR_REQ_NOT_ACCEP 71L
#define ERROR_REDIR_PAUSED 72L
#define ERROR_FILE_EXISTS 80L
#define ERROR_CANNOT_MAKE 82L
#define ERROR_FAIL_I24 83L
#define ERROR_OUT_OF_STRUCTURES 84L
#define ERROR_ALREADY_ASSIGNED 85L
#define ERROR_INVALID_PASSWORD 86L
#define ERROR_INVALID_PARAMETER 87L
#define ERROR_NET_WRITE_FAULT 88L
#define ERROR_NO_PROC_SLOTS 89L
#define ERROR_TOO_MANY_SEMAPHORES 100L
#define ERROR_EXCL_SEM_ALREADY_OWNED 101L
#define ERROR_SEM_IS_SET 102L
#define ERROR_TOO_MANY_SEM_REQUESTS 103L
#define ERROR_INVALID_AT_INTERRUPT_TIME 104L
#define ERROR_SEM_OWNER_DIED 105L
#define ERROR_SEM_USER_LIMIT 106L
#define ERROR_DISK_CHANGE 107L
#define ERROR_DRIVE_LOCKED 108L
#define ERROR_BROKEN_PIPE 109L
#define ERROR_OPEN_FAILED 110L
#define ERROR_BUFFER_OVERFLOW 111L
#define ERROR_DISK_FULL 112L
#define ERROR_NO_MORE_SEARCH_HANDLES 113L
#define ERROR_INVALID_TARGET_HANDLE 114L
#define ERROR_INVALID_CATEGORY 117L
#define ERROR_INVALID_VERIFY_SWITCH 118L
#define ERROR_BAD_DRIVER_LEVEL 119L
#define ERROR_CALL_NOT_IMPLEMENTED 120L
#define ERROR_SEM_TIMEOUT 121L
#define ERROR_INSUFFICIENT_BUFFER 122L
#define ERROR_INVALID_NAME 123L
#define ERROR_INVALID_LEVEL 124L
#define ERROR_NO_VOLUME_LABEL 125L
#define ERROR_MOD_NOT_FOUND 126L
#define ERROR_PROC_NOT_FOUND 127L
#define ERROR_WAIT_NO_CHILDREN 128L
#define ERROR_CHILD_NOT_COMPLETE 129L
#define ERROR_DIRECT_ACCESS_HANDLE 130L
#define ERROR_NEGATIVE_SEEK 131L
#define ERROR_SEEK_ON_DEVICE 132L
#define ERROR_IS_JOIN_TARGET 133L
#define ERROR_IS_JOINED 134L
#define ERROR_IS_SUBSTED 135L
#define ERROR_NOT_JOINED 136L
#define ERROR_NOT_SUBSTED 137L
#define ERROR_JOIN_TO_JOIN 138L
#define ERROR_SUBST_TO_SUBST 139L
#define ERROR_JOIN_TO_SUBST 140L
#define ERROR_SUBST_TO_JOIN 141L
#define ERROR_BUSY_DRIVE 142L
#define ERROR_SAME_DRIVE 143L
#define ERROR_DIR_NOT_ROOT 144L
#define ERROR_DIR_NOT_EMPTY 145L
#define ERROR_IS_SUBST_PATH 146L
#define ERROR_IS_JOIN_PATH 147L
#define ERROR_PATH_BUSY 148L
#define ERROR_IS_SUBST_TARGET 149L
#define ERROR_SYSTEM_TRACE 150L
#define ERROR_INVALID_EVENT_COUNT 151L
#define ERROR_TOO_MANY_MUXWAITERS 152L
#define ERROR_INVALID_LIST_FORMAT 153L
#define ERROR_LABEL_TOO_LONG 154L
#define ERROR_TOO_MANY_TCBS 155L
#define ERROR_SIGNAL_REFUSED 156L
#define ERROR_DISCARDED 157L
#define ERROR_NOT_LOCKED 158L
#define ERROR_BAD_THREADID_ADDR 159L
#define ERROR_BAD_ARGUMENTS 160L
#define ERROR_BAD_PATHNAME 161L
#define ERROR_SIGNAL_PENDING 162L
#define ERROR_MAX_THRDS_REACHED 164L
#define ERROR_LOCK_FAILED 167L
#define ERROR_BUSY 170L
#define ERROR_CANCEL_VIOLATION 173L
#define ERROR_ATOMIC_LOCKS_NOT_SUPPORTED 174L
#define ERROR_INVALID_SEGMENT_NUMBER 180L
#define ERROR_INVALID_ORDINAL 182L
#define ERROR_ALREADY_EXISTS 183L
#define ERROR_INVALID_FLAG_NUMBER 186L
#define ERROR_SEM_NOT_FOUND 187L
#define ERROR_INVALID_STARTING_CODESEG 188L
#define ERROR_INVALID_STACKSEG 189L
#define ERROR_INVALID_MODULETYPE 190L
#define ERROR_INVALID_EXE_SIGNATURE 191L
#define ERROR_EXE_MARKED_INVALID 192L
#define ERROR_BAD_EXE_FORMAT 193L
#define ERROR_ITERATED_DATA_EXCEEDS_64k 194L
#define ERROR_INVALID_MINALLOCSIZE 195L
#define ERROR_DYNLINK_FROM_INVALID_RING 196L
#define ERROR_IOPL_NOT_ENABLED 197L
#define ERROR_INVALID_SEGDPL 198L
#define ERROR_AUTODATASEG_EXCEEDS_64k 199L
#define ERROR_RING2SEG_MUST_BE_MOVABLE 200L
#define ERROR_RELOC_CHAIN_XEEDS_SEGLIM 201L
#define ERROR_INFLOOP_IN_RELOC_CHAIN 202L
#define ERROR_ENVVAR_NOT_FOUND 203L
#define ERROR_NO_SIGNAL_SENT 205L
#define ERROR_FILENAME_EXCED_RANGE 206L
#define ERROR_RING2_STACK_IN_USE 207L
#define ERROR_META_EXPANSION_TOO_LONG 208L
#define ERROR_INVALID_SIGNAL_NUMBER 209L
#define ERROR_THREAD_1_INACTIVE 210L
#define ERROR_LOCKED 212L
#define ERROR_TOO_MANY_MODULES 214L
#define ERROR_NESTING_NOT_ALLOWED 215L
#define ERROR_BAD_PIPE 230L
#define ERROR_PIPE_BUSY 231L
#define ERROR_NO_DATA 232L
#define ERROR_PIPE_NOT_CONNECTED 233L
#define ERROR_MORE_DATA 234L
#define ERROR_VC_DISCONNECTED 240L
#define ERROR_INVALID_EA_NAME 254L
#define ERROR_EA_LIST_INCONSISTENT 255L
#define ERROR_NO_MORE_ITEMS 259L
#define ERROR_CANNOT_COPY 266L
#define ERROR_DIRECTORY 267L
#define ERROR_EAS_DIDNT_FIT 275L
#define ERROR_EA_FILE_CORRUPT 276L
#define ERROR_EA_TABLE_FULL 277L
#define ERROR_INVALID_EA_HANDLE 278L
#define ERROR_EAS_NOT_SUPPORTED 282L
#define ERROR_NOT_OWNER 288L
#define ERROR_TOO_MANY_POSTS 298L
#define ERROR_PARTIAL_COPY 299L
#define ERROR_MR_MID_NOT_FOUND 317L
#define ERROR_INVALID_ADDRESS 487L
#define ERROR_ARITHMETIC_OVERFLOW 534L
#define ERROR_PIPE_CONNECTED 535L
#define ERROR_PIPE_LISTENING 536L
#define ERROR_EA_ACCESS_DENIED 994L
#define ERROR_OPERATION_ABORTED 995L
#define ERROR_IO_INCOMPLETE 996L
#define ERROR_IO_PENDING 997L
#define ERROR_NOACCESS 998L
#define ERROR_SWAPERROR 999L
#define ERROR_STACK_OVERFLOW 1001L
#define ERROR_INVALID_MESSAGE 1002L
#define ERROR_CAN_NOT_COMPLETE 1003L
#define ERROR_INVALID_FLAGS 1004L
#define ERROR_UNRECOGNIZED_VOLUME 1005L
#define ERROR_FILE_INVALID 1006L
#define ERROR_FULLSCREEN_MODE 1007L
#define ERROR_NO_TOKEN 1008L
#define ERROR_BADDB 1009L
#define ERROR_BADKEY 1010L
#define ERROR_CANTOPEN 1011L
#define ERROR_CANTREAD 1012L
#define ERROR_CANTWRITE 1013L
#define ERROR_REGISTRY_RECOVERED 1014L
#define ERROR_REGISTRY_CORRUPT 1015L
#define ERROR_REGISTRY_IO_FAILED 1016L
#define ERROR_NOT_REGISTRY_FILE 1017L
#define ERROR_KEY_DELETED 1018L
#define ERROR_NO_LOG_SPACE 1019L
#define ERROR_KEY_HAS_CHILDREN 1020L
#define ERROR_CHILD_MUST_BE_VOLATILE 1021L
#define ERROR_NOTIFY_ENUM_DIR 1022L
#define ERROR_DEPENDENT_SERVICES_RUNNING 1051L
#define ERROR_INVALID_SERVICE_CONTROL 1052L
#define ERROR_SERVICE_REQUEST_TIMEOUT 1053L
#define ERROR_SERVICE_NO_THREAD 1054L
#define ERROR_SERVICE_DATABASE_LOCKED 1055L
#define ERROR_SERVICE_ALREADY_RUNNING 1056L
#define ERROR_INVALID_SERVICE_ACCOUNT 1057L
#define ERROR_SERVICE_DISABLED 1058L
#define ERROR_CIRCULAR_DEPENDENCY 1059L
#define ERROR_SERVICE_DOES_NOT_EXIST 1060L
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL 1061L
#define ERROR_SERVICE_NOT_ACTIVE 1062L
#define ERROR_FAILED_SERVICE_CONTROLLER_CONNECT 1063L
#define ERROR_EXCEPTION_IN_SERVICE 1064L
#define ERROR_DATABASE_DOES_NOT_EXIST 1065L
#define ERROR_SERVICE_SPECIFIC_ERROR 1066L
#define ERROR_PROCESS_ABORTED 1067L
#define ERROR_SERVICE_DEPENDENCY_FAIL 1068L
#define ERROR_SERVICE_LOGON_FAILED 1069L
#define ERROR_SERVICE_START_HANG 1070L
#define ERROR_INVALID_SERVICE_LOCK 1071L
#define ERROR_SERVICE_MARKED_FOR_DELETE 1072L
#define ERROR_SERVICE_EXISTS 1073L
#define ERROR_ALREADY_RUNNING_LKG 1074L
#define ERROR_SERVICE_DEPENDENCY_DELETED 1075L
#define ERROR_BOOT_ALREADY_ACCEPTED 1076L
#define ERROR_SERVICE_NEVER_STARTED 1077L
#define ERROR_DUPLICATE_SERVICE_NAME 1078L
#define ERROR_END_OF_MEDIA 1100L
#define ERROR_FILEMARK_DETECTED 1101L
#define ERROR_BEGINNING_OF_MEDIA 1102L
#define ERROR_SETMARK_DETECTED 1103L
#define ERROR_NO_DATA_DETECTED 1104L
#define ERROR_PARTITION_FAILURE 1105L
#define ERROR_INVALID_BLOCK_LENGTH 1106L
#define ERROR_DEVICE_NOT_PARTITIONED 1107L
#define ERROR_UNABLE_TO_LOCK_MEDIA 1108L
#define ERROR_UNABLE_TO_UNLOAD_MEDIA 1109L
#define ERROR_MEDIA_CHANGED 1110L
#define ERROR_BUS_RESET 1111L
#define ERROR_NO_MEDIA_IN_DRIVE 1112L
#define ERROR_NO_UNICODE_TRANSLATION 1113L
#define ERROR_DLL_INIT_FAILED 1114L
#define ERROR_SHUTDOWN_IN_PROGRESS 1115L
#define ERROR_NO_SHUTDOWN_IN_PROGRESS 1116L
#define ERROR_IO_DEVICE 1117L
#define ERROR_SERIAL_NO_DEVICE 1118L
#define ERROR_IRQ_BUSY 1119L
#define ERROR_MORE_WRITES 1120L
#define ERROR_COUNTER_TIMEOUT 1121L
#define ERROR_FLOPPY_ID_MARK_NOT_FOUND 1122L
#define ERROR_FLOPPY_WRONG_CYLINDER 1123L
#define ERROR_FLOPPY_UNKNOWN_ERROR 1124L
#define ERROR_FLOPPY_BAD_REGISTERS 1125L
#define ERROR_DISK_RECALIBRATE_FAILED 1126L
#define ERROR_DISK_OPERATION_FAILED 1127L
#define ERROR_DISK_RESET_FAILED 1128L
#define ERROR_EOM_OVERFLOW 1129L
#define ERROR_NOT_ENOUGH_SERVER_MEMORY 1130L
#define ERROR_POSSIBLE_DEADLOCK 1131L
#define ERROR_MAPPED_ALIGNMENT 1132L
#define ERROR_SET_POWER_STATE_VETOED 1140L
#define ERROR_SET_POWER_STATE_FAILED 1141L
#define ERROR_OLD_WIN_VERSION 1150L
#define ERROR_APP_WRONG_OS 1151L
#define ERROR_SINGLE_INSTANCE_APP 1152L
#define ERROR_RMODE_APP 1153L
#define ERROR_INVALID_DLL 1154L
#define ERROR_NO_ASSOCIATION 1155L
#define ERROR_DDE_FAIL 1156L
#define ERROR_DLL_NOT_FOUND 1157L
#define ERROR_BAD_USERNAME 2202L
#define ERROR_NOT_CONNECTED 2250L
#define ERROR_OPEN_FILES 2401L
#define ERROR_ACTIVE_CONNECTIONS 2402L
#define ERROR_DEVICE_IN_USE 2404L
#define ERROR_BAD_DEVICE 1200L
#define ERROR_CONNECTION_UNAVAIL 1201L
#define ERROR_DEVICE_ALREADY_REMEMBERED 1202L
#define ERROR_NO_NET_OR_BAD_PATH 1203L
#define ERROR_BAD_PROVIDER 1204L
#define ERROR_CANNOT_OPEN_PROFILE 1205L
#define ERROR_BAD_PROFILE 1206L
#define ERROR_NOT_CONTAINER 1207L
#define ERROR_EXTENDED_ERROR 1208L
#define ERROR_INVALID_GROUPNAME 1209L
#define ERROR_INVALID_COMPUTERNAME 1210L
#define ERROR_INVALID_EVENTNAME 1211L
#define ERROR_INVALID_DOMAINNAME 1212L
#define ERROR_INVALID_SERVICENAME 1213L
#define ERROR_INVALID_NETNAME 1214L
#define ERROR_INVALID_SHARENAME 1215L
#define ERROR_INVALID_PASSWORDNAME 1216L
#define ERROR_INVALID_MESSAGENAME 1217L
#define ERROR_INVALID_MESSAGEDEST 1218L
#define ERROR_SESSION_CREDENTIAL_CONFLICT 1219L
#define ERROR_REMOTE_SESSION_LIMIT_EXCEEDED 1220L
#define ERROR_DUP_DOMAINNAME 1221L
#define ERROR_NO_NETWORK 1222L
#define ERROR_CANCELLED 1223L
#define ERROR_USER_MAPPED_FILE 1224L
#define ERROR_CONNECTION_REFUSED 1225L
#define ERROR_GRACEFUL_DISCONNECT 1226L
#define ERROR_ADDRESS_ALREADY_ASSOCIATED 1227L
#define ERROR_ADDRESS_NOT_ASSOCIATED 1228L
#define ERROR_CONNECTION_INVALID 1229L
#define ERROR_CONNECTION_ACTIVE 1230L
#define ERROR_NETWORK_UNREACHABLE 1231L
#define ERROR_HOST_UNREACHABLE 1232L
#define ERROR_PROTOCOL_UNREACHABLE 1233L
#define ERROR_PORT_UNREACHABLE 1234L
#define ERROR_REQUEST_ABORTED 1235L
#define ERROR_CONNECTION_ABORTED 1236L
#define ERROR_RETRY 1237L
#define ERROR_CONNECTION_COUNT_LIMIT 1238L
#define ERROR_LOGIN_TIME_RESTRICTION 1239L
#define ERROR_LOGIN_WKSTA_RESTRICTION 1240L
#define ERROR_INCORRECT_ADDRESS 1241L
#define ERROR_ALREADY_REGISTERED 1242L
#define ERROR_SERVICE_NOT_FOUND 1243L
#define ERROR_NOT_AUTHENTICATED 1244L
#define ERROR_NOT_LOGGED_ON 1245L
#define ERROR_CONTINUE 1246L
#define ERROR_ALREADY_INITIALIZED 1247L
#define ERROR_NO_MORE_DEVICES 1248L
#define ERROR_NOT_ALL_ASSIGNED 1300L
#define ERROR_SOME_NOT_MAPPED 1301L
#define ERROR_NO_QUOTAS_FOR_ACCOUNT 1302L
#define ERROR_LOCAL_USER_SESSION_KEY 1303L
#define ERROR_NULL_LM_PASSWORD 1304L
#define ERROR_UNKNOWN_REVISION 1305L
#define ERROR_REVISION_MISMATCH 1306L
#define ERROR_INVALID_OWNER 1307L
#define ERROR_INVALID_PRIMARY_GROUP 1308L
#define ERROR_NO_IMPERSONATION_TOKEN 1309L
#define ERROR_CANT_DISABLE_MANDATORY 1310L
#define ERROR_NO_LOGON_SERVERS 1311L
#define ERROR_NO_SUCH_LOGON_SESSION 1312L
#define ERROR_NO_SUCH_PRIVILEGE 1313L
#define ERROR_PRIVILEGE_NOT_HELD 1314L
#define ERROR_INVALID_ACCOUNT_NAME 1315L
#define ERROR_USER_EXISTS 1316L
#define ERROR_NO_SUCH_USER 1317L
#define ERROR_GROUP_EXISTS 1318L
#define ERROR_NO_SUCH_GROUP 1319L
#define ERROR_MEMBER_IN_GROUP 1320L
#define ERROR_MEMBER_NOT_IN_GROUP 1321L
#define ERROR_LAST_ADMIN 1322L
#define ERROR_WRONG_PASSWORD 1323L
#define ERROR_ILL_FORMED_PASSWORD 1324L
#define ERROR_PASSWORD_RESTRICTION 1325L
#define ERROR_LOGON_FAILURE 1326L
#define ERROR_ACCOUNT_RESTRICTION 1327L
#define ERROR_INVALID_LOGON_HOURS 1328L
#define ERROR_INVALID_WORKSTATION 1329L
#define ERROR_PASSWORD_EXPIRED 1330L
#define ERROR_ACCOUNT_DISABLED 1331L
#define ERROR_NONE_MAPPED 1332L
#define ERROR_TOO_MANY_LUIDS_REQUESTED 1333L
#define ERROR_LUIDS_EXHAUSTED 1334L
#define ERROR_INVALID_SUB_AUTHORITY 1335L
#define ERROR_INVALID_ACL 1336L
#define ERROR_INVALID_SID 1337L
#define ERROR_INVALID_SECURITY_DESCR 1338L
#define ERROR_BAD_INHERITANCE_ACL 1340L
#define ERROR_SERVER_DISABLED 1341L
#define ERROR_SERVER_NOT_DISABLED 1342L
#define ERROR_INVALID_ID_AUTHORITY 1343L
#define ERROR_ALLOTTED_SPACE_EXCEEDED 1344L
#define ERROR_INVALID_GROUP_ATTRIBUTES 1345L
#define ERROR_BAD_IMPERSONATION_LEVEL 1346L
#define ERROR_CANT_OPEN_ANONYMOUS 1347L
#define ERROR_BAD_VALIDATION_CLASS 1348L
#define ERROR_BAD_TOKEN_TYPE 1349L
#define ERROR_NO_SECURITY_ON_OBJECT 1350L
#define ERROR_CANT_ACCESS_DOMAIN_INFO 1351L
#define ERROR_INVALID_SERVER_STATE 1352L
#define ERROR_INVALID_DOMAIN_STATE 1353L
#define ERROR_INVALID_DOMAIN_ROLE 1354L
#define ERROR_NO_SUCH_DOMAIN 1355L
#define ERROR_DOMAIN_EXISTS 1356L
#define ERROR_DOMAIN_LIMIT_EXCEEDED 1357L
#define ERROR_INTERNAL_DB_CORRUPTION 1358L
#define ERROR_INTERNAL_ERROR 1359L
#define ERROR_GENERIC_NOT_MAPPED 1360L
#define ERROR_BAD_DESCRIPTOR_FORMAT 1361L
#define ERROR_NOT_LOGON_PROCESS 1362L
#define ERROR_LOGON_SESSION_EXISTS 1363L
#define ERROR_NO_SUCH_PACKAGE 1364L
#define ERROR_BAD_LOGON_SESSION_STATE 1365L
#define ERROR_LOGON_SESSION_COLLISION 1366L
#define ERROR_INVALID_LOGON_TYPE 1367L
#define ERROR_CANNOT_IMPERSONATE 1368L
#define ERROR_RXACT_INVALID_STATE 1369L
#define ERROR_RXACT_COMMIT_FAILURE 1370L
#define ERROR_SPECIAL_ACCOUNT 1371L
#define ERROR_SPECIAL_GROUP 1372L
#define ERROR_SPECIAL_USER 1373L
#define ERROR_MEMBERS_PRIMARY_GROUP 1374L
#define ERROR_TOKEN_ALREADY_IN_USE 1375L
#define ERROR_NO_SUCH_ALIAS 1376L
#define ERROR_MEMBER_NOT_IN_ALIAS 1377L
#define ERROR_MEMBER_IN_ALIAS 1378L
#define ERROR_ALIAS_EXISTS 1379L
#define ERROR_LOGON_NOT_GRANTED 1380L
#define ERROR_TOO_MANY_SECRETS 1381L
#define ERROR_SECRET_TOO_LONG 1382L
#define ERROR_INTERNAL_DB_ERROR 1383L
#define ERROR_TOO_MANY_CONTEXT_IDS 1384L
#define ERROR_LOGON_TYPE_NOT_GRANTED 1385L
#define ERROR_NT_CROSS_ENCRYPTION_REQUIRED 1386L
#define ERROR_NO_SUCH_MEMBER 1387L
#define ERROR_INVALID_MEMBER 1388L
#define ERROR_TOO_MANY_SIDS 1389L
#define ERROR_LM_CROSS_ENCRYPTION_REQUIRED 1390L
#define ERROR_NO_INHERITANCE 1391L
#define ERROR_FILE_CORRUPT 1392L
#define ERROR_DISK_CORRUPT 1393L
#define ERROR_NO_USER_SESSION_KEY 1394L
#define ERROR_LICENSE_QUOTA_EXCEEDED 1395L
#define ERROR_INVALID_WINDOW_HANDLE 1400L
#define ERROR_INVALID_MENU_HANDLE 1401L
#define ERROR_INVALID_CURSOR_HANDLE 1402L
#define ERROR_INVALID_ACCEL_HANDLE 1403L
#define ERROR_INVALID_HOOK_HANDLE 1404L
#define ERROR_INVALID_DWP_HANDLE 1405L
#define ERROR_TLW_WITH_WSCHILD 1406L
#define ERROR_CANNOT_FIND_WND_CLASS 1407L
#define ERROR_WINDOW_OF_OTHER_THREAD 1408L
#define ERROR_HOTKEY_ALREADY_REGISTERED 1409L
#define ERROR_CLASS_ALREADY_EXISTS 1410L
#define ERROR_CLASS_DOES_NOT_EXIST 1411L
#define ERROR_CLASS_HAS_WINDOWS 1412L
#define ERROR_INVALID_INDEX 1413L
#define ERROR_INVALID_ICON_HANDLE 1414L
#define ERROR_PRIVATE_DIALOG_INDEX 1415L
#define ERROR_LISTBOX_ID_NOT_FOUND 1416L
#define ERROR_NO_WILDCARD_CHARACTERS 1417L
#define ERROR_CLIPBOARD_NOT_OPEN 1418L
#define ERROR_HOTKEY_NOT_REGISTERED 1419L
#define ERROR_WINDOW_NOT_DIALOG 1420L
#define ERROR_CONTROL_ID_NOT_FOUND 1421L
#define ERROR_INVALID_COMBOBOX_MESSAGE 1422L
#define ERROR_WINDOW_NOT_COMBOBOX 1423L
#define ERROR_INVALID_EDIT_HEIGHT 1424L
#define ERROR_DC_NOT_FOUND 1425L
#define ERROR_INVALID_HOOK_FILTER 1426L
#define ERROR_INVALID_FILTER_PROC 1427L
#define ERROR_HOOK_NEEDS_HMOD 1428L
#define ERROR_GLOBAL_ONLY_HOOK 1429L
#define ERROR_JOURNAL_HOOK_SET 1430L
#define ERROR_HOOK_NOT_INSTALLED 1431L
#define ERROR_INVALID_LB_MESSAGE 1432L
#define ERROR_SETCOUNT_ON_BAD_LB 1433L
#define ERROR_LB_WITHOUT_TABSTOPS 1434L
#define ERROR_DESTROY_OBJECT_OF_OTHER_THREAD 1435L
#define ERROR_CHILD_WINDOW_MENU 1436L
#define ERROR_NO_SYSTEM_MENU 1437L
#define ERROR_INVALID_MSGBOX_STYLE 1438L
#define ERROR_INVALID_SPI_VALUE 1439L
#define ERROR_SCREEN_ALREADY_LOCKED 1440L
#define ERROR_HWNDS_HAVE_DIFF_PARENT 1441L
#define ERROR_NOT_CHILD_WINDOW 1442L
#define ERROR_INVALID_GW_COMMAND 1443L
#define ERROR_INVALID_THREAD_ID 1444L
#define ERROR_NON_MDICHILD_WINDOW 1445L
#define ERROR_POPUP_ALREADY_ACTIVE 1446L
#define ERROR_NO_SCROLLBARS 1447L
#define ERROR_INVALID_SCROLLBAR_RANGE 1448L
#define ERROR_INVALID_SHOWWIN_COMMAND 1449L
#define ERROR_NO_SYSTEM_RESOURCES 1450L
#define ERROR_NONPAGED_SYSTEM_RESOURCES 1451L
#define ERROR_PAGED_SYSTEM_RESOURCES 1452L
#define ERROR_WORKING_SET_QUOTA 1453L
#define ERROR_PAGEFILE_QUOTA 1454L
#define ERROR_COMMITMENT_LIMIT 1455L
#define ERROR_MENU_ITEM_NOT_FOUND 1456L
#define ERROR_EVENTLOG_FILE_CORRUPT 1500L
#define ERROR_EVENTLOG_CANT_START 1501L
#define ERROR_LOG_FILE_FULL 1502L
#define ERROR_EVENTLOG_FILE_CHANGED 1503L
#define RPC_S_INVALID_STRING_BINDING 1700L
#define RPC_S_WRONG_KIND_OF_BINDING 1701L
#define RPC_S_INVALID_BINDING 1702L
#define RPC_S_PROTSEQ_NOT_SUPPORTED 1703L
#define RPC_S_INVALID_RPC_PROTSEQ 1704L
#define RPC_S_INVALID_STRING_UUID 1705L
#define RPC_S_INVALID_ENDPOINT_FORMAT 1706L
#define RPC_S_INVALID_NET_ADDR 1707L
#define RPC_S_NO_ENDPOINT_FOUND 1708L
#define RPC_S_INVALID_TIMEOUT 1709L
#define RPC_S_OBJECT_NOT_FOUND 1710L
#define RPC_S_ALREADY_REGISTERED 1711L
#define RPC_S_TYPE_ALREADY_REGISTERED 1712L
#define RPC_S_ALREADY_LISTENING 1713L
#define RPC_S_NO_PROTSEQS_REGISTERED 1714L
#define RPC_S_NOT_LISTENING 1715L
#define RPC_S_UNKNOWN_MGR_TYPE 1716L
#define RPC_S_UNKNOWN_IF 1717L
#define RPC_S_NO_BINDINGS 1718L
#define RPC_S_NO_PROTSEQS 1719L
#define RPC_S_CANT_CREATE_ENDPOINT 1720L
#define RPC_S_OUT_OF_RESOURCES 1721L
#define RPC_S_SERVER_UNAVAILABLE 1722L
#define RPC_S_SERVER_TOO_BUSY 1723L
#define RPC_S_INVALID_NETWORK_OPTIONS 1724L
#define RPC_S_NO_CALL_ACTIVE 1725L
#define RPC_S_CALL_FAILED 1726L
#define RPC_S_CALL_FAILED_DNE 1727L
#define RPC_S_PROTOCOL_ERROR 1728L
#define RPC_S_UNSUPPORTED_TRANS_SYN 1730L
#define RPC_S_UNSUPPORTED_TYPE 1732L
#define RPC_S_INVALID_TAG 1733L
#define RPC_S_INVALID_BOUND 1734L
#define RPC_S_NO_ENTRY_NAME 1735L
#define RPC_S_INVALID_NAME_SYNTAX 1736L
#define RPC_S_UNSUPPORTED_NAME_SYNTAX 1737L
#define RPC_S_UUID_NO_ADDRESS 1739L
#define RPC_S_DUPLICATE_ENDPOINT 1740L
#define RPC_S_UNKNOWN_AUTHN_TYPE 1741L
#define RPC_S_MAX_CALLS_TOO_SMALL 1742L
#define RPC_S_STRING_TOO_LONG 1743L
#define RPC_S_PROTSEQ_NOT_FOUND 1744L
#define RPC_S_PROCNUM_OUT_OF_RANGE 1745L
#define RPC_S_BINDING_HAS_NO_AUTH 1746L
#define RPC_S_UNKNOWN_AUTHN_SERVICE 1747L
#define RPC_S_UNKNOWN_AUTHN_LEVEL 1748L
#define RPC_S_INVALID_AUTH_IDENTITY 1749L
#define RPC_S_UNKNOWN_AUTHZ_SERVICE 1750L
#define EPT_S_INVALID_ENTRY 1751L
#define EPT_S_CANT_PERFORM_OP 1752L
#define EPT_S_NOT_REGISTERED 1753L
#define RPC_S_NOTHING_TO_EXPORT 1754L
#define RPC_S_INCOMPLETE_NAME 1755L
#define RPC_S_INVALID_VERS_OPTION 1756L
#define RPC_S_NO_MORE_MEMBERS 1757L
#define RPC_S_NOT_ALL_OBJS_UNEXPORTED 1758L
#define RPC_S_INTERFACE_NOT_FOUND 1759L
#define RPC_S_ENTRY_ALREADY_EXISTS 1760L
#define RPC_S_ENTRY_NOT_FOUND 1761L
#define RPC_S_NAME_SERVICE_UNAVAILABLE 1762L
#define RPC_S_INVALID_NAF_ID 1763L
#define RPC_S_CANNOT_SUPPORT 1764L
#define RPC_S_NO_CONTEXT_AVAILABLE 1765L
#define RPC_S_INTERNAL_ERROR 1766L
#define RPC_S_ZERO_DIVIDE 1767L
#define RPC_S_ADDRESS_ERROR 1768L
#define RPC_S_FP_DIV_ZERO 1769L
#define RPC_S_FP_UNDERFLOW 1770L
#define RPC_S_FP_OVERFLOW 1771L
#define RPC_X_NO_MORE_ENTRIES 1772L
#define RPC_X_SS_CHAR_TRANS_OPEN_FAIL 1773L
#define RPC_X_SS_CHAR_TRANS_SHORT_FILE 1774L
#define RPC_X_SS_IN_NULL_CONTEXT 1775L
#define RPC_X_SS_CONTEXT_DAMAGED 1777L
#define RPC_X_SS_HANDLES_MISMATCH 1778L
#define RPC_X_SS_CANNOT_GET_CALL_HANDLE 1779L
#define RPC_X_NULL_REF_POINTER 1780L
#define RPC_X_ENUM_VALUE_OUT_OF_RANGE 1781L
#define RPC_X_BYTE_COUNT_TOO_SMALL 1782L
#define RPC_X_BAD_STUB_DATA 1783L
#define ERROR_INVALID_USER_BUFFER 1784L
#define ERROR_UNRECOGNIZED_MEDIA 1785L
#define ERROR_NO_TRUST_LSA_SECRET 1786L
#define ERROR_NO_TRUST_SAM_ACCOUNT 1787L
#define ERROR_TRUSTED_DOMAIN_FAILURE 1788L
#define ERROR_TRUSTED_RELATIONSHIP_FAILURE 1789L
#define ERROR_TRUST_FAILURE 1790L
#define RPC_S_CALL_IN_PROGRESS 1791L
#define ERROR_NETLOGON_NOT_STARTED 1792L
#define ERROR_ACCOUNT_EXPIRED 1793L
#define ERROR_REDIRECTOR_HAS_OPEN_HANDLES 1794L
#define ERROR_PRINTER_DRIVER_ALREADY_INSTALLED 1795L
#define ERROR_UNKNOWN_PORT 1796L
#define ERROR_UNKNOWN_PRINTER_DRIVER 1797L
#define ERROR_UNKNOWN_PRINTPROCESSOR 1798L
#define ERROR_INVALID_SEPARATOR_FILE 1799L
#define ERROR_INVALID_PRIORITY 1800L
#define ERROR_INVALID_PRINTER_NAME 1801L
#define ERROR_PRINTER_ALREADY_EXISTS 1802L
#define ERROR_INVALID_PRINTER_COMMAND 1803L
#define ERROR_INVALID_DATATYPE 1804L
#define ERROR_INVALID_ENVIRONMENT 1805L
#define RPC_S_NO_MORE_BINDINGS 1806L
#define ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT 1807L
#define ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT 1808L
#define ERROR_NOLOGON_SERVER_TRUST_ACCOUNT 1809L
#define ERROR_DOMAIN_TRUST_INCONSISTENT 1810L
#define ERROR_SERVER_HAS_OPEN_HANDLES 1811L
#define ERROR_RESOURCE_DATA_NOT_FOUND 1812L
#define ERROR_RESOURCE_TYPE_NOT_FOUND 1813L
#define ERROR_RESOURCE_NAME_NOT_FOUND 1814L
#define ERROR_RESOURCE_LANG_NOT_FOUND 1815L
#define ERROR_NOT_ENOUGH_QUOTA 1816L
#define RPC_S_NO_INTERFACES 1817L
#define RPC_S_CALL_CANCELLED 1818L
#define RPC_S_BINDING_INCOMPLETE 1819L
#define RPC_S_COMM_FAILURE 1820L
#define RPC_S_UNSUPPORTED_AUTHN_LEVEL 1821L
#define RPC_S_NO_PRINC_NAME 1822L
#define RPC_S_NOT_RPC_ERROR 1823L
#define RPC_S_UUID_LOCAL_ONLY 1824L
#define RPC_S_SEC_PKG_ERROR 1825L
#define RPC_S_NOT_CANCELLED 1826L
#define RPC_X_INVALID_ES_ACTION 1827L
#define RPC_X_WRONG_ES_VERSION 1828L
#define RPC_X_WRONG_STUB_VERSION 1829L
#define RPC_S_GROUP_MEMBER_NOT_FOUND 1898L
#define EPT_S_CANT_CREATE 1899L
#define RPC_S_INVALID_OBJECT 1900L
#define ERROR_INVALID_TIME 1901L
#define ERROR_INVALID_FORM_NAME 1902L
#define ERROR_INVALID_FORM_SIZE 1903L
#define ERROR_ALREADY_WAITING 1904L
#define ERROR_PRINTER_DELETED 1905L
#define ERROR_INVALID_PRINTER_STATE 1906L
#define ERROR_PASSWORD_MUST_CHANGE 1907L
#define ERROR_DOMAIN_CONTROLLER_NOT_FOUND 1908L
#define ERROR_ACCOUNT_LOCKED_OUT 1909L
#define ERROR_NO_BROWSER_SERVERS_FOUND 6118L
#define ERROR_INVALID_PIXEL_FORMAT 2000L
#define ERROR_BAD_DRIVER 2001L
#define ERROR_INVALID_WINDOW_STYLE 2002L
#define ERROR_METAFILE_NOT_SUPPORTED 2003L
#define ERROR_TRANSFORM_NOT_SUPPORTED 2004L
#define ERROR_CLIPPING_NOT_SUPPORTED 2005L
#define ERROR_UNKNOWN_PRINT_MONITOR 3000L
#define ERROR_PRINTER_DRIVER_IN_USE 3001L
#define ERROR_SPOOL_FILE_NOT_FOUND 3002L
#define ERROR_SPL_NO_STARTDOC 3003L
#define ERROR_SPL_NO_ADDJOB 3004L
#define ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED 3005L
#define ERROR_PRINT_MONITOR_ALREADY_INSTALLED 3006L
#define ERROR_WINS_INTERNAL 4000L
#define ERROR_CAN_NOT_DEL_LOCAL_WINS 4001L
#define ERROR_STATIC_INIT 4002L
#define ERROR_INC_BACKUP 4003L
#define ERROR_FULL_BACKUP 4004L
#define ERROR_REC_NON_EXISTENT 4005L
#define ERROR_RPL_NOT_ALLOWED 4006L
#define SEVERITY_SUCCESS 0
#define SEVERITY_ERROR 1
#define FACILITY_WINDOWS 8
#define FACILITY_STORAGE 3
#define FACILITY_RPC 1
#define FACILITY_WIN32 7
#define FACILITY_CONTROL 10
#define FACILITY_NULL 0
#define FACILITY_ITF 4
#define FACILITY_DISPATCH 2
#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
#define FAILED(Status) ((HRESULT)(Status)<0)
#define IS_ERROR(Status) ((unsigned long)(Status) >> 31 == SEVERITY_ERROR)
#define HRESULT_CODE(r) ((r)&0xFFFF)
#define SCODE_CODE(c) ((c)&0xFFFF)
#define HRESULT_FACILITY(r) (((r)>>16)&0x1fff)
#define SCODE_FACILITY(c) (((c)>>16)&0x1fff)
#define HRESULT_SEVERITY(r) (((r)>>31)&0x1)
#define SCODE_SEVERITY(c) (((c)>>31)&0x1)
#define MAKE_HRESULT(s,f,c) ((HRESULT)(((unsigned long)(s)<<31)|((unsigned long)(f)<<16)|((unsigned long)(c))))
#define MAKE_SCODE(s,f,c) ((SCODE)(((unsigned long)(s)<<31)|((unsigned long)(f)<<16)|((unsigned long)(c))) )
#define FACILITY_NT_BIT 0x10000000
#define HRESULT_FROM_WIN32(x) (x?((HRESULT)(((x)&0x0000FFFF)|(FACILITY_WIN32<<16)|0x80000000)):0)
#define HRESULT_FROM_NT(x) ((HRESULT)((x)|FACILITY_NT_BIT))
#define GetScode(hr) ((SCODE) (hr))
#define ResultFromScode(sc) ((HRESULT) (sc))
#define PropagateResult(hrPrevious, scBase) ((HRESULT) scBase)
#define NOERROR S_OK
#define E_UNEXPECTED 0x8000FFFFL
#define E_NOTIMPL 0x80004001L
#define E_OUTOFMEMORY 0x8007000EL
#define E_INVALIDARG 0x80070057L
#define E_NOINTERFACE 0x80004002L
#define E_POINTER 0x80004003L
#define E_HANDLE 0x80070006L
#define E_ABORT 0x80004004L
#define E_FAIL 0x80004005L
#define E_ACCESSDENIED 0x80070005L
#define CO_E_INIT_TLS 0x80004006L
#define CO_E_INIT_SHARED_ALLOCATOR 0x80004007L
#define CO_E_INIT_MEMORY_ALLOCATOR 0x80004008L
#define CO_E_INIT_CLASS_CACHE 0x80004009L
#define CO_E_INIT_RPC_CHANNEL 0x8000400AL
#define CO_E_INIT_TLS_SET_CHANNEL_CONTROL 0x8000400BL
#define CO_E_INIT_TLS_CHANNEL_CONTROL 0x8000400CL
#define CO_E_INIT_UNACCEPTED_USER_ALLOCATOR 0x8000400DL
#define CO_E_INIT_SCM_MUTEX_EXISTS 0x8000400EL
#define CO_E_INIT_SCM_FILE_MAPPING_EXISTS 0x8000400FL
#define CO_E_INIT_SCM_MAP_VIEW_OF_FILE 0x80004010L
#define CO_E_INIT_SCM_EXEC_FAILURE 0x80004011L
#define CO_E_INIT_ONLY_SINGLE_THREADED 0x80004012L
#define S_OK (0x00000000L)
#define S_FALSE (0x00000001L)
#define OLE_E_FIRST 0x80040000L
#define OLE_E_LAST 0x800400FFL
#define OLE_S_FIRST 0x00040000L
#define OLE_S_LAST 0x000400FFL
#define OLE_E_OLEVERB 0x80040000L
#define OLE_E_ADVF 0x80040001L
#define OLE_E_ENUM_NOMORE 0x80040002L
#define OLE_E_ADVISENOTSUPPORTED 0x80040003L
#define OLE_E_NOCONNECTION 0x80040004L
#define OLE_E_NOTRUNNING 0x80040005L
#define OLE_E_NOCACHE 0x80040006L
#define OLE_E_BLANK 0x80040007L
#define OLE_E_CLASSDIFF 0x80040008L
#define OLE_E_CANT_GETMONIKER 0x80040009L
#define OLE_E_CANT_BINDTOSOURCE 0x8004000AL
#define OLE_E_STATIC 0x8004000BL
#define OLE_E_PROMPTSAVECANCELLED 0x8004000CL
#define OLE_E_INVALIDRECT 0x8004000DL
#define OLE_E_WRONGCOMPOBJ 0x8004000EL
#define OLE_E_INVALIDHWND 0x8004000FL
#define OLE_E_NOT_INPLACEACTIVE 0x80040010L
#define OLE_E_CANTCONVERT 0x80040011L
#define OLE_E_NOSTORAGE 0x80040012L
#define DV_E_FORMATETC 0x80040064L
#define DV_E_DVTARGETDEVICE 0x80040065L
#define DV_E_STGMEDIUM 0x80040066L
#define DV_E_STATDATA 0x80040067L
#define DV_E_LINDEX 0x80040068L
#define DV_E_TYMED 0x80040069L
#define DV_E_CLIPFORMAT 0x8004006AL
#define DV_E_DVASPECT 0x8004006BL
#define DV_E_DVTARGETDEVICE_SIZE 0x8004006CL
#define DV_E_NOIVIEWOBJECT 0x8004006DL
#define DRAGDROP_E_FIRST 0x80040100L
#define DRAGDROP_E_LAST 0x8004010FL
#define DRAGDROP_S_FIRST 0x00040100L
#define DRAGDROP_S_LAST 0x0004010FL
#define DRAGDROP_E_NOTREGISTERED 0x80040100L
#define DRAGDROP_E_ALREADYREGISTERED 0x80040101L
#define DRAGDROP_E_INVALIDHWND 0x80040102L
#define CLASSFACTORY_E_FIRST 0x80040110L
#define CLASSFACTORY_E_LAST 0x8004011FL
#define CLASSFACTORY_S_FIRST 0x00040110L
#define CLASSFACTORY_S_LAST 0x0004011FL
#define CLASS_E_NOAGGREGATION 0x80040110L
#define CLASS_E_CLASSNOTAVAILABLE 0x80040111L
#define MARSHAL_E_FIRST 0x80040120L
#define MARSHAL_E_LAST 0x8004012FL
#define MARSHAL_S_FIRST 0x00040120L
#define MARSHAL_S_LAST 0x0004012FL
#define DATA_E_FIRST 0x80040130L
#define DATA_E_LAST 0x8004013FL
#define DATA_S_FIRST 0x00040130L
#define DATA_S_LAST 0x0004013FL
#define VIEW_E_FIRST 0x80040140L
#define VIEW_E_LAST 0x8004014FL
#define VIEW_S_FIRST 0x00040140L
#define VIEW_S_LAST 0x0004014FL
#define VIEW_E_DRAW 0x80040140L
#define REGDB_E_FIRST 0x80040150L
#define REGDB_E_LAST 0x8004015FL
#define REGDB_S_FIRST 0x00040150L
#define REGDB_S_LAST 0x0004015FL
#define REGDB_E_READREGDB 0x80040150L
#define REGDB_E_WRITEREGDB 0x80040151L
#define REGDB_E_KEYMISSING 0x80040152L
#define REGDB_E_INVALIDVALUE 0x80040153L
#define REGDB_E_CLASSNOTREG 0x80040154L
#define REGDB_E_IIDNOTREG 0x80040155L
#define CACHE_E_FIRST 0x80040170L
#define CACHE_E_LAST 0x8004017FL
#define CACHE_S_FIRST 0x00040170L
#define CACHE_S_LAST 0x0004017FL
#define CACHE_E_NOCACHE_UPDATED 0x80040170L
#define OLEOBJ_E_FIRST 0x80040180L
#define OLEOBJ_E_LAST 0x8004018FL
#define OLEOBJ_S_FIRST 0x00040180L
#define OLEOBJ_S_LAST 0x0004018FL
#define OLEOBJ_E_NOVERBS 0x80040180L
#define OLEOBJ_E_INVALIDVERB 0x80040181L
#define CLIENTSITE_E_FIRST 0x80040190L
#define CLIENTSITE_E_LAST 0x8004019FL
#define CLIENTSITE_S_FIRST 0x00040190L
#define CLIENTSITE_S_LAST 0x0004019FL
#define INPLACE_E_NOTUNDOABLE 0x800401A0L
#define INPLACE_E_NOTOOLSPACE 0x800401A1L
#define INPLACE_E_FIRST 0x800401A0L
#define INPLACE_E_LAST 0x800401AFL
#define INPLACE_S_FIRST 0x000401A0L
#define INPLACE_S_LAST 0x000401AFL
#define ENUM_E_FIRST 0x800401B0L
#define ENUM_E_LAST 0x800401BFL
#define ENUM_S_FIRST 0x000401B0L
#define ENUM_S_LAST 0x000401BFL
#define CONVERT10_E_FIRST 0x800401C0L
#define CONVERT10_E_LAST 0x800401CFL
#define CONVERT10_S_FIRST 0x000401C0L
#define CONVERT10_S_LAST 0x000401CFL
#define CONVERT10_E_OLESTREAM_GET 0x800401C0L
#define CONVERT10_E_OLESTREAM_PUT 0x800401C1L
#define CONVERT10_E_OLESTREAM_FMT 0x800401C2L
#define CONVERT10_E_OLESTREAM_BITMAP_TO_DIB 0x800401C3L
#define CONVERT10_E_STG_FMT 0x800401C4L
#define CONVERT10_E_STG_NO_STD_STREAM 0x800401C5L
#define CONVERT10_E_STG_DIB_TO_BITMAP 0x800401C6L
#define CLIPBRD_E_FIRST 0x800401D0L
#define CLIPBRD_E_LAST 0x800401DFL
#define CLIPBRD_S_FIRST 0x000401D0L
#define CLIPBRD_S_LAST 0x000401DFL
#define CLIPBRD_E_CANT_OPEN 0x800401D0L
#define CLIPBRD_E_CANT_EMPTY 0x800401D1L
#define CLIPBRD_E_CANT_SET 0x800401D2L
#define CLIPBRD_E_BAD_DATA 0x800401D3L
#define CLIPBRD_E_CANT_CLOSE 0x800401D4L
#define MK_E_FIRST 0x800401E0L
#define MK_E_LAST 0x800401EFL
#define MK_S_FIRST 0x000401E0L
#define MK_S_LAST 0x000401EFL
#define MK_E_CONNECTMANUALLY 0x800401E0L
#define MK_E_EXCEEDEDDEADLINE 0x800401E1L
#define MK_E_NEEDGENERIC 0x800401E2L
#define MK_E_UNAVAILABLE 0x800401E3L
#define MK_E_SYNTAX 0x800401E4L
#define MK_E_NOOBJECT 0x800401E5L
#define MK_E_INVALIDEXTENSION 0x800401E6L
#define MK_E_INTERMEDIATEINTERFACENOTSUPPORTED 0x800401E7L
#define MK_E_NOTBINDABLE 0x800401E8L
#define MK_E_NOTBOUND 0x800401E9L
#define MK_E_CANTOPENFILE 0x800401EAL
#define MK_E_MUSTBOTHERUSER 0x800401EBL
#define MK_E_NOINVERSE 0x800401ECL
#define MK_E_NOSTORAGE 0x800401EDL
#define MK_E_NOPREFIX 0x800401EEL
#define MK_E_ENUMERATION_FAILED 0x800401EFL
#define CO_E_FIRST 0x800401F0L
#define CO_E_LAST 0x800401FFL
#define CO_S_FIRST 0x000401F0L
#define CO_S_LAST 0x000401FFL
#define CO_E_NOTINITIALIZED 0x800401F0L
#define CO_E_ALREADYINITIALIZED 0x800401F1L
#define CO_E_CANTDETERMINECLASS 0x800401F2L
#define CO_E_CLASSSTRING 0x800401F3L
#define CO_E_IIDSTRING 0x800401F4L
#define CO_E_APPNOTFOUND 0x800401F5L
#define CO_E_APPSINGLEUSE 0x800401F6L
#define CO_E_ERRORINAPP 0x800401F7L
#define CO_E_DLLNOTFOUND 0x800401F8L
#define CO_E_ERRORINDLL 0x800401F9L
#define CO_E_WRONGOSFORAPP 0x800401FAL
#define CO_E_OBJNOTREG 0x800401FBL
#define CO_E_OBJISREG 0x800401FCL
#define CO_E_OBJNOTCONNECTED 0x800401FDL
#define CO_E_APPDIDNTREG 0x800401FEL
#define CO_E_RELEASED 0x800401FFL
#define OLE_S_USEREG 0x00040000L
#define OLE_S_STATIC 0x00040001L
#define OLE_S_MAC_CLIPFORMAT 0x00040002L
#define DRAGDROP_S_DROP 0x00040100L
#define DRAGDROP_S_CANCEL 0x00040101L
#define DRAGDROP_S_USEDEFAULTCURSORS 0x00040102L
#define DATA_S_SAMEFORMATETC 0x00040130L
#define VIEW_S_ALREADY_FROZEN 0x00040140L
#define CACHE_S_FORMATETC_NOTSUPPORTED 0x00040170L
#define CACHE_S_SAMECACHE 0x00040171L
#define CACHE_S_SOMECACHES_NOTUPDATED 0x00040172L
#define OLEOBJ_S_INVALIDVERB 0x00040180L
#define OLEOBJ_S_CANNOT_DOVERB_NOW 0x00040181L
#define OLEOBJ_S_INVALIDHWND 0x00040182L
#define INPLACE_S_TRUNCATED 0x000401A0L
#define CONVERT10_S_NO_PRESENTATION 0x000401C0L
#define MK_S_REDUCED_TO_SELF 0x000401E2L
#define MK_S_ME 0x000401E4L
#define MK_S_HIM 0x000401E5L
#define MK_S_US 0x000401E6L
#define MK_S_MONIKERALREADYREGISTERED 0x000401E7L
#define CO_E_CLASS_CREATE_FAILED 0x80080001L
#define CO_E_SCM_ERROR 0x80080002L
#define CO_E_SCM_RPC_FAILURE 0x80080003L
#define CO_E_BAD_PATH 0x80080004L
#define CO_E_SERVER_EXEC_FAILURE 0x80080005L
#define CO_E_OBJSRV_RPC_FAILURE 0x80080006L
#define MK_E_NO_NORMALIZED 0x80080007L
#define CO_E_SERVER_STOPPING 0x80080008L
#define MEM_E_INVALID_ROOT 0x80080009L
#define MEM_E_INVALID_LINK 0x80080010L
#define MEM_E_INVALID_SIZE 0x80080011L
#define DISP_E_UNKNOWNINTERFACE 0x80020001L
#define DISP_E_MEMBERNOTFOUND 0x80020003L
#define DISP_E_PARAMNOTFOUND 0x80020004L
#define DISP_E_TYPEMISMATCH 0x80020005L
#define DISP_E_UNKNOWNNAME 0x80020006L
#define DISP_E_NONAMEDARGS 0x80020007L
#define DISP_E_BADVARTYPE 0x80020008L
#define DISP_E_EXCEPTION 0x80020009L
#define DISP_E_OVERFLOW 0x8002000AL
#define DISP_E_BADINDEX 0x8002000BL
#define DISP_E_UNKNOWNLCID 0x8002000CL
#define DISP_E_ARRAYISLOCKED 0x8002000DL
#define DISP_E_BADPARAMCOUNT 0x8002000EL
#define DISP_E_PARAMNOTOPTIONAL 0x8002000FL
#define DISP_E_BADCALLEE 0x80020010L
#define DISP_E_NOTACOLLECTION 0x80020011L
#define TYPE_E_BUFFERTOOSMALL 0x80028016L
#define TYPE_E_INVDATAREAD 0x80028018L
#define TYPE_E_UNSUPFORMAT 0x80028019L
#define TYPE_E_REGISTRYACCESS 0x8002801CL
#define TYPE_E_LIBNOTREGISTERED 0x8002801DL
#define TYPE_E_UNDEFINEDTYPE 0x80028027L
#define TYPE_E_QUALIFIEDNAMEDISALLOWED 0x80028028L
#define TYPE_E_INVALIDSTATE 0x80028029L
#define TYPE_E_WRONGTYPEKIND 0x8002802AL
#define TYPE_E_ELEMENTNOTFOUND 0x8002802BL
#define TYPE_E_AMBIGUOUSNAME 0x8002802CL
#define TYPE_E_NAMECONFLICT 0x8002802DL
#define TYPE_E_UNKNOWNLCID 0x8002802EL
#define TYPE_E_DLLFUNCTIONNOTFOUND 0x8002802FL
#define TYPE_E_BADMODULEKIND 0x800288BDL
#define TYPE_E_SIZETOOBIG 0x800288C5L
#define TYPE_E_DUPLICATEID 0x800288C6L
#define TYPE_E_INVALIDID 0x800288CFL
#define TYPE_E_TYPEMISMATCH 0x80028CA0L
#define TYPE_E_OUTOFBOUNDS 0x80028CA1L
#define TYPE_E_IOERROR 0x80028CA2L
#define TYPE_E_CANTCREATETMPFILE 0x80028CA3L
#define TYPE_E_CANTLOADLIBRARY 0x80029C4AL
#define TYPE_E_INCONSISTENTPROPFUNCS 0x80029C83L
#define TYPE_E_CIRCULARTYPE 0x80029C84L
#define STG_E_INVALIDFUNCTION 0x80030001L
#define STG_E_FILENOTFOUND 0x80030002L
#define STG_E_PATHNOTFOUND 0x80030003L
#define STG_E_TOOMANYOPENFILES 0x80030004L
#define STG_E_ACCESSDENIED 0x80030005L
#define STG_E_INVALIDHANDLE 0x80030006L
#define STG_E_INSUFFICIENTMEMORY 0x80030008L
#define STG_E_INVALIDPOINTER 0x80030009L
#define STG_E_NOMOREFILES 0x80030012L
#define STG_E_DISKISWRITEPROTECTED 0x80030013L
#define STG_E_SEEKERROR 0x80030019L
#define STG_E_WRITEFAULT 0x8003001DL
#define STG_E_READFAULT 0x8003001EL
#define STG_E_SHAREVIOLATION 0x80030020L
#define STG_E_LOCKVIOLATION 0x80030021L
#define STG_E_FILEALREADYEXISTS 0x80030050L
#define STG_E_INVALIDPARAMETER 0x80030057L
#define STG_E_MEDIUMFULL 0x80030070L
#define STG_E_ABNORMALAPIEXIT 0x800300FAL
#define STG_E_INVALIDHEADER 0x800300FBL
#define STG_E_INVALIDNAME 0x800300FCL
#define STG_E_UNKNOWN 0x800300FDL
#define STG_E_UNIMPLEMENTEDFUNCTION 0x800300FEL
#define STG_E_INVALIDFLAG 0x800300FFL
#define STG_E_INUSE 0x80030100L
#define STG_E_NOTCURRENT 0x80030101L
#define STG_E_REVERTED 0x80030102L
#define STG_E_CANTSAVE 0x80030103L
#define STG_E_OLDFORMAT 0x80030104L
#define STG_E_OLDDLL 0x80030105L
#define STG_E_SHAREREQUIRED 0x80030106L
#define STG_E_NOTFILEBASEDSTORAGE 0x80030107L
#define STG_E_EXTANTMARSHALLINGS 0x80030108L
#define STG_S_CONVERTED 0x00030200L
#define RPC_E_CALL_REJECTED 0x80010001L
#define RPC_E_CALL_CANCELED 0x80010002L
#define RPC_E_CANTPOST_INSENDCALL 0x80010003L
#define RPC_E_CANTCALLOUT_INASYNCCALL 0x80010004L
#define RPC_E_CANTCALLOUT_INEXTERNALCALL 0x80010005L
#define RPC_E_CONNECTION_TERMINATED 0x80010006L
#define RPC_E_SERVER_DIED 0x80010007L
#define RPC_E_CLIENT_DIED 0x80010008L
#define RPC_E_INVALID_DATAPACKET 0x80010009L
#define RPC_E_CANTTRANSMIT_CALL 0x8001000AL
#define RPC_E_CLIENT_CANTMARSHAL_DATA 0x8001000BL
#define RPC_E_CLIENT_CANTUNMARSHAL_DATA 0x8001000CL
#define RPC_E_SERVER_CANTMARSHAL_DATA 0x8001000DL
#define RPC_E_SERVER_CANTUNMARSHAL_DATA 0x8001000EL
#define RPC_E_INVALID_DATA 0x8001000FL
#define RPC_E_INVALID_PARAMETER 0x80010010L
#define RPC_E_CANTCALLOUT_AGAIN 0x80010011L
#define RPC_E_SERVER_DIED_DNE 0x80010012L
#define RPC_E_SYS_CALL_FAILED 0x80010100L
#define RPC_E_OUT_OF_RESOURCES 0x80010101L
#define RPC_E_ATTEMPTED_MULTITHREAD 0x80010102L
#define RPC_E_NOT_REGISTERED 0x80010103L
#define RPC_E_FAULT 0x80010104L
#define RPC_E_SERVERFAULT 0x80010105L
#define RPC_E_CHANGED_MODE 0x80010106L
#define RPC_E_INVALIDMETHOD 0x80010107L
#define RPC_E_DISCONNECTED 0x80010108L
#define RPC_E_RETRY 0x80010109L
#define RPC_E_SERVERCALL_RETRYLATER 0x8001010AL
#define RPC_E_SERVERCALL_REJECTED 0x8001010BL
#define RPC_E_INVALID_CALLDATA 0x8001010CL
#define RPC_E_CANTCALLOUT_ININPUTSYNCCALL 0x8001010DL
#define RPC_E_WRONG_THREAD 0x8001010EL
#define RPC_E_THREAD_NOT_INIT 0x8001010FL
#define RPC_E_UNEXPECTED 0x8001FFFFL
#endif
