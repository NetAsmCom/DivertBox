#ifndef DIVERT_H
#define DIVERT_H

#ifdef _WIN32
    #define DIVERT_PLATFORM_WINDOWS
#elif __linux__
    #define DIVERT_PLATFORM_LINUX
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define DIVERT_PLATFORM_MACOS
    #endif
#endif

#if !defined(DIVERT_PLATFORM_WINDOWS) &&\
    !defined(DIVERT_PLATFORM_LINUX) &&\
    !defined(DIVERT_PLATFORM_MACOS)
    #error "libdivert: unsupported platform"
#endif

typedef enum
{
    DIVERT_ERROR_NONE       = 0
} divert_error_t;

typedef enum
{
    DIVERT_TYPE_IPV4_UDP    = 0xA,
    DIVERT_TYPE_IPV4_ICMP   = 0xB,
    DIVERT_TYPE_IPV4_TCP    = 0xC,
    DIVERT_TYPE_IPV6_UDP    = 0xD,
    DIVERT_TYPE_IPV6_ICMP   = 0xE,
    DIVERT_TYPE_IPV6_TCP    = 0xF
} divert_type_t;

typedef enum
{
    DIVERT_MODE_DIVERT      = 0xA,
    DIVERT_MODE_SNIFF       = 0xB,
    DIVERT_MODE_INFO        = 0xC
} divert_mode_t;

typedef enum
{
    DIVERT_STATUS_IDLE      = 0x0,
    DIVERT_STATUS_READY     = 0xA,
    DIVERT_STATUS_ACTIVE    = 0xF
} divert_status_t;

typedef struct { /* TODO */ } divert_ipv4_header_t;
typedef struct { /* TODO */ } divert_ipv6_header_t;
typedef struct { /* TODO */ } divert_udp_header_t;
typedef struct { /* TODO */ } divert_icmp_header_t;
typedef struct { /* TODO */ } divert_tcp_header_t;

typedef void (*divert_handler_func_t)(divert_type_t type, void* ip, void* protocol, const char* buffer, int length);

divert_error_t divert_status(divert_status_t* status);

divert_error_t divert_open(divert_handler_func_t handler);
divert_error_t divert_close(void);

divert_error_t divert_filter_add(const char* buffer, int length);
divert_error_t divert_filter_get(int index, char* buffer, int* length);
divert_error_t divert_filter_remove(int index);
divert_error_t divert_filter_count(int* count);
divert_error_t divert_filter_clear(void);

divert_error_t divert_start(divert_mode_t mode);
divert_error_t divert_inject(divert_type_t type, void* ip, void* protocol, const char* buffer, int length);
divert_error_t divert_stop(void);

#endif // DIVERT_H
