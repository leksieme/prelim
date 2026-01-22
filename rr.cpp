#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    float bt[20], rem_bt[20], wt[20], tat[20];
    float quantum;
    float time = 0, wtavg = 0, tatavg = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter time quantum: ";
    cin >> quantum;

    for(int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> bt[i];
        rem_bt[i] = bt[i];
        wt[i] = 0;
    }

    /* Round Robin Scheduling */
    bool done;
    do
    {
        done = true;
        for(int i = 0; i < n; i++)
        {
            if(rem_bt[i] > 0)
            {
                done = false;
                if(rem_bt[i] > quantum)
                {
                    time += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
    } while(!done);

    for(int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t"
             << fixed << setprecision(2)
             << bt[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << wtavg / n;
    cout << "\nAverage Turnaround Time: " << tatavg / n << endl;

    return 0;
}
