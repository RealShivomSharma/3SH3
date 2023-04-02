#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 20
#define CYLINDERS 300

// Function prototypes
int fcfs(int requests[], int initial_pos);
int sstf(int requests[], int initial_pos);
int scan(int requests[], int initial_pos, int direction);
int c_scan(int requests[], int initial_pos, int direction);
int look(int requests[], int initial_pos, int direction);
int c_look(int requests[], int initial_pos, int direction);
void sort(int arr[], int n);

int main(int argc, char* argv[]) {
    // Parse command line arguments
    if (argc != 3) {
        printf("Usage: %s initial_pos direction\n", argv[0]);
        return 1;
    }
    int initial_pos = atoi(argv[1]);
    int direction = (strcmp(argv[2], "LEFT") == 0) ? -1 : 1;

    // Read requests from binary file
    FILE* fp = fopen("requests.bin", "rb");
    int requests[MAX_REQUESTS];
    fread(requests, sizeof(int), MAX_REQUESTS, fp);
    fclose(fp);

    // FCFS
    printf("FCFS:\n");
    int fcfs_head_movements = fcfs(requests, initial_pos);
    printf("Total head movements: %d\n", fcfs_head_movements);

    // SSTF
    printf("\nSSTF:\n");
    int sstf_head_movements = sstf(requests, initial_pos);
    printf("Total head movements: %d\n", sstf_head_movements);

    // Sort requests for SCAN, C-SCAN, LOOK, and C-LOOK
    int sorted_requests[MAX_REQUESTS];
    memcpy(sorted_requests, requests, sizeof(requests));
    sort(sorted_requests, MAX_REQUESTS);

    // SCAN
    printf("\nSCAN:\n");
    int scan_head_movements = scan(sorted_requests, initial_pos, direction);
    printf("Total head movements: %d\n", scan_head_movements);

    // C-SCAN
    printf("\nC-SCAN:\n");
    int c_scan_head_movements = c_scan(sorted_requests, initial_pos, direction);
    printf("Total head movements: %d\n", c_scan_head_movements);

    // LOOK
    printf("\nLOOK:\n");
    int look_head_movements = look(sorted_requests, initial_pos, direction);
    printf("Total head movements: %d\n", look_head_movements);

    // C-LOOK
    printf("\nC-LOOK:\n");
    int c_look_head_movements = c_look(sorted_requests, initial_pos, direction);
    printf("Total head movements: %d\n", c_look_head_movements);

    return 0;
}

int fcfs(int requests[], int initial_pos) {
    // TODO: Implement FCFS
    return 0;
}

int sstf(int requests[], int initial_pos) {
    // TODO: Implement SSTF
    return 0;
}

int scan(int requests[], int initial_pos, int direction) {
    // TODO: Implement SCAN
    return 0;
}

int c_scan(int requests[], int initial_pos, int direction) {
    // TODO: Implement C-SCAN
    return 0;
}

int look(int requests[], int initial_pos, int direction) {
    // TODO: Implement LOOK
    return 0;
}

int c_look(int requests[], int initial_pos, int direction) {
    // TODO: Implement C-LOOK
    return