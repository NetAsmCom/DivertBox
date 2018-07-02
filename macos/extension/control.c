#include "divert.h"

#include <sys/kern_control.h>

u_int32_t active_unit = 0;

#define FUNCTION "control_handle_connect"
errno_t control_handle_connect(kern_ctl_ref kctlref, struct sockaddr_ctl* sac, void** unitinfo)
{
    if (active_unit != 0)
    {
        LOG("another unit already active");
        return EBUSY;
    }

    active_unit = sac->sc_unit;

    LOGF("unit connected > unit: %d", active_unit);
    return 0;
}
#undef FUNCTION

#define FUNCTION "control_handle_disconnect"
errno_t control_handle_disconnect(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo)
{
    if (unit == active_unit)
    {
        active_unit = 0;

        LOG("active unit disconnected");
    }

    return 0;
}
#undef FUNCTION

#define FUNCTION "control_handle_send"
errno_t control_handle_send(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, mbuf_t m, int flags)
{
    return 0;
}
#undef FUNCTION

#define FUNCTION "control_handle_setopt"
errno_t control_handle_setopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t len)
{
    return 0;
}
#undef FUNCTION

#define FUNCTION "control_handle_getopt"
errno_t control_handle_getopt(kern_ctl_ref kctlref, u_int32_t unit, void* unitinfo, int opt, void* data, size_t* len)
{
    return 0;
}
#undef FUNCTION

struct kern_ctl_reg control_reg =
{
    kBUNDLE_ID,
    0, // dynamic ID
    0, // dynamic ignored
    CTL_FLAG_PRIVILEGED, // super-user
    0, // default send size
    0, // default receive size
    &control_handle_connect,
    &control_handle_disconnect,
    &control_handle_send,
    &control_handle_setopt,
    &control_handle_getopt
};

kern_ctl_ref control_ref = 0;

#define FUNCTION "control_register"
kern_return_t control_register()
{
    errno_t error = ctl_register(&control_reg, &control_ref);
    if (error != 0)
    {
        LOGF("cannot register control > error: %d", error);
        return KERN_FAILURE;
    }

    LOG("control registered");
    return KERN_SUCCESS;
}
#undef FUNCTION

#define FUNCTION "control_deregister"
kern_return_t control_deregister()
{
    if (control_ref == 0)
    {
        LOG("control already deregistered");
        return KERN_SUCCESS;
    }

    if (active_unit != 0)
    {
        LOGF("unit active on control > unit: %d", active_unit);
        return KERN_FAILURE;
    }

    errno_t error = ctl_deregister(control_ref);
    if (error != 0)
    {
        LOGF("cannot deregister control > error: %d", error);
        return KERN_FAILURE;
    }

    control_ref = 0;

    LOG("control deregistered");
    return KERN_SUCCESS;
}
#undef FUNCTION
