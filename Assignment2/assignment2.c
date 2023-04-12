#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/

#define BUFFER_SIZE 10 /*Define buffer size to read addresses file*/
#define MISS -1 /*Define miss as  -1*/
#define PAGE_SIZE 256 /*Each page consists of 256 bytes*/
#define PAGES PAGE_SIZE /*PAGE Size is equal to 256 bytes*/
#define MAX_ENTRIES 16 /*MAX entries in the tlb is 16*/
#define OFFSET_BITS 8 /*2^8 -> 8 bits in offset*/
#define OFFSET_MASK 255  /* OFFSET_MASk = 2^8 -1 */
#define FRAME_SIZE PAGE_SIZE /*FrAME SIZE = PAGE_SIZE*/
#define BACKING_STORE "BACKING_STORE.bin"
#define ADDRESSES "addresses.txt"
#define LOGICAL_ADDRESS_SPACE 65536
#define PHYSICAL_ADDRESS_SPACE LOGICAL_ADDRESS_SPACE/2


/* 
Shivom Sharma 400332395
Eddy Su 400263717
Assignment 2  
*/

typedef struct { int PAGE_NUM; int FRAME_NUM; } TLBEntry; //Declare structure for TLBEntry with page and frame numbers
signed char *start_address; //Declare signed char for the starting address
/*Initialize global variables to hold the number of hits and page faults*/
int TLB_hits = 0; 
int page_faults = 0; 

/*Prototypes for utility functions for navigating TLB*/
int search_TLB(int PAGE_NUM, TLBEntry *T);
void TLB_Add(int PAGE_NUMBER, int FRAME_NUMBER, int index, TLBEntry *T);
void TLB_Update(int OLD_PAGE, int NEW_PAGE, TLBEntry *T);

int search_TLB(int PAGE_NUM, TLBEntry *T) {
    //Search the TLB to find a matching page number
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (PAGE_NUM == T[i].PAGE_NUM) { //If the page number is found, return the corresponding frame
            return T[i].FRAME_NUM;
        }
    }
    return MISS; //Returns a miss if the frame is not present in the TLB
}

void TLB_Add(int PAGE_NUMBER, int FRAME_NUMBER, int index, TLBEntry* T) {
    T[index].PAGE_NUM = PAGE_NUMBER; //Replace page number at given index
    T[index].FRAME_NUM = FRAME_NUMBER; //Replace frame number at given index
   

}

void TLB_Update(int OLD_PAGE, int NEW_PAGE, TLBEntry *T) {
    if (search_TLB(OLD_PAGE, T)) { //Search the tlb to find the old page passed in
        for (int i = 0; i < MAX_ENTRIES; i++) { //Loop through the TLB
            if(T[i].PAGE_NUM == OLD_PAGE)  //Find the page once the old page is found
                T[i].PAGE_NUM = NEW_PAGE; //Update the page in the TLB
        }
    }

}


int main() {
    TLBEntry TLB[MAX_ENTRIES]; //Declare collection of TLB entries
    
    char buff[BUFFER_SIZE]; //Create buffer to read from addressses file
    /*Initialize the memory values to 0 */
    int PAGE_NUM = 0; 
    int PAGE_OFFSET = 0;
    int Physical_address = 0;
    int total_addresses = 0;
    int logical_address = 0;
    int frame_count = 0;
    int TLB_index = 0;
    /*Create space to store physical memory, initialized at 0*/
    signed char physical_memory[PHYSICAL_ADDRESS_SPACE] = {0};
    int queued_index = 0;
    /*Initialize the page table to -1 for all entries*/
    int page_table[PAGES];
    for (int i = 0; i < 256; i++) {
        page_table[i] = -1;
    }
    signed char byte_value; //Create a signed character to read in value at physical address
    //opening addresses file
    FILE *addresses = fopen(ADDRESSES, "r"); 
    if (addresses == NULL){
        printf("addresses.txt does not exist or cannot be opened.");
        return 0;
    }

    //opening BACKING_STORE binary file
    int backing_store = open(BACKING_STORE, O_RDONLY); //read only
    if (backing_store == -1){
        printf("BACKING_STORE.bin does not exist or cannot be opened.");
        return 0;
    }
    //Create the starting address mapping the pages to memory
    start_address = mmap(0, LOGICAL_ADDRESS_SPACE, PROT_READ, MAP_PRIVATE, backing_store, 0);
    /*While the buffer is not at the end*/
    while (fgets(buff, BUFFER_SIZE, addresses) != NULL) {
        total_addresses++; //Increement the total number of addresses
        logical_address = atoi(buff); //Calculate the logical address
        PAGE_NUM = (logical_address >> OFFSET_BITS); //Get the page number
        PAGE_OFFSET = logical_address&OFFSET_MASK; //Get the page offset
        printf("logical address : %d \n page number : %d \n page offset : %d \n", logical_address, PAGE_NUM, PAGE_OFFSET);
        int FRAME_NUM = search_TLB(PAGE_NUM, TLB); //Search the tlb for the given page number
        if (FRAME_NUM != MISS) { //If there is a TLB hit
            Physical_address = (FRAME_NUM << OFFSET_BITS) | PAGE_OFFSET; //Calculate the physical address at a given page number
            byte_value = physical_memory[Physical_address]; //Get the byte value from the physical memory
            printf("Virtual address: %d Physical address = %d Value=%d\n", logical_address, Physical_address, byte_value);//Print the output
            TLB_hits++; //Increase the number of TLB hits 
        }
        else { //If there is a TLB miss
            FRAME_NUM = page_table[PAGE_NUM]; //Get frame number from page table
            if(FRAME_NUM == -1) { //If the frame number is not found page fault
                //page fault
                page_faults++; 
                FRAME_NUM = queued_index; //Set the frame number to the queued index
                queued_index = (queued_index + 1) % (PHYSICAL_ADDRESS_SPACE / PAGE_SIZE); //Increment it and mod to see if it needs to be reset

                memcpy(physical_memory + frame_count*FRAME_SIZE, start_address + PAGE_NUM *PAGE_SIZE, PAGE_SIZE); //Copy a page over from the memory

                for(int i =0; i < PAGES; i++) { //Loop through the pages
                    if (page_table[i] == frame_count) { //Set frame count to negative one and update the TLB for the chang ein physical memory
                        page_table[i] = -1;
                        TLB_Update(i, PAGE_NUM, TLB);
                    }
                }
                page_table[PAGE_NUM] = frame_count; //Store hte frame in the page table
                frame_count = (frame_count +1)%128; //Increment the frame count to the max of 128 and reset to 0 once it has been reached


            }
            Physical_address = (FRAME_NUM << OFFSET_BITS) | PAGE_OFFSET; //Store the physical address
            byte_value = physical_memory[Physical_address]; //Grab the value from the physical address
            printf("Virtual address: %d Physical address = %d Value=%d\n", logical_address, Physical_address, byte_value);
            TLB_Add(PAGE_NUM, FRAME_NUM, TLB_index, TLB); //Add the frame and page number at the given index
            TLB_index = (TLB_index+1)%MAX_ENTRIES; //Increment the TLB index, if at capacity of the TLB start from 0

        }
        
        
    }
    munmap(start_address, LOGICAL_ADDRESS_SPACE); //Unmap the memory allocated
    printf("Total addresses = %d\nPage faults = %d\nTLB Hits = %d", total_addresses, page_faults,TLB_hits); 
    fclose(addresses);

    return 0;
}
