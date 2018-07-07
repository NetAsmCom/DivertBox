#include "library.h"

#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <ftw.h>

int library_directory_exists(const char* path)
{
    struct stat s;
    return stat(path, &s) || !S_ISDIR(s.st_mode);
}

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
