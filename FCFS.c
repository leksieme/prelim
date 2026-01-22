#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, n;
    float bt[20], wt[20], tat[20];
    float wtavg = 0.0, tatavg = 0.0;

    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nEnter Burst Time for Process %d -- ", i);
        scanf("%f", &bt[i]);   // accepts decimal values
    }

    wt[0] = 0.0;
    tat[0] = bt[0];

    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
    }

    for(i = 0; i < n; i++)
    {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\n\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
    for(i = 0; i < n; i++)
    {
        printf("\n\tP%d\t\t%.2f\t\t%.2f\t\t%.2f",
               i, bt[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time -- %.2f", wtavg / n);
    printf("\nAverage Turnaround Time -- %.2f", tatavg / n);

    return 0;
}

