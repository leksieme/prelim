#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p[20], i, k, n, tempP;
    float bt[20], wt[20], tat[20], temp;
    float wtavg = 0.0, tatavg = 0.0;

    printf("\nEnter the number of processes -- ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20)
    {
        printf("Invalid input. Please enter a number between 1 and 20.\n");
        return 1;
    }

    for(i = 0; i < n; i++)
    {
        p[i] = i;
        printf("Enter Burst Time for Process %d -- ", i);
        if (scanf("%f", &bt[i]) != 1 || bt[i] < 0)
        {
            printf("Invalid burst time. Please enter a non-negative number.\n");
            return 1;
        }
    }

    /* Sorting processes by burst time (SJF) */
    for(i = 0; i < n; i++)
    {
        for(k = i + 1; k < n; k++)
        {
            if(bt[i] > bt[k])
            {
                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;

                tempP = p[i];
                p[i] = p[k];
                p[k] = tempP;
            }
        }
    }

    wt[0] = 0.0;
    tat[0] = bt[0];

    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for(i = 0; i < n; i++)
    {
        printf("\tP%d\t%.2f\t\t%.2f\t\t%.2f\n",
               p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time -- %.2f", wtavg / n);
    printf("\nAverage Turnaround Time -- %.2f\n", tatavg / n);

    return 0;
}
