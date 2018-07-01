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

    return 0;
}
