#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> // for sort

using namespace std;

struct Process {
    int id;
    float bt;
    float wt;
    float tat;
};

// Function to display the results
void displayResults(const vector<Process>& processes) {
    float wtavg = 0, tatavg = 0;
    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for (auto p : processes) {
        cout << "P" << p.id << "\t"
             << fixed << setprecision(2) << p.bt << "\t\t"
             << p.wt << "\t\t"
             << p.tat << endl;
        wtavg += p.wt;
        tatavg += p.tat;
    }
    cout << "\nAverage Waiting Time: " << wtavg / processes.size()
         << "\nAverage Turnaround Time: " << tatavg / processes.size() << endl;
}

// FCFS Scheduling
void FCFS(vector<Process> processes) {
    processes[0].wt = 0;
    processes[0].tat = processes[0].bt;

    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].wt = processes[i-1].wt + processes[i-1].bt;
        processes[i].tat = processes[i].wt + processes[i].bt;
    }

    cout << "\n--- FCFS Scheduling ---\n";
    displayResults(processes);
}

// SJF Scheduling (Non-Preemptive)
void SJF(vector<Process> processes) {
    // Sort by burst time
    sort(processes.begin(), processes.end(), [](Process a, Process b){
        return a.bt < b.bt;
    });

    processes[0].wt = 0;
    processes[0].tat = processes[0].bt;

    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].wt = processes[i-1].wt + processes[i-1].bt;
        processes[i].tat = processes[i].wt + processes[i].bt;
    }

    cout << "\n--- SJF Scheduling ---\n";
    displayResults(processes);
}

// Round Robin Scheduling
void RoundRobin(vector<Process> processes, float quantum) {
    size_t n = processes.size();
    vector<float> rem_bt(n);
    for (size_t i = 0; i < n; i++) rem_bt[i] = processes[i].bt;

    float time = 0;
    bool done;
    do {
        done = true;
        for (size_t i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    time += rem_bt[i];
                    processes[i].wt = time - processes[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!done);

    for (size_t i = 0; i < n; i++)
        processes[i].tat = processes[i].bt + processes[i].wt;

    cout << "\n--- Round Robin Scheduling (Quantum = " << quantum << ") ---\n";
    displayResults(processes);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        cout << "Enter Burst Time for Process " << i << ": ";
        cin >> processes[i].bt;
    }

    float quantum;
    cout << "Enter Time Quantum for Round Robin: ";
    cin >> quantum;

    FCFS(processes);
    SJF(processes);
    RoundRobin(processes, quantum);

    return 0;
}
