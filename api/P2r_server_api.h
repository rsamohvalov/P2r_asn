#include "P2r_api.h"

typedef struct _TerminateWarning
{
    int fp_id;
    int warning_id;
    int timeout;
} struct_TerminateWarning;

typedef struct _TerminateCancel
{
    int fp_id;
    int warning_id;
} struct_TerminateCancel;

typedef struct _RestoreWarning
{
    int fp_id;
    int timeout;
} struct_RestoreWarning;

typedef struct _SpeedNotification
{
    int fp_id;
    float speed;
} struct_SpeedNotification;

typedef void (*SpeedNotificationCallback)(struct_SpeedNotification speed);
typedef int (*SessionTerminationCallback)(struct_TerminateWarning termination);
typedef void (*SessionTerminationCancelCallback)(struct_TerminateCancel cancelation);
typedef void (*SessionRestoreCallback)(struct_RestoreWarning restoration);

typedef struct _ApiCallTable
{
    SpeedNotificationCallback speed_notify_callback;
    SessionTerminationCallback terminate_callback;
    SessionTerminationCancelCallback terminate_cancel_callback;
    SessionRestoreCallback restore_callback;
} ApiCallTable;

typedef struct _ServerParameters
{
    int id;
    unsigned short port;
    char addr[64];
    ApiCallTable *callbacks;
} ServerParameters;

ret_val InitServer(char *addr, unsigned short port, int id, ApiCallTable *callbacks);
ret_val StopServer();