#ifndef DIVERT_H
#define DIVERT_H

#define kBUNDLE_ID "com.mfatihmar.divert"

#include <mach/mach_types.h>

kern_return_t divert_start(kmod_info_t* ki, void* d);
kern_return_t divert_stop(kmod_info_t* ki, void* d);

void _log(const char* function, const char* text);
void _logf(const char* function, const char* format, ...);

#define LOG(text) _log(FUNCTION, text)
#define LOGF(format, args...) _logf(FUNCTION, format, args)

#endif // DIVERT_H
