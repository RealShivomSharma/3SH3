#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 20

int abs(int x) {
    return x > 0 ? x : -x;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sstf(int requests[], int size, int head, int *headMovements) {
    int sortedRequests[MAX_REQUESTS];
    memcpy(sortedRequests, requests, size * sizeof(int));
    int sortedSize = size;
    int visited[MAX_REQUESTS] = {0};
    int curr = head;
    *headMovements = 0;

    for (int i = 0; i < size; i++) {
        int minDist = __INT_MAX__, nextIndex = -1;
        for (int j = 0; j < sortedSize; j++) {
            if (!visited[j]) {
                printf("%d ", sortedRequests[j]);
                int dist = abs(curr - sortedRequests[j]);
                if (dist < minDist) {
                    minDist = dist;
                    nextIndex = j;
                }
            }
        }

        visited[nextIndex] = 1;
        *headMovements += minDist;
        curr = sortedRequests[nextIndex];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <head position> <head direction (L or R)>\n", argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);
    char *headDir = argv[2];

    if (head < 0 || head > 299 || (strcmp(headDir, "L") != 0 && strcmp(headDir, "R") != 0)) {
        printf("Invalid input.\n");
        return 1;
    }

    FILE *fp = fopen("request.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int requests[MAX_REQUESTS];
    int size = 0;
    while (size < MAX_REQUESTS && fread(&requests[size], sizeof(int), 1, fp)) {
        size++;
    }

    fclose(fp);

    int headMovements;
    sstf(requests, size, head, &headMovements);

    printf("SSTF Algorithm\n");
    printf("Initial head position: %d\n", head);
    printf("Head direction: %s\n", headDir);
    printf("Requests: ");
    
    printf("\n");
    printf("Total head movements: %d\n", headMovements);

    return 0;
}