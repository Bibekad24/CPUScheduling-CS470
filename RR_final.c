#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Round Robin Scheduling
void roundRobin(Process proc[], int n, int quantum) {
    int time = 0, done;
    
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("Execution Order: ");
    while (1) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = 0;
                printf("P%d ", proc[i].process_id);
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].arrival_time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                    proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
                }
            }
        }
        if (done) break;
    }
    printf("\n");
}

// Print process details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 4;

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
