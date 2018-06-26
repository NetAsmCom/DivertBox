#ifndef divert_h
#define divert_h

int divert_status();

int divert_open();
int divert_close();

int divert_filter_add();
int divert_filter_get();
int divert_filter_remove();
int divert_filter_count();
int divert_filter_clear();

int divert_start();
int divert_inject();
int divert_stop();

#endif // divert_h
