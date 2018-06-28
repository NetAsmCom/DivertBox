#ifndef DIVERT_H
#define DIVERT_H

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32) || defined(WIN32)
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

typedef void* dv_raw_ptr_t;

typedef enum
{
    DV_ERROR_NONE       = 0
} dv_error_t;

typedef enum
{
    DV_TYPE_IPV4_UDP    = 0xA,
    DV_TYPE_IPV4_ICMP   = 0xB,
    DV_TYPE_IPV4_TCP    = 0xC,
    DV_TYPE_IPV6_UDP    = 0xD,
    DV_TYPE_IPV6_ICMP   = 0xE,
    DV_TYPE_IPV6_TCP    = 0xF
} dv_packet_type_t;

typedef enum
{
    DV_MODE_DIVERT      = 0xA,
    DV_MODE_SNIFF       = 0xB,
    DV_MODE_INFO        = 0xC
} dv_capture_mode_t;

typedef enum
{
    DV_STATUS_IDLE      = 0x0,
    DV_STATUS_READY     = 0xA,
    DV_STATUS_ACTIVE    = 0xF
} dv_status_t;

typedef struct
{
    // TODO
} dv_ipv4_header_t;
typedef struct
{
    // TODO
} dv_ipv6_header_t;
typedef struct
{
    uint16_t source_port;
    uint16_t destination_port;
    uint16_t length;
    uint16_t checksum;
} dv_udp_header_t;
typedef struct
{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
} dv_icmp_header_t;
typedef struct
{
    uint16_t source_port;
    uint16_t destination_port;
    uint32_t sequence_number;
    uint32_t acknowledgement_number;
    uint8_t data_offset:4,
            reserved:4;
    uint8_t cwr_flag:1,
            ece_flag:1,
            urg_flag:1,
            ack_flag:1,
            psh_flag:1,
            rst_flag:1,
            syn_flag:1,
            fin_flag:1;
    uint16_t window_size;
    uint16_t checksum;
    uint16_t urgent_pointer;
    // TODO: options
} dv_tcp_header_t; // TODO: needs testing

typedef void (*dv_handler_func_t)(dv_packet_type_t type, const dv_raw_ptr_t ip_header, const dv_raw_ptr_t protocol_header, const uint8_t* buffer, size_t length);

dv_error_t divert_status(dv_status_t* status);

dv_error_t divert_open(dv_handler_func_t handler);
dv_error_t divert_close(void);

dv_error_t divert_filter_add(const uint8_t* buffer, size_t length);
dv_error_t divert_filter_get(size_t index, uint8_t* buffer, size_t* length);
dv_error_t divert_filter_remove(size_t index);
dv_error_t divert_filter_count(size_t* count);
dv_error_t divert_filter_clear(void);

dv_error_t divert_start(dv_capture_mode_t mode);
dv_error_t divert_inject(dv_packet_type_t type, const dv_raw_ptr_t ip_header, const dv_raw_ptr_t protocol_header, const uint8_t* buffer, size_t length);
dv_error_t divert_stop(void);

#endif // DIVERT_H
