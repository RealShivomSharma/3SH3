#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 20

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[]) {
    printf("lol");
    if (argc != 3) {
        printf("Usage: %s initial_position direction\n", argv[0]);
        return 1;
    }

    int initial_pos = atoi(argv[1]);
    char *direction = argv[2];

    if (strcmp(direction, "LEFT") != 0 && strcmp(direction, "RIGHT") != 0) {
        printf("Invalid direction: %s\n", direction);
        return 1;
    }

    int requests[MAX_REQUESTS];
    int num_requests = 0;

    FILE *f = fopen("request.bin", "rb");
    if (f == NULL) {
        printf("Failed to open request.bin\n");
        return 1;
    }

    while (num_requests < MAX_REQUESTS && fread(&requests[num_requests], sizeof(int), 1, f) == 1) {
        num_requests++;
    }

    fclose(f);

    int sorted_requests[MAX_REQUESTS];
    memcpy(sorted_requests, requests, num_requests * sizeof(int));
    qsort(sorted_requests, num_requests, sizeof(int), cmpfunc);

    int serviced_requests[MAX_REQUESTS];
    int num_serviced_requests = 0;

    int current_pos = initial_pos;
    int total_head_movements = 0;

    while (num_serviced_requests < num_requests) {
        int shortest_distance = 300;
        int shortest_index = -1;

        for (int i = 0; i < num_requests; i++) {
            int distance = abs(current_pos - sorted_requests[i]);
            if (distance < shortest_distance && !serviced_requests[i]) {
                shortest_distance = distance;
                shortest_index = i;
            }
        }

        if (shortest_index == -1) {
            if (strcmp(direction, "LEFT") == 0) {
                direction = "RIGHT";
            } else {
                direction = "LEFT";
            }
            continue;
        }

        serviced_requests[shortest_index] = 1;
        num_serviced_requests++;

        int next_pos = sorted_requests[shortest_index];
        total_head_movements += abs(current_pos - next_pos);
        current_pos = next_pos;

        if (strcmp(direction, "LEFT") == 0 && current_pos == 0) {
            direction = "RIGHT";
        } else if (strcmp(direction, "RIGHT") == 0 && current_pos == 299) {
            direction = "LEFT";
        }
    }

    printf("SSTF Total Head Movements: %d\n", total_head_movements);

    return 0;
}