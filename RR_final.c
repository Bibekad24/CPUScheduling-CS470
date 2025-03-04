#include <stdio.h>
#include <stdlib.h>

// Structure to store process details
typedef struct {
    int process_id;      // Process ID
    int arrival_time;    // Arrival time of process
    int burst_time;      // Original burst time
    int remaining_time;  // Remaining burst time (for round-robin execution)
    int waiting_time;    // Time process waits in ready queue
    int turnaround_time; // Total time from arrival to completion
} Process;

// Simulates Round Robin Scheduling
void roundRobin(Process proc[], int n, int quantum) {
    int time = 0, done;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("Execution Order: ");
    while (1) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                done = 0;  // Mark that at least one process is not done
                printf("P%d ", proc[i].process_id);

                // If process has more than quantum time left, execute for quantum time
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else { // If remaining time is less than quantum, execute fully
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].arrival_time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                    proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
                }
            }
        }
        if (done) break; // Exit when all processes are completed
    }
    printf("\n");
}

// Prints process table with details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Define process list with ID, arrival time, and burst time
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 4; // Time quantum for Round Robin scheduling

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
