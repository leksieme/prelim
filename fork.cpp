#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0)
    {
        cout << "First fork failed" << endl;
        exit(1);
    }

    if (pid1 == 0)
    {
        // First child
        cout << "First Child PID: " << getpid()
             << ", Parent PID: " << getppid() << endl;
        exit(0);
    }
    else
    {
        pid2 = fork();

        if (pid2 < 0)
        {
            cout << "Second fork failed" << endl;
            exit(1);
        }

        if (pid2 == 0)
        {
            // Second child
            cout << "Second Child PID: " << getpid()
                 << ", Parent PID: " << getppid() << endl;
            exit(0);
        }
        else
        {
            // Parent
            cout << "Parent PID: " << getpid() << endl;
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
