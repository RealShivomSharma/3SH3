#include <stdio.h>
#include <stdlib.h>
/*
Shivom Sharma 400332395
Eddy Su 
Assignment 3
*/
#define virt_addr 63536
#define Physical_address_space virt_addr * 1/2
#define BUFFER_SIZE 6
#define MAX_ENTRIES 16
#define PAGES
#define OFFSET_BITS
#define OFFSET_MASK
#define PAGE_SIZE 256
#define HIT 1 
#define MISS 0 

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
    int size;
    int rear;
    int front;
    int count;
    TLBEntry *TLB_ENTRIES;
}TLB;

int isEmpty(TLB *T) {
    return T->count == 0; //Returns whether the count in the TLB when count is 0 
    //This indicates whether there are any items left over
}
int isFull(TLB *T) {
    return T->count == MAX_ENTRIES;
}

void TLB_init(TLB *T) {
    T->size = MAX_ENTRIES; //Store the size of the TLB as the max number of entries
    T->front = 0; //Set the initial index for the front of the TLB 
    T->rear = 0; //Set the initial index for the rear of the TLB
    T->count = 0; //Set the initial count for the queue as 0, since no TLB entries have been added
    T->TLB_ENTRIES = (TLB_ENTRY *)malloc(q->size * sizeof(TLB_ENTRY)); //Allocate the size for the students stored within the queue dynamically based on the size passed in
}

void search_TLB(int *PAGE_NUM, TLB *T) {
    for (int i =0; i <T.size; i++) {
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
    
void TLB_Add(int *PAGE_NUM, int *FRAME_NUM) { 
    
}

void TLB_Update() {

}

int main() {
    int page_table[PAGES] =  {-1,-1,-1,-1,-1,-1,-1,-1,-1};
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
        PAGE_NUM = atoi(buff) >> OFFSET_BITS
        for (int i = 0; i < MAX_ENTRIES; i++) {
            if (PAGE_NUM == TLB[i].PAGE_NUM) 
                FRAME_NUM = TLB[i].FRAME_NUM;
                TLB_STATUS = HIT;
            else {
                TLB_STATUS = MISS;
            } 
        }
        if (TLB_STATUS = MISS) {
            FRAME_NUM = page_table[PAGE_NUM];
            if (FRAME_NUM == -1) {
                //Page Fault
            }
        }


        PAGE_OFFSET = atoi(buff) & OFFSET_MASK;
        
        Physical_address = (frame_number << OFFSET_BITS) | PAGE_OFFSET;

    }
    free(TLB);
    return 0;
}