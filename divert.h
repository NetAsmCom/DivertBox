#ifndef DIVERT_H
#define DIVERT_H

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32) || defined(WIN32)
    #define DIVERT_PLATFORM_WINDOWS 1
#elif __linux__
    #define DIVERT_PLATFORM_LINUX 1
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define DIVERT_PLATFORM_MACOS 1
    #endif
#endif

#if !defined(DIVERT_PLATFORM_WINDOWS) &&\
    !defined(DIVERT_PLATFORM_LINUX) &&\
    !defined(DIVERT_PLATFORM_MACOS)
    #error "libdivert: unsupported platform"
#endif

/*
 * ==== FILTER LANGUAGE SYNTAX ====
 * (Still very early at the stage, under development)
 * 
 *  [] Filter
 *      | (binary operator)
 *      & (binary operator)
 *      ! (unary operator)
 * 
 *  : Type
 *      inbound
 *      outbound
 *      ip4
 *      ip6
 *      udp
 *      icmp
 *      tcp
 * 
 *  {} Condition
 *      = (binary operator)
 *      > (binary operator)
 *      < (binary operator)
 *      ! (unary operator)
 * 
 *  () Group
 *      filter
 *      condition
 * 
 *  Examples
 * 
 *  Capture outgoing DNS traffic
 *  [outbound] & ([tcp: { port = 53 }] | [udp: { port = 53 }])
 * 
 *  Capture incoming HTTP/HTTPS traffic
 *  [inbound] & [ip4] & [tcp: { port = 80 } | { port = 443}]
 * 
 *  Capture incoming not-injected loopback traffic
 *  [inbound: { trait != inject } & { trait = loopback }]
 * 
 */

typedef enum
{
    DV_ERROR_NONE                               = 0,
    DV_ERROR_UNKNOWN                            = 1,
    DV_ERROR_SUPERUSER_REQUIRED                 = 2,
    DV_ERROR_KERNEL_SERVICE_CHECKSUM_FAILED     = 3,
    DV_ERROR_KERNEL_SERVICE_LOAD_FAILED         = 4,
    DV_ERROR_KERNEL_SERVICE_CONNECT_FAILED      = 5,
    DV_ERROR_KERNEL_SERVICE_UNLOAD_FAILED       = 6,
} dv_error_t;

typedef enum
{
    DV_MODE_DIVERT      = 0xA,
    DV_MODE_SNIFF       = 0xB,
    DV_MODE_INFO        = 0xC
} dv_mode_t;

typedef enum
{
    DV_STATUS_IDLE      = 0x0,
    DV_STATUS_LIMBO     = 0x6,
    DV_STATUS_READY     = 0xA,
    DV_STATUS_ACTIVE    = 0xF
} dv_status_t;

dv_status_t divert_status(void);
dv_error_t divert_open(void);
dv_error_t divert_close(void);

dv_error_t divert_filter_add(const uint8_t* buffer, size_t buffer_length);
dv_error_t divert_filter_get(size_t index, uint8_t* buffer, size_t buffer_length, size_t* output_length);
dv_error_t divert_filter_remove(size_t index);
dv_error_t divert_filter_count(size_t* count);
dv_error_t divert_filter_clear(void);

dv_error_t divert_start(dv_mode_t mode);
dv_error_t divert_capture(size_t* filter_index, uint8_t* buffer, size_t buffer_length, size_t* output_length);
dv_error_t divert_inject(const uint8_t* buffer, size_t buffer_length);
dv_error_t divert_stop(void);

#endif // DIVERT_H
