#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 20

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 3) {
        printf("Usage: %s <initial_position> <direction>\n", argv[0]);
        return 1;
    }

    int initial_pos = atoi(argv[1]);
    if (initial_pos < 0 || initial_pos > 299) {
        printf("Error: Initial position must be between 0 and 299.\n");
        return 1;
    }

    int direction;
    if (strcmp(argv[2], "LEFT") == 0) {
        direction = -1;
    } else if (strcmp(argv[2], "RIGHT") == 0) {
        direction = 1;
    } else {
        printf("Error: Invalid direction.\n");
        return 1;
    }

    // Read requests from file
    FILE *fp;
    int requests[MAX_REQUESTS];
    fp = fopen("requests.bin", "rb");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    fread(requests, sizeof(int), MAX_REQUESTS, fp);
    fclose(fp);

    // FCFS algorithm
    int total_head_movements = 0;
    int curr_pos = initial_pos;
    printf("FCFS Algorithm:\n");
    for (int i = 0; i < MAX_REQUESTS; i++) {
        int distance = abs(requests[i] - curr_pos);
        total_head_movements += distance;
        printf("Servicing request %d at cylinder %d. Head movement: %d\n", i+1, requests[i], distance);
        curr_pos = requests[i];
    }
    printf("Total head movements: %d\n", total_head_movements);

    return 0;
}