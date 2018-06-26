#ifndef DIVERT_H
#define DIVERT_H

int divert_status(int* status);

int divert_open(void (*handler_func)(int type, void* ip, void* protocol, void* buffer, int length));
int divert_close(void);

int divert_filter_add(void* buffer, int length);
int divert_filter_get(int index, void* buffer, int* length);
int divert_filter_remove(int index);
int divert_filter_count(int* count);
int divert_filter_clear(void);

int divert_start(int mode);
int divert_inject(int type, void* ip, void* protocol, void* buffer, int length);
int divert_stop(void);

#endif // DIVERT_H
