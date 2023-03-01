#include "P2r_api.h"

ret_val P2rClientInit(long id, const char *server, unsigned short port);
ret_val P2rClientRelease();
ret_val SendP2RSpeedLevelNotification(double speed);
ret_val SendP2RSessionTerminationWarning(long time, long warning_id, int reason);
ret_val SendP2RSessionTerminationWarningCancel(long warning_id);
ret_val SendP2RSessionRestoreWarning(long time);