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
#define BUFFER_SIZE 10
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
#define MEMORY_SIZE 1<<15

signed char *mmapfptr;
int intArray[MEMORY_SIZE];

typedef struct {
    int PAGE_NUM;
    int FRAME_NUM;
}TLBEntry;



int main() {
    char buff[BUFFER_SIZE];
    int PAGE_NUM;
    int FRAME_NUM;
    int PAGE_OFFSET = 0;
    int Physical_address = 0;
    int TLB_STATUS = 0;
    int TLB_total_hits = 0;
    int TLB_total_miss = 0;
    int page_faults_total_miss = 0;
    int total_addresses = 0 ;
    int logical_address=0;

    int queued_index = 0;
    
    //calloc allows all 0 assigned on initialization
    //uint16_t *page_table = calloc(PAGE_TABLE, sizeof(uint16_t));
    int page_table[PAGE_TABLE];
    for (int i = 0; i < PAGE_TABLE; i++) {
        page_table[i] = -1;
    }
    TLBEntry *TLB = NULL;
    TLB = calloc(MAX_ENTRIES, sizeof(TLBEntry));
    int TLB_index = 0;

    //opening addresses file
    FILE *fptr = fopen("addresses.txt", "r"); 
    if (fptr == NULL){
        printf("addresses.txt does not exist or cannot be opened.");
        return 0;
    }

    //opening output file
    FILE *output = fopen("output_test.txt", "w"); 
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
        logical_address = atoi(buff); // given addresses
        PAGE_NUM = (logical_address >> OFFSET_BITS) & 0xff;
        PAGE_OFFSET = atoi(buff) & 0xff;

        int index;
        for (index = 0; index < MAX_ENTRIES; index++) {
            if (PAGE_NUM == TLB[index].PAGE_NUM) {
                FRAME_NUM = TLB[index].FRAME_NUM;
                TLB_STATUS = HIT;
                TLB_total_hits++;
                break;
            } 
        }
        //fprintf(output, "\n%d\n", PAGE_NUM);
        if (index == MAX_ENTRIES) {  //check for tlb miss
            TLB_total_miss++;
            FRAME_NUM = page_table[PAGE_NUM];
            if (FRAME_NUM == -1) {
                //Page Fault
                page_faults_total_miss++;
                FRAME_NUM = queued_index;
                queued_index++;
                if (queued_index == (1<<15/ PAGE_SIZE)){
                    queued_index = 0;
                }
                memcpy(intArray + FRAME_NUM* PAGE_SIZE, mmapfptr+PAGE_NUM* PAGE_SIZE, PAGE_SIZE);
                page_table[PAGE_NUM] = FRAME_NUM;
                
            }
            TLB[TLB_index].PAGE_NUM = PAGE_NUM;
            TLB[TLB_index].FRAME_NUM = FRAME_NUM;
            TLB_index = (++TLB_index) % MAX_ENTRIES;
        }
        
        Physical_address = (FRAME_NUM << 8)|  PAGE_OFFSET;
        signed char value = *(signed char*)(intArray + Physical_address);
        fprintf(output, "Virtual address: %d Physical address = %d Value=%d\n", logical_address, Physical_address, value);

    }
    fprintf(output, "Total addresses = %d\nPage faults = %d\nTLB Hits = %d\nTLB Miss = %d", total_addresses, page_faults_total_miss,TLB_total_hits, TLB_total_miss);
    fclose(fptr);
    fclose(output);
    free(TLB);
    return 0;
}