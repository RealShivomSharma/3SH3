

#include <stdio.h>
#include <unistd.h>


#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/
#include <stdlib.h> /*For file descriptors*/


//Define the needed macros
#define PAGES        10
#define BUFFER_SIZE  15
#define PAGE_SIZE   256
#define OFFSET_BITS  8
#define OFFSET_MASK  255


/*Define the needed macros*/
#define INT_SIZE 4 // Size of integer in bytes
#define INT_COUNT 10 
#define MEMORY_SIZE (INT_COUNT * INT_SIZE) 

// Define character pointer to store the starting address of the memory mapped file

//Define integer array to store numbers from the memory mapped file.
int page_table[MEMORY_SIZE]; 
signed char *mmapfptr; 
int sum = 0;


int main(int argc, char *argv[]) {

    //declare variables and declare and initialize the page table.
	int pagenum = 0; int pageoffset = 0; int physical_add = 0; int frame_num = 0;
	

	/*Declare a file pointer fptr. fopen initializes an object of type file.
	 This is stored in fptr. The mode 'r' indicates that the file is for 
	read only purpose.*/

	FILE *fptr = fopen("ltaddr.txt", "r");

    //Use the open() system call to open and read the numbers.bin file.
    int mmapfile_fd = open("page_table.bin", O_RDONLY); 
    
    //Use the mmap() system call to memory map numbers.bin file
    mmapfptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0); 
   

    //Use a for loop to retrieve the contents of the memory mapped file and store it in the integer array using memcpy() function.
    for(int i = 0; i < MEMORY_SIZE; i++){
        memcpy(page_table + i, mmapfptr + 4*i, INT_SIZE);
    }

    munmap(mmapfptr, MEMORY_SIZE); 

	/*Read characters from the file at a time.
	These characters are stored in buff to read the logical addresses*/
	char buff[BUFFER_SIZE];
	while(fgets(buff, BUFFER_SIZE, fptr) != NULL){
		pagenum = atoi(buff) >> OFFSET_BITS;
		pageoffset = atoi(buff) & OFFSET_MASK;
		physical_add = page_table[pagenum] << OFFSET_BITS | pageoffset;
		printf("Virtual addr is %d ", atoi(buff));
        printf("Page# = %d & ", pagenum);
        printf("Offset = %d ", pageoffset);
        printf("frame number = %d ", page_table[pagenum]);
		printf("Physical addr = %d\n", physical_add);
		
	}

	/*Close the file.*/
	fclose(fptr);

	return 0;
}