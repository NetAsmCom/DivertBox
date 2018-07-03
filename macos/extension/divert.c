#include "divert.h"

#include <stdarg.h>

#define FUNCTION "divert_start"
kern_return_t divert_start(kmod_info_t* ki, void* d)
{
    LOG("call");
    return control_register();
}
#undef FUNCTION

#define FUNCTION "divert_stop"
kern_return_t divert_stop(kmod_info_t* ki, void* d)
{
    LOG("call");
    return control_deregister();
}
#undef FUNCTION

void _log(const char* function, const char* text)
{
    printf("["kBUNDLE_ID"] @%s(): %s\n", function, text);
}

void _logf(const char* function, const char* format, ...)
{
    va_list list;
    va_start(list, format);
    
    char buffer[UINT8_MAX];
    vsnprintf(buffer, UINT8_MAX, format, list);

    _log(function, buffer);

    va_end(list);
}
