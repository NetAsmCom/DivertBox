#include <divert.h>
#include "library.h"

dv_status_t _status = DV_STATUS_IDLE;

dv_status_t divert_status()
{
    return _status;
}

dv_error_t divert_open()
{
    if (library_superuser_access())
    {
        return DV_ERROR_SUPERUSER_REQUIRED;
    }

    if (library_directory_exists(kBUNDLE_DIR))
    {
        return DV_ERROR_KERNEL_SERVICE_LOAD_FAILED;
    }

    /*

    ! DISABLED FOR DEVELOPMENT PURPOSES
    ! MUST BE ENABLED ON RELEASE BUILDS

    char directory_md5sum[16];
    if (library_directory_md5sum(kBUNDLE_DIR, directory_md5sum))
    {
        return DV_ERROR_KERNEL_SERVICE_CHECKSUM_FAILED;
    }

    if (strncmp(directory_md5sum, kBUNDLE_MD5, 16))
    {
        return DV_ERROR_KERNEL_SERVICE_CHECKSUM_FAILED;
    }

    */

    if (library_directory_chown(kBUNDLE_DIR, "root", "wheel"))
    {
        return DV_ERROR_KERNEL_SERVICE_LOAD_FAILED;
    }

    if (library_kext_load_with_directory(kBUNDLE_DIR))
    {
        return DV_ERROR_KERNEL_SERVICE_LOAD_FAILED;
    }
    
    if (library_kext_loaded_and_valid(kBUNDLE_ID, kBUNDLE_DIR))
    {
        _status = library_kext_unload_with_directory(kBUNDLE_DIR) ? DV_STATUS_LIMBO : DV_STATUS_IDLE;
        library_kext_unload_with_id(kBUNDLE_ID);

        return DV_ERROR_KERNEL_SERVICE_LOAD_FAILED;
    }

    // TODO: open control socket connection

    _status = DV_STATUS_READY;
    return DV_ERROR_NONE;
}

dv_error_t divert_close()
{
    // TODO: disconnect control socket connection

    if (library_kext_unload_with_directory(kBUNDLE_DIR))
    {
        _status = DV_STATUS_LIMBO;
        library_kext_unload_with_id(kBUNDLE_ID);

        return DV_ERROR_KERNEL_SERVICE_UNLOAD_FAILED;;
    }

    _status = DV_STATUS_IDLE;
    return DV_ERROR_NONE;
}
