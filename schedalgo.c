#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float bt;
    float wt;
    float tat;
} Process;

// Function to display results
void displayResults(Process p[], int n) {
    float wtavg = 0, tatavg = 0;
    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%.2f\t\t%.2f\t\t%.2f\n", p[i].id, p[i].bt, p[i].wt, p[i].tat);
        wtavg += p[i].wt;
        tatavg += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f\n", wtavg / n);
    printf("Average Turnaround Time: %.2f\n", tatavg / n);
}

// FCFS Scheduling
void FCFS(Process p[], int n) {
    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\n--- FCFS Scheduling ---\n");
    displayResults(p, n);
}

// SJF Scheduling (Non-Preemptive)
void SJF(Process p[], int n) {
    // Make a copy to sort
    Process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].bt > p[j].bt) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\n--- SJF Scheduling ---\n");
    displayResults(p, n);
}

// Round Robin Scheduling
void RoundRobin(Process p[], int n, float quantum) {
    float rem_bt[20];
    for (int i = 0; i < n; i++) rem_bt[i] = p[i].bt;

    float time = 0;
    int done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    time += rem_bt[i];
                    p[i].wt = time - p[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!done);

    for (int i = 0; i < n; i++)
        p[i].tat = p[i].bt + p[i].wt;

    printf("\n--- Round Robin Scheduling (Quantum = %.2f) ---\n", quantum);
    displayResults(p, n);
}

int main() {
    int n;
    Process processes[20];
    float quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        printf("Enter Burst Time for Process %d: ", i);
        scanf("%f", &processes[i].bt);
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%f", &quantum);

    // Make copies for different algorithms
    Process fcfs[20], sjf[20], rr[20];
    for (int i = 0; i < n; i++) {
        fcfs[i] = processes[i];
        sjf[i] = processes[i];
        rr[i] = processes[i];
    }

    FCFS(fcfs, n);
    SJF(sjf, n);
    RoundRobin(rr, n, quantum);

    return 0;
}
