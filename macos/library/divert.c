#include <divert.h>

dv_error_t divert_status(dv_status_t* status)
{
    *status = DV_STATUS_IDLE;
    return DV_ERROR_NONE;
}
