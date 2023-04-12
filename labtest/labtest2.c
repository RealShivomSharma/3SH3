/* 
Shivom Sharma 400332395
Eddy Su 400263717
Lab test 2  
*/


#include <stdio.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/

#define BUFFER_SIZE 15 /*Define buffer size to read addresses file*/
#define PAGE_SIZE 1024 /*Each page consists of 256 bytes*/
#define OFFSET_BITS 10 /*2^10 -> 10 bits in offset*/
#define OFFSET_MASK 1023  /* OFFSET_MASk = 2^10 -1 */
#define LOGICAL_ADDRESS_SPACE 4*10 /* 4 bit int * 10 items*/

int main(){
    int pagetable[LOGICAL_ADDRESS_SPACE]; //Declare page table with 40 entries
    int logical_address, PAGE_NUM, PAGE_OFFSET, FRAME_NUM, physical_address ; //Initialize variables
    signed char *pages; //Declare signed char for the starting address
    char buff[BUFFER_SIZE]; 

    //opening addresses file
    FILE *addresses = fopen("ltaddr.txt", "r"); 
    if (addresses == NULL){
        printf("ltaddr.txt does not exist or cannot be opened.");
        return 0;
    }

    //opening pagetablefile binary file
    int pagetablefile = open("pagetable.bin", O_RDONLY); //read only
    if (pagetablefile == -1){ 
        printf("pagetable.bin does not exist or cannot be opened.");
        return 0;
    }
    //Create the starting address mapping the pages to memory
    pages = mmap(0, LOGICAL_ADDRESS_SPACE, PROT_READ, MAP_PRIVATE, pagetablefile, 0);

    for(int i = 0; i < LOGICAL_ADDRESS_SPACE; i++){
        memcpy(pagetable + i, pages + 4*i, 4); //iterate through and copy entries into pagetable from memory
    }

    munmap(pages,LOGICAL_ADDRESS_SPACE); //Unmap

    while (fgets(buff, BUFFER_SIZE, addresses) != NULL) {
        logical_address = atoi(buff); //Calculate the logical address
        PAGE_NUM = (logical_address >> OFFSET_BITS); //Get the page number
        PAGE_OFFSET = logical_address&OFFSET_MASK; //Get the page offset
        FRAME_NUM = pagetable[PAGE_NUM]; //Get frame number
        physical_address = (FRAME_NUM << OFFSET_BITS) | PAGE_OFFSET; //Calculate the physical address at a given page number
        printf("Virtual addr is %d: Page# = %d & Offset = %d frame number = %d Physical addr = %d \n", logical_address, PAGE_NUM, PAGE_OFFSET, FRAME_NUM, physical_address);
    }

    fclose(addresses); //Close address file 
}