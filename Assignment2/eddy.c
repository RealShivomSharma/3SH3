#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/
#include <stdint.h>
/*
Shivom Sharma 400332395
Eddy Su 400263717
Assignment 3    
*/

#define virt_addr 63536
#define Physical_address_space virt_addr * 1/2
#define BUFFER_SIZE 6
#define MAX_ENTRIES 16 //
#define PAGES 256 //
#define PAGE_TABLE 32768 //
#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define PAGE_SIZE 256
#define FRAME_SIZE PAGE_SIZE
#define HIT 1   
#define MISS 0
#define INT_SIZE 4
#define INT_COUNT 
#define MEMORY_SIZE PAGE_SIZE * INT_SIZE

signed char *mmapfptr;
int intArray[MEMORY_SIZE];

/*int isEmpty(TLB *T);
int isFull(TLB *T);
void TLB_init(TLB *T);
void search_TLB(int *PAGE_NUM, TLB *T);
void TLB_Add(int *PAGE_NUM, TLB *T);
void TLB_Update(void);*/
typedef struct {
    int PAGE_NUM;
    int FRAME_NUM;
}TLBEntry;
/*struct {
    int rear;
    int front;
    int count;
    TLBEntry entries[MAX_ENTRIES];
}TLB;


void search_TLB(int *PAGE_NUM, TLBEntry *T) {
    for (int i =0; i < MAX_ENTRIES; i++) {
        if (PAGE_NUM = TLB.PAGE_NUM) {
            FRAME_NUM = TLB.PAGE_NUM;
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
void TLB_Update() {

}

void TLB_Init(TLB *T) {
    T->entries = {0};
    T->front = -1;
    T->rear = -1;
    T->count = 0;
}*/



int main() {
    char buff[BUFFER_SIZE];
    int PAGE_NUM = 0;
    int PAGE_OFFSET = 0;
    int Physical_address = 0;
    int frame_number = 0;
    int TLB_STATUS = 0;
    int TLB_total_hits = 0;
    int TLB_total_miss = 0;
    int page_faults_total_miss = 0;
    int total_addresses = 0 ;
    int logical_address;
    int value = 0;

    uint16_t *page_table = calloc(PAGE_TABLE, sizeof(uint16_t));
    TLBEntry *TLB = NULL;
    TLB = calloc(MAX_ENTRIES, sizeof(TLBEntry));
    int tlb_index = 0;

    //opening addresses file
    FILE *fptr = fopen("addresses.txt", "r"); 
    if (fptr == NULL){
        printf("addresses.txt does not exist or cannot be opened.");
        return 0;
    }

    //opening output file
    FILE *output = fopen("output.txt", "r"); 
    if (output == NULL){
        printf("output.txt does not exist or cannot be opened.");
        return 0;
    }

    //opening BACKING_STORE binary file
    int mmapfile_fd = open("BACKING_STORE.bin", O_RDONLY); //read only
    if (mmapfile_fd == -1){
        printf("BACKING_STORE.bin does not exist or cannot be opened.");
        return 0;
    }
    uint8_t *mmapfptr = mmap(NULL, 1 << 16, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);

    while (fgets(buff, BUFFER_SIZE, fptr) != NULL) {
        total_addresses++;
        logical_address = atoi(buff);
        PAGE_NUM = (logical_address >> OFFSET_BITS) & 0xff;
        PAGE_OFFSET = atoi(buff) & 0xff;
        Physical_address = (frame_number << OFFSET_BITS) | PAGE_OFFSET;

        int index;
        for (index = 0; index < MAX_ENTRIES; index++) {
            if (PAGE_NUM == TLB[index].PAGE_NUM) {
                frame_number = TLB[index].FRAME_NUM;
                TLB_STATUS = HIT;
                TLB_total_hits++;
                break;
            } 
        }
        if (index == MAX_ENTRIES) {
            frame_number = page_table[PAGE_NUM];
            if (frame_number == 0) {
                //Page Fault
                page_faults_total_miss++;
                for (int i = 0; i < MEMORY_SIZE; i++) {
                    memcpy(intArray + i, mmapfptr + 4*i, INT_SIZE);
                }
                
            }
        }
        
        fprintf(output, "Virtual address: %d Physical address = %d Value=%d", logical_address, Physical_address, value);

    }
    fprintf(output, "Total addresses = %d\nPage faults = %d\nTLB Hits = %d", total_addresses, page_faults_total_miss,TLB_total_hits);
    fclose(fptr);
    fclose(output);
    free(TLB);
    return 0;
}