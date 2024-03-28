/*
Name: Michael Adams

Summary: Read data from a file & implement FCFS and SJF scheduling algorithms. 
Calculate the average waiting time and average turnaround time of concurrent processes.
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare functions
void sortByFCFS(int num_process, int *arrival, int *burst, int *waitTime, int *index, int *turnaroundTime);
void sortBySJF(int num_process, int *arrival, int *burst, int *waitTime, int *index, int *turnaroundTime);


int main(int argc, char **argv) {
    FILE *file;
    int num_process;
    int *arrival;
    int *burst;
    int *waitTime;
    int *index;
    int *turnaroundTime;
  
   

    // Open That File!
    file = fopen(argv[1], "r");

    // Error
    if (!file) {
        perror("Error opening file, try again:(");
        return 1;//Return 1 indicates error
    }

    // Read the first line to establish # of processes
    fscanf(file, "%d", &num_process);

    // Allocate the arrays for arrTime, burstTime, and waitTime

    arrival = (int *)malloc(num_process * sizeof(int));
    burst = (int *)malloc(num_process * sizeof(int));
    waitTime = (int *)malloc(num_process * sizeof(int));
    index = (int *)malloc(num_process * sizeof(int)); //copy index
    turnaroundTime = (int *)malloc(num_process * sizeof(int));

     waitTime[0] = 0; //P1 has waitTime of 0, so set it to 0. 

    // Read each line of the file and store arrival, burstTime
    for (int i = 0; i < num_process; i++) {
        fscanf(file, "%d", arrival + i);
        fscanf(file, "%d", burst + i);
    }

    // Close the file
    fclose(file);

   // Determine algo
    if (strcmp(argv[2], "FCFS") == 0) {
        // Call function
        sortByFCFS(num_process, arrival, burst, waitTime, index, turnaroundTime);
    } else if (strcmp(argv[2], "SJF") == 0) {
        // Call function
        sortBySJF(num_process, arrival, burst, waitTime, index, turnaroundTime);
    } else {
        printf("Invalid scheduling algo. USe FCFS or SJF.\n");
        return 1; // 1 indicates an error occurred
    }

    // Release memory
    free(arrival);
    free(burst);
    free(waitTime);
    free(index); 
    free(turnaroundTime);

    return 0;
}

void sortByFCFS(int num_process, int *arrival, int *burst, int *waitTime, int *index, int *turnaroundTime)  {
    //declare 
    float avgWaitTime = 0.0, avgTurnTime = 0.0;

    // Calculate waitTime
    waitTime[0] = 0; // P1 has waitTime of 0, so set it to 0.
    for (int i = 1; i < num_process; i++) {
        waitTime[i] = waitTime[i - 1] + burst[i - 1];
    }

    // create a var that will store all values of waitTime[]
    for (int i = 0; i < num_process; i++) {
        avgWaitTime += waitTime[i];
    }
    //Now average it 
    avgWaitTime = ((avgWaitTime / num_process)-1);

    // Calculate turnaround time
    //Make another var that follows the same logic behing avgWaitTime
    for (int i = 0; i < num_process; i++) {
        turnaroundTime[i] = waitTime[i] + burst[i];
        avgTurnTime += turnaroundTime[i];
    }
    //Now average it
    avgTurnTime = ((avgTurnTime / num_process)-1);


    // Order of Execution is built into the function
    printf("Order of Execution: ");
    for (int i = 0; i < num_process; i++) {
        printf("P%d", arrival[i] + 1 ); // Add 1 to the index
        if (i < num_process - 1) {
            printf(" -> ");
        }
    }
    
    printf("\n");

    // Print average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnTime);
    printf("\n");

}

void sortBySJF(int num_process, int *arrival, int *burst, int *waitTime, int *index, int *turnaroundTime) {
    //Declare variables
    float avgWaitTime = 0.0, avgTurnTime = 0.0;

    // Calculate waitTime
    waitTime[0] = 0; // P1 has waitTime of 0, so set it to 0.
    for (int i = 1; i < num_process; i++) {
        waitTime[i] = waitTime[i - 1] + burst[i - 1];
    }

    // create a var that will store all values of waitTime[]
    for (int i = 0; i < num_process; i++) {
        avgWaitTime += waitTime[i];
    }
    //Now average it 
    avgWaitTime = ((avgWaitTime / num_process)-1);

    // Calculate turnaround time
    //Make another var that follows the same logic behing avgWaitTime
    for (int i = 0; i < num_process; i++) {
        turnaroundTime[i] = waitTime[i] + burst[i];
        avgTurnTime += turnaroundTime[i];
    }

    //Now average it
    avgTurnTime = ((avgTurnTime / num_process)-1);
   

    // Sort based on burst time
    for (int i = 0; i < num_process - 1; i++) {
        for (int j = 0; j < num_process - i - 1; j++) {
            if (burst[j] > burst[j + 1]) {
                // Swap each burst
                int tempBurstIndex = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = tempBurstIndex;

                // Swap each arrival
                int tempArrTime = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = tempArrTime;

                // Swap each index
                int tempIndex = index[j];
                index[j] = index[j + 1];
                index[j + 1] = tempIndex;
            }
        }
    }

    // Order of Execution is built into the function
    printf("Order of Execution: ");
    for (int i = 0; i < num_process; i++) {
        printf("P%d", arrival[i] + 1 ); // Add 1 to the index
        if (i < num_process - 1) {
            printf(" -> ");
        }
    }
    
    printf("\n");


    // Print average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnTime);
    printf("\n");

}
