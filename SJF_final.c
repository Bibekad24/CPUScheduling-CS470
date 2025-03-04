#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to store process details
typedef struct {
    int process_id;      // Process ID
    int arrival_time;    // Arrival time of process
    int burst_time;      // Original burst time
    int remaining_time;  // Remaining burst time (for preemptive scheduling)
    int waiting_time;    // Time process waits in ready queue
    int turnaround_time; // Total time from arrival to completion
    int is_completed;    // Flag to mark process completion
} Process;

int n; // Total number of processes

// Finds the process with the shortest remaining time that has arrived
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX, index = -1;
    for (int i = 0; i < n; i++) {
        if (!proc[i].is_completed && proc[i].arrival_time <= current_time && proc[i].remaining_time < min_time) {
            min_time = proc[i].remaining_time;
            index = i;
        }
    }
    return index;
}

// Simulates Shortest Remaining Time First (SRTF) Scheduling
void srtf(Process proc[]) {
    int time = 0, completed = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("Execution Order: ");
    while (completed != n) {
        int index = findNextProcess(proc, time);
        if (index == -1) { // If no process is ready, increment time
            time++;
            continue;
        }

        // Execute process for one time unit
        printf("P%d ", proc[index].process_id);
        proc[index].remaining_time--;
        time++;

        // If process finishes execution, calculate turnaround and waiting times
        if (proc[index].remaining_time == 0) {
            proc[index].is_completed = 1;
            completed++;
            proc[index].turnaround_time = time - proc[index].arrival_time;
            proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
        }
    }
    printf("\n");
}

// Computes and prints average waiting & turnaround times
void calculateAverageMetrics(Process proc[]) {
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += proc[i].waiting_time;
        avg_turnaround += proc[i].turnaround_time;
    }
    printf("Average Waiting Time: %.2f\n", avg_wait / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);
}

// Prints process table with details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Define process list with ID, arrival time, and burst time
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);
    calculateAverageMetrics(proc);

    return 0;
}
