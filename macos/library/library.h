#ifndef LIBRARY_H
#define LIBRARY_H

#define kBUNDLE_ID "com.mfatihmar.divert"
#define kBUNDLE_MD5 "DBA0BB4EA08DD00AD771E99E807B2A86"
#define kBUNDLE_DIR "divert.kext"

int library_directory_exists(const char* path);
int library_superuser_access(void);
int library_md5sum_directory(const char* path, unsigned char* checksum);
int library_string_to_hexstring(const char* string, int string_length, char* hexstring, int hexstring_length);
int library_chown_directory(const char* path, const char* user, const char* group);
int library_kext_load_with_directory(const char* path);
int library_kext_loaded_and_valid(const char* id, const char* path);

#endif // LIBRARY_H
