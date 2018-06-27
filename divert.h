#ifndef DIVERT_H
#define DIVERT_H

#define DIVERT_MODE_DIVERT 0
#define DIVERT_MODE_SNIFF 1
#define DIVERT_MODE_INFO 2

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
