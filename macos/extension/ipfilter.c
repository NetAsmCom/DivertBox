#include "divert.h"

#include <netinet/kpi_ipfilter.h>

#define FUNCTION "filter_handle_input_v4"
errno_t filter_handle_input_v4(void* cookie, mbuf_t* data, int offset, u_int8_t protocol)
{
    return 0;
}
#undef FUNCTION

#define FUNCTION "filter_handle_output_v4"
errno_t filter_handle_output_v4(void* cookie, mbuf_t* data, ipf_pktopts_t options)
{
    return 0;
}
#undef FUNCTION

#define FUNCTION "filter_handle_detach_v4"
void filter_handle_detach_v4(void* cookie)
{
}
#undef FUNCTION

#define FUNCTION "filter_handle_input_v6"
errno_t filter_handle_input_v6(void* cookie, mbuf_t* data, int offset, u_int8_t protocol)
{
    return 0;
}
#undef FUNCTION

#define FUNCTION "filter_handle_output_v6"
errno_t filter_handle_output_v6(void* cookie, mbuf_t* data, ipf_pktopts_t options)
{
    return 0;
}
#undef FUNCTION

#define FUNCTION "filter_handle_detach_v6"
void filter_handle_detach_v6(void* cookie)
{
}
#undef FUNCTION

struct ipf_filter filter_v4 =
{
    (void*)0xCAFEBABE,
    "DivertIPv4Filter",
    &filter_handle_input_v4,
    &filter_handle_output_v4,
    &filter_handle_detach_v4
};

ipfilter_t filter_v4_ref = 0;

struct ipf_filter filter_v6 =
{
    (void*)0xDEADC0DE,
    "DivertIPv6Filter",
    &filter_handle_input_v6,
    &filter_handle_output_v6,
    &filter_handle_detach_v6
};

ipfilter_t filter_v6_ref = 0;

#define FUNCTION "ipfilter_add"
kern_return_t ipfilter_add()
{
    errno_t error = ipf_addv4(&filter_v4, &filter_v4_ref);
    if (error != 0)
    {
        LOGF("cannot add IPv4 filter > error: %d", error);
        ipfilter_remove();
        return KERN_FAILURE;
    }
    LOG("IPv4 filter added");

    error = ipf_addv6(&filter_v6, &filter_v6_ref);
    if (error != 0)
    {
        LOGF("cannot add IPv6 filter > error: %d", error);
        ipfilter_remove();
        return KERN_FAILURE;
    }
    LOG("IPv6 filter added");

    return KERN_SUCCESS;
}
#undef FUNCTION

#define FUNCTION "ipfilter_remove"
kern_return_t ipfilter_remove()
{
    kern_return_t result = KERN_SUCCESS;
    errno_t error = 0;

    if (filter_v4_ref == 0)
    {
        LOG("IPv4 filter already removed");
    }
    else
    {
        error = ipf_remove(filter_v4_ref);
        if (error != 0)
        {
            LOGF("cannot remove IPv4 filter > error: %d", error);
            result = KERN_FAILURE;
        }
        else
        {
            filter_v4_ref = 0;

            LOG("IPv4 filter removed");
        }
    }

    if (filter_v6_ref == 0)
    {
        LOG("IPv6 filter already removed");
    }
    else
    {
        error = ipf_remove(filter_v6_ref);
        if (error != 0)
        {
            LOGF("cannot remove IPv6 filter > error: %d", error);
            result = KERN_FAILURE;
        }
        else
        {
            filter_v6_ref = 0;

            LOG("IPv6 filter removed");
        }
    }

    return result;
}
#undef FUNCTION
