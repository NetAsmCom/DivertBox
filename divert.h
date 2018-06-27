#ifndef DIVERT_H
#define DIVERT_H

#define DIVERT_TYPE_IPV4_UDP    0xA
#define DIVERT_TYPE_IPV4_ICMP   0xB
#define DIVERT_TYPE_IPV4_TCP    0xC
#define DIVERT_TYPE_IPV6_UDP    0xD
#define DIVERT_TYPE_IPV6_ICMP   0xE
#define DIVERT_TYPE_IPV6_TCP    0xF

typedef enum
{
    DIVERT_MODE_DIVERT          = 0xA,
    DIVERT_MODE_SNIFF           = 0xB,
    DIVERT_MODE_INFO            = 0xC
} divert_mode_t;

int divert_status(int* status);

int divert_open(void (*handler_func)(int type, void* ip, void* protocol, const char* buffer, int length));
int divert_close(void);

int divert_filter_add(const char* buffer, int length);
int divert_filter_get(int index, char* buffer, int* length);
int divert_filter_remove(int index);
int divert_filter_count(int* count);
int divert_filter_clear(void);

int divert_start(int mode);
int divert_inject(int type, void* ip, void* protocol, const char* buffer, int length);
int divert_stop(void);

#endif // DIVERT_H
