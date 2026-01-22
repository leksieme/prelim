#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0)
    {
        printf("First fork failed\n");
        exit(1);
    }

    if (pid1 == 0)
    {
        // First child
        printf("First Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        pid2 = fork();

        if (pid2 < 0)
        {
            printf("Second fork failed\n");
            exit(1);
        }

        if (pid2 == 0)
        {
            // Second child
            printf("Second Child PID: %d, Parent PID: %d\n", getpid(), getppid());
            exit(0);
        }
        else
        {
            // Parent
            printf("Parent PID: %d\n", getpid());
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
