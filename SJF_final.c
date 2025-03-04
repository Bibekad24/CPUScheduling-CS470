#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Find the process with the shortest remaining time
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

// Shortest Remaining Time First (SRTF) Scheduling
void srtf(Process proc[]) {
    int time = 0, completed = 0;
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;

    printf("Execution Order: ");
    while (completed != n) {
        int index = findNextProcess(proc, time);
        if (index == -1) { 
            time++;
            continue;
        }

        printf("P%d ", proc[index].process_id);
        proc[index].remaining_time--;
        time++;

        if (proc[index].remaining_time == 0) { 
            proc[index].is_completed = 1;
            completed++;
            proc[index].turnaround_time = time - proc[index].arrival_time;
            proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
        }
    }
    printf("\n");
}

// Calculate average waiting & turnaround time
void calculateAverageMetrics(Process proc[]) {
    double avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += proc[i].waiting_time;
        avg_turnaround += proc[i].turnaround_time;
    }
    printf("Average Waiting Time: %.2f\n", avg_wait / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);
}

// Print process details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);
    calculateAverageMetrics(proc);

    return 0;
}
