#include "library.h"

#include <CommonCrypto/CommonDigest.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <ftw.h>

// -------- directory exists

int library_directory_exists(const char* path)
{
    struct stat s;
    return stat(path, &s) || !S_ISDIR(s.st_mode);
}

// -------- superuser access

int library_superuser_access()
{
    return geteuid();
}

// -------- md5sum directory

CC_MD5_CTX _library_md5_context;

int _library_md5sum_ftw_handle(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    if (S_ISDIR(sb->st_mode))
    {
        return CC_MD5_Update(&_library_md5_context, fpath, strlen(fpath)) != 1;
    }

    if (S_ISREG(sb->st_mode))
    {
        FILE* file = fopen(fpath, "rb");
        if (file == NULL) { return 0; }

        char buffer[UINT8_MAX];
        size_t length = 0;

        do
        {
            length = fread(buffer, 1, UINT8_MAX, file);

            if (CC_MD5_Update(&_library_md5_context, buffer, length) != 1)
            {
                fclose(file);
                return 1;
            }
        }
        while (length > 0);

        fclose(file);
    }

    return 0;
}

int library_md5sum_directory(const char* path, unsigned char* checksum)
{
    return
        CC_MD5_Init(&_library_md5_context) != 1 ||
        CC_MD5_Update(&_library_md5_context, kBUNDLE_ID, strlen(kBUNDLE_ID)) != 1 ||
        nftw(path, &_library_md5sum_ftw_handle, 4, FTW_PHYS | FTW_DEPTH) ||
        CC_MD5_Final(checksum, &_library_md5_context) != 1;
}

// -------- chown directory

uid_t _library_chown_user_id = 0;
gid_t _library_chown_group_id = 0;

int _library_chown_ftw_handle(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    if (S_ISDIR(sb->st_mode) || S_ISREG(sb->st_mode))
    {
        return chown(fpath, _library_chown_user_id, _library_chown_group_id);
    }

    return 0;
}

int library_chown_directory(const char* path, const char* user, const char* group)
{
    _library_chown_user_id = 0;
    {
        struct passwd* pwd = getpwnam(user);
        if (pwd == NULL) { return -1; }
        _library_chown_user_id = pwd->pw_uid;
    }

    _library_chown_group_id = 0;
    {
        struct group* grp = getgrnam(group);
        if (grp == NULL) { return -1; }
        _library_chown_group_id = grp->gr_gid;
    }

    return nftw(path, &_library_chown_ftw_handle, 4, FTW_PHYS | FTW_DEPTH);
}
