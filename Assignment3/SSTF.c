#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 20

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int abs(int a) {
    if (a < 0) return -a;
    return a;
}

int sstf(int current, int* requests, int size) {
    //int serviced[MAX_REQUESTS];
    int total_head_movements = 0;
    //memset(serviced, 0, sizeof(serviced));
    int i, j, closest, distance;
    for (i = 0; i < size; i++) {
        closest = -1;
        distance = 999999;
        for (j = 0; j < size; j++) {
            if (requests[j]!=1) {
                if (abs(requests[j] - current) < distance) {
                    distance = abs(requests[j] - current);
                    closest = j;
                }
            }
        }
        current = requests[closest];
        requests[closest] = 1;
        total_head_movements += distance;
        //printf("%d, ", current);
         if (i < (size-1)){
            printf("%d, ", current);
        } else {
            printf("%d", current);
        }
    }
    return total_head_movements;
}

int main(int argc, char* argv[]) {
    printf("SSTF DISK SCHEDULING ALGORITHM \n\n");
    if (argc < 3) {
        printf("not enough arguments <initial position> <direction>\n");
        return 1;
    }
    int initial_position = atoi(argv[1]);
    char* direction = argv[2];
    int requests[MAX_REQUESTS];
    int size = 0;
    FILE* fp;
    fp = fopen("request.bin", "rb");
    if (fp == NULL) {
        printf("Error: Unable to open request file\n");
        return 1;
    }
    while (size < 20 && fread(&requests[size], sizeof(int), 1, fp)) {
        size++;
    }
    fclose(fp);
    int sorted_requests[MAX_REQUESTS];
    memcpy(sorted_requests, requests, sizeof(requests));
    qsort(sorted_requests, size, sizeof(int), cmpfunc);
    int total_head_movements;
    //printf("%d\n", initial_position);
    if (strcmp(direction, "RIGHT") == 0 || strcmp(direction, "LEFT") == 0) {
        total_head_movements = sstf(initial_position, sorted_requests, size);
    }  else {
        printf("Error: Invalid direction specified\n");
        return 1;
    }
    printf("\n\nTotal head movements: %d\n", total_head_movements);
    return 0;
}