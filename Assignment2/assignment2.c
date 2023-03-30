#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/
/*
Shivom Sharma 400332395
Eddy Su 
Assignment 3    
*/

#define virt_addr 63536
#define Physical_address_space virt_addr * 1/2
#define BUFFER_SIZE 6
#define MAX_ENTRIES 16
#define PAGES 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define PAGE_SIZE 256
#define HIT 1   
#define MISS 0
#define INT_SIZE 4
#define INT_COUNT 
#define MEMORY_SIZE PAGE_SIZE * INT_SIZE

signed char *mmapfptr;
int intArray[MEMORY_SIZE];

int isEmpty(TLB *T);
int isFull(TLB *T);
void TLB_init(TLB *T);
void search_TLB(int *PAGE_NUM, TLB *T);
void TLB_Add(int *PAGE_NUM, TLB *T);
void TLB_Update(void);
struct {
    int PAGE_NUM;
    int FRAME_NUM;
}TLBEntry;
struct {
    int rear;
    int front;
    int count;
    TLBEntry entries[MAX_ENTRIES];
}TLB;

//Our
struct {

}PhysicalMemory;

void search_TLB(int *PAGE_NUM, TLB *T) {
    for (int i =0; i < MAX_ENTRIES; i++) {
        if (PAGE_NUM = TLB[i].PAGE_NUM) {
            FRAME_NUM = TLB[i].PAGE_NUM;
            TLB_STATUS = HIT;
        }
        else {
            TLB_STATUS = MISS;
        }

    }
    if (TLB_STATUS == MISS) {
        FRAME_NUM = page_table[PAGE_NUM];
        if(FRAME_NUM == -1) {
            // Page Fault
        }
    }
}
    
void TLB_Add(int *PAGE_NUM, int *FRAME_NUM, TLB *TLB) { 
    if (TLB->count == MAX_ENTRIES) {
        TLB->entries[front].PAGE_NUM = PAGE_NUM;
        TLB->entries[front].FRAME_NUM = FRAME_NUM;
    }
     
}
.
void TLB_Update() {

}

void TLB_Init(TLB *T) {
    T->entries = {{0}};
    T->front = -1;
    T->rear = -1;
    T->count = 0;
}

int main() {
    int page_table[PAGES] = {-1};
    char buff[BUFFER_SIZE];
    int PAGE_NUM = 0;
    int PAGE_OFFSET = 0;
    int Physical_address = 0;
    int frame_number = 0;
    int TLB_STATUS = 0;
    TLB TLB;
    TLB_INIT(TLB);

    FILE *fptr = fopen("addresses.txt", "r");

    while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
        PAGE_NUM = atoi(buff) >> OFFSET_BITS;
        for (int i = 0; i < MAX_ENTRIES; i++) {
            if (PAGE_NUM == TLB[i].PAGE_NUM) {
                FRAME_NUM = TLB[i].FRAME_NUM;
                TLB_STATUS = HIT;
            }
            else {
                TLB_STATUS = MISS;
            } 
        }
        if (TLB_STATUS = MISS) {
            FRAME_NUM = page_table[PAGE_NUM];
            if (FRAME_NUM == -1) {
                //Page Fault
                int mmapfile_fd = open("numbers.bin", O_RDONLY);
                mmapfptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);
                for (int i = 0; i < MEMORY_SIZE; i++) {
                    memcpy(intArray + i, mmapfptr + 4*i, INT_SIZE);
                }
                
            }
        }
        
        


        PAGE_OFFSET = atoi(buff) & OFFSET_MASK;
        
        Physical_address = (frame_number << OFFSET_BITS) | PAGE_OFFSET;

    }
    fclose(fptr);
    free(TLB);
    return 0;
}