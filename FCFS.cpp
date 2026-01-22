#include <iostream>
using namespace std;

int main()
{
    int n;
    float bt[20], wt[20], tat[20];
    float wtavg = 0, tatavg = 0;

    cout << "Enter the number of processes: ";
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> bt[i];   // accepts decimal values
    }

    wt[0] = 0.0;
    tat[0] = bt[0];

    for(int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
    }

    for(int i = 0; i < n; i++)
    {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t\t"
             << bt[i] << "\t\t"
             << wt[i] << "\t\t"
             << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << wtavg / n;
    cout << "\nAverage Turnaround Time: " << tatavg / n;

    return 0;
}
