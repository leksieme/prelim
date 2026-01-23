#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float at;
    float bt;
    float ct;
    float wt;
    float tat;
} Process;

// Function to display results
void displayResults(Process p[], int n) {
    float wtavg = 0, tatavg = 0;
    printf("\nPROCESS ID\tAT\tBT\tCT\tTT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].id, (int)p[i].at, (int)p[i].bt, (int)p[i].ct, (int)p[i].tat, (int)p[i].wt);
        wtavg += p[i].wt;
        tatavg += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f\n", wtavg / n);
    printf("Average Turnaround Time: %.2f\n", tatavg / n);
    
    //round robin
}
void RoundRobin(Process p[], int n, float quantum) {
    float rem_bt[20];
    int completed[20] = {0};
    
    for (int i = 0; i < n; i++) rem_bt[i] = p[i].bt;

    float time = 0;
    int process_count = 0;
    int current = 0;

    while (process_count < n) {
        // Find next process that has arrived
        int found = 0;
        int attempts = 0;
        
        while (!found && attempts < n) {
            if (!completed[current] && p[current].at <= time && rem_bt[current] > 0) {
                found = 1;
                break;
            }
            current = (current + 1) % n;
            attempts++;
        }

        // If no process has arrived, jump to next arrival
        if (!found) {
            float min_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && p[i].at < min_arrival) {
                    min_arrival = p[i].at;
                }
            }
            time = min_arrival;
            current = 0;
            continue;
        }

        // Execute process for quantum time
        if (rem_bt[current] > quantum) {
            time += quantum;
            rem_bt[current] -= quantum;
        } else {
            time += rem_bt[current];
            p[current].ct = time;
            p[current].tat = p[current].ct - p[current].at;
            p[current].wt = p[current].tat - p[current].bt;
            rem_bt[current] = 0;
            completed[current] = 1;
            process_count++;
        }

        current = (current + 1) % n;
    }

    printf("\n--- Round Robin Scheduling (Quantum = %.2f) ---\n", quantum);
    displayResults(p, n);
}
// SJF Scheduling (Non-Preemptive)
void SJF(Process p[], int n) 
{
    int completed[20] = {0};
    float time = 0;
    int process_count = 0;

    while (process_count < n) {
        int shortest = -1;
        float min_bt = 1e9;

        // Find process with shortest BT that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                shortest = i;
            }
        }

        // If no process has arrived, jump to next arrival
        if (shortest == -1) {
            float min_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && p[i].at < min_arrival) {
                    min_arrival = p[i].at;
                }
            }
            time = min_arrival;
            continue;
        }

        time += p[shortest].bt;
        p[shortest].ct = time;
        p[shortest].tat = p[shortest].ct - p[shortest].at;
        p[shortest].wt = p[shortest].tat - p[shortest].bt;
        completed[shortest] = 1;
        process_count++;
    }

    printf("\n--- SJF Scheduling ---\n");
    displayResults(p, n);
}
void SRTF(Process p[], int n) {
    float rem_bt[20];
    int completed[20] = {0};
    
    for (int i = 0; i < n; i++) rem_bt[i] = p[i].bt;

    float time = 0;
    int shortest;
    float min_rem;
    int process_count = 0;

    while (process_count < n) {
        shortest = -1;
        min_rem = 1e9;

        // Find process with shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].at <= time && rem_bt[i] < min_rem) {
                min_rem = rem_bt[i];
                shortest = i;
            }
        }

        // If no process has arrived, jump to next arrival
        if (shortest == -1) {
            float min_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && p[i].at < min_arrival) {
                    min_arrival = p[i].at;
                }
            }
            time = min_arrival;
            continue;
        }

        time += 1;
        rem_bt[shortest] -= 1;
        
        if (rem_bt[shortest] == 0) {
            completed[shortest] = 1;
            p[shortest].ct = time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            process_count++;
        }
    }

    printf("\n--- SRTF Scheduling ---\n");
    displayResults(p, n);
}

int main() {
    float at[] = {4, 2, 3, 6, 1, 5, 8, 7};
    float bt[] = {53, 43, 18, 16, 44, 73, 99, 27};
    int n = 8;

    // Calculate mean and median of burst time for quantum
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += bt[i];
    }
    float mean = sum / n;

    // Calculate median
    float bt_sorted[8];
    for (int i = 0; i < n; i++) bt_sorted[i] = bt[i];
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt_sorted[i] > bt_sorted[j]) {
                float temp = bt_sorted[i];
                bt_sorted[i] = bt_sorted[j];
                bt_sorted[j] = temp;
            }
        }
    }
    
    float median = (bt_sorted[3] + bt_sorted[4]) / 2.0;
    float quantum = median;

    printf("Mean of Burst Time: %.2f\n", mean);
    printf("Median of Burst Time: %.2f\n", median);
    printf("Recommended Time Quantum: %.2f\n", quantum);

    Process processes[20];

    // Initialize processes with predefined AT and BT
    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        processes[i].at = at[i];
        processes[i].bt = bt[i];
    }

    // Make copies for different algorithms
    Process srtf[20], sjf[20], rr[20];
    for (int i = 0; i < n; i++) {
        srtf[i] = processes[i];
        sjf[i] = processes[i];
        rr[i] = processes[i];
    }
    RoundRobin(rr, n, quantum);
    SJF(sjf, n);
    SRTF(srtf, n);
    
    

    return 0;
}

