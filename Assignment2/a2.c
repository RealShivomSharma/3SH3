#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/

#define MISS 0 
#define HIT 1
#define PAGE_SIZE 256
#define PAGES PAGE_SIZE/2
#define MAX_ENTRIES 16
#define OFFSET_BITS 8
#define OFFSET_MASK PAGE_SIZE
#define FRAME_SIZE PAGE_SIZE
#define MEMORY_SIZE FRAME_SIZE * INT_SIZE
#define BACKING_STORE "BACKING_STORE.bin"
#define ADDRESSES "addresses.txt"

signed char *mmapfptr;
int TLB_hits = 0;
int Page_faults = 0; 
int TLB_STATUS = 0;
struct TLBEntry { int PAGE_NUM, int FRAME_NUM };
struct TLB { int front, int rear, int count, TLBEntry entries[MAX_ENTRIES] };
int page_table[PAGE_SIZE];




//initialize all TLB entries to negative, and the circular buffer front and rear at 0 
void TLB_init(TLB *T) {
    T->front = -1;
    T->rear = -1;
    T->count = 0;
    T->entries = {-1};
}

void search_TLB(TLB *T, int PAGE_NUM) {
    //First check to see if the TLB is empty 
    if (T->count == 0 )
        
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (PAGE_NUM = T->entries[i].PAGE_NUM) {
            FRAME_NUM = T->entries[i].FRAME_NUM;
            TLB_hits++;
            TLB_STATUS == HIT;
        }
        else 
            TLB_STATUS = MISS;
        }
    if (TLB_STATUS = MISS) {
        FRAME_NUM = page_table[PAGE_NUM];
            if (FRAME_NUM == -1) {
                //Page Fault 
        }
    }
}

void TLB_Add(int *PAGE_NUMBER, int *FRAME_NUMBER, TLB* T) {
    if (T->count == MAX_ENTRIES) {
        T->entries[T->front].PAGE_NUM = PAGE_NUMBER;
        T->entries[T->front].FRAME_NUM = FRAME_NUMBER;
    }
}

void TLB_Update() {
    
}


void 
int main() {

    return 0;
}
