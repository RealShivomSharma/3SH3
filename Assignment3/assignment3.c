#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 20

int abs(int a) {
    if (a < 0) return -a;
    return a;
}

void bubble_sort(int arr[], int size) {
    for (int i=0; i< size-1; i++) {
        for (int j=0; j< size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp= arr[j];
                arr[j] =arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void FCFS(int initial_pos, int requests[MAX_REQUESTS]) {
    int total_head_movements = 0;
    int curr_pos = initial_pos;
    printf("FCFS DISK SCHEDULING ALGORITHM:\n\n");
    for (int i = 0; i < MAX_REQUESTS; i++) {
        int distance = abs(requests[i] - curr_pos);
        total_head_movements += distance;
        if (i < (MAX_REQUESTS-1)){
            printf("%d, ", requests[i]);
        } else {
            printf("%d", requests[i]);
        }
        curr_pos = requests[i];
    }
    printf("\n\nTotal head movements: %d\n\n", total_head_movements);
}

void SSTF(int initial_pos, int requests[MAX_REQUESTS], int size){
    printf("SSTF DISK SCHEDULING ALGORITHM:\n\n");

    int total_head_movements = 0;
    int curr_pos = initial_pos;
    int i, j, closest, distance;
    for (i = 0; i < size; i++) {
        closest = -1;
        distance = 999999;
        for (j = 0; j < size; j++) {
            if (requests[j]!=1) {
                if (abs(requests[j] - curr_pos) < distance) {
                    distance = abs(requests[j] - curr_pos);
                    closest = j;
                }
            }
        }
        curr_pos = requests[closest];
        requests[closest] = 1;
        total_head_movements += distance;
         if (i < (size-1)){
            printf("%d, ", curr_pos);
        } else {
            printf("%d", curr_pos);
        }
    }
    printf("\n\nTotal head movements: %d\n\n", total_head_movements);
}

int main(int argc, char *argv[]) {
    int initial_pos, direction;
    if (argc != 3) {
        printf("Missing Arguments, required: <initial_position> <direction>\n");
        return 1;
    }

    initial_pos = atoi(argv[1]);
    if (initial_pos < 0 || initial_pos > 299) {
        printf("Invalid position.\n");
        return 1;
    }

    if (strcmp(argv[2], "LEFT") == 0) {
        direction = -1;
    } else if (strcmp(argv[2], "RIGHT") == 0) {
        direction = 1;
    } else {
        printf("Invalid direction.\n");
        return 1;
    }


    FILE *fp;
    int requests[MAX_REQUESTS];
    int size=0;
    fp = fopen("request.bin", "rb");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    size = fread(requests, sizeof(int), MAX_REQUESTS, fp);
    fclose(fp);

    int sorted_requests[MAX_REQUESTS];
    memcpy(sorted_requests, requests, sizeof(requests));
    bubble_sort(sorted_requests, size);

    // FCFS algorithm
    FCFS(initial_pos, requests);
    SSTF(initial_pos, sorted_requests, size);
    return 0;
}