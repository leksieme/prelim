#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    int p[20];
    float bt[20], wt[20], tat[20];
    float wtavg = 0.0, tatavg = 0.0;

    cout << "Enter the number of processes -- ";
    cin >> n;

    if (n <= 0 || n > 20)
    {
        cout << "Invalid input. Please enter a number between 1 and 20.\n";
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        p[i] = i;
        cout << "Enter Burst Time for Process " << i << " -- ";
        cin >> bt[i];

        if (bt[i] < 0)
        {
            cout << "Invalid burst time. Please enter a non-negative number.\n";
            return 1;
        }
    }

    /* Sorting processes by burst time (SJF) */
    for (int i = 0; i < n; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            if (bt[i] > bt[k])
            {
                swap(bt[i], bt[k]);
                swap(p[i], p[k]);
            }
        }
    }

    wt[0] = 0.0;
    tat[0] = bt[0];

    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i] << "\t"
             << fixed << setprecision(2)
             << bt[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time -- " << wtavg / n;
    cout << "\nAverage Turnaround Time -- " << tatavg / n << endl;

    return 0;
}
