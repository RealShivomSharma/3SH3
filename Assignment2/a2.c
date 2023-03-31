#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/

#define BUFFER_SIZE 10
#define MISS 0 
#define HIT 1
#define PAGE_SIZE 256
#define PAGES PAGE_SIZE
#define MAX_ENTRIES 16
#define OFFSET_BITS 8
#define OFFSET_MASK PAGE_SIZE -1  
#define FRAME_SIZE PAGE_SIZE
#define MEMORY_SIZE FRAME_SIZE * INT_SIZE
#define BACKING_STORE "BACKING_STORE.bin"
#define ADDRESSES "addresses.txt"

signed char *start_address;
int TLB_hits = 0;
int Page_faults = 0; 
int TLB_STATUS = 0;
struct TLBEntry { int PAGE_NUM, int FRAME_NUM };
struct TLB { int front, int rear, int count, TLBEntry entries[MAX_ENTRIES] };
int page_table[PAGES] = {-1};
int intArray[MEMORY_SIZE];

//initialize all TLB entries to negative, and the circular buffer front and rear at 0 
void TLB_init(TLB *T) {
    T->front = -1;
    T->rear = -1;
    T->count = 0;
    T->entries = {-1};
}

int search_TLB(TLB *T, int PAGE_NUM) {
    //First check to see if the TLB is empty 
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (PAGE_NUM = T->entries[i].PAGE_NUM) { //If the page number is found, return 1
            FRAME_NUM = T->entries[i].FRAME_NUM;
            TLB_hits++;
            return t->entries[i].FRAME_NUM;
        }
        return MISS; //Returns a miss if the frame is not present in the TLB
}
}

void TLB_Add(int *PAGE_NUMBER, int *FRAME_NUMBER, TLB* T) {
    if (T->count == MAX_ENTRIES) {
        T->entries[T->front].PAGE_NUM = PAGE_NUMBER;
        T->entries[T->front].FRAME_NUM = FRAME_NUMBER;
    }
    front = (front + 1)% T->size;

}

void TLB_Update() {
    int index; 
    
}


void 
int main() {
    TLB *TLB;
    TLB_init(TLB);

    char buff[BUFFER_SIZE];
    int PAGE_NUM = 0;
    int FRAME_NUM = 0;
    int PAGE_OFFSET = 0;
    int Physical_address = 0;
    int total_addresses = 0;
    int logical_address = 0;

    //opening addresses file
    FILE *addresses = fopen(ADDRESSES, "r"); 
    if (addresses == NULL){
        printf("addresses.txt does not exist or cannot be opened.");
        return 0;
    }
    //opening BACKING_STORE binary file
    int backing_store = open(BACKING_STORE, O_RDONLY); //read only
    if (backing_store == NULL){
        printf("BACKING_STORE.bin does not exist or cannot be opened.");
        return 0;
    }
    uint8_t *mmapfptr = mmap(NULL, 1 << 16, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);

    while (fgets(buff, BUFFER_SIZE, addresses) != NULL) {
        total_addresses++;
        logical_address = atoi(buff);
        PAGE_NUM = (logical_address >> OFFSET_BITS);
        PAGE_OFFSET = atoi(buff) & OFFSET_MASK;
        Physical_address = (frame_number << OFFSET_BITS) | PAGE_OFFSET;
        printf("Virtual addr is: %s, Page# = %d & Offset = %d. Physical addr = %d ", buff, PAGE_NUM, PAGE_OFFSET, Physical_address);
        
        if(search_TLB(PAGE_NUM, FRAME_NUM, TLB) == MISS) {
            FRAME_NUM = page_table[PAGE_NUM];
            if(FRAME_NUM == -1 ) {
                //page fault
                page_faults++;    
                memcpy(intArray + FRAME_NUM *PAGE_SIZE, start_address+PAGE_NUM *PAGE_SIZE, PAGE_SIZE);
                page_table[PAGE_NUM] = FRAME_NUM;
            }
            
        }
    }

    return 0;
}
