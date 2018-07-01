#include <stdio.h>
#include <divert.h>

int main()
{
#ifdef DIVERT_PLATFORM_WINDOWS
    printf("libdivert for windows\n");
#elif DIVERT_PLATFORM_LINUX
    printf("libdivert for linux\n");
#elif DIVERT_PLATFORM_MACOS
    printf("libdivert for macos\n");
#endif

    dv_status_t status;
    if (divert_status(&status) == DV_ERROR_NONE)
    {
        switch (status)
        {
            case DV_STATUS_IDLE: printf("divert: idle\n"); break;
            case DV_STATUS_READY: printf("divert: ready\n"); break;
            case DV_STATUS_ACTIVE: printf("divert: active\n"); break;
        }
    }
    else
    {
        printf("cannot get divert status\n");
    }

    return 0;
}
