#include <unistd.h>
#include <stdio.h>

int main()
{
    if (geteuid() == 0)
        setuid(0);
    if (getuid() == 0)
        printf("I am root!\n");
    return 0;
}
