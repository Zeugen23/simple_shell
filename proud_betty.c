#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int a = 2;
    int b = 6;
    int difference = b - a;
    pid_t pid;
    pid = getpid();

    printf("Difference is %d\n", difference);
    printf("PID is %d\n", pid);

    return 0;
}
