/*
*
* Author: Prof. Neerja Mhaskar
* Course: Operating Systems Comp Sci/SFWRWENG 3SH3

*/
#include <stdio.h>
#include <unistd.h>

//Define the needed macros
#define BUFFER_SIZE 10
#define OFFSET_MASK 4095
#define PAGES 8
#define OFFSET_BITS 12
#define PAGE_SIZE 2^12

int main(int argc, char *argv[]) {
    //declare variables and declare and initialize the page table.
	char buff[BUFFER_SIZE];
	int page_table[PAGES] = {6,4,3,7,0,1,2,5};
	int PAGE_NUM = 0;
	int PAGE_OFFSET = 0;
	int Physical_address = 0;
	int frame_number = 0;
	/*Declare a file pointer fptr. fopen initializes an object of type file.
	 This is stored in fptr. The mode 'r' indicates that the file is for 
	read only purpose.*/
	FILE *fptr = fopen("labaddr.txt", "r");

	/*Read characters from the file at a time.
	These characters are stored in buff to read the logical addresses*/
    while(fgets(buff, BUFFER_SIZE, fptr) != NULL) {
		
		
		PAGE_NUM = atoi(buff) >> OFFSET_BITS;
		PAGE_OFFSET = atoi(buff) & OFFSET_MASK;
		frame_number = page_table[PAGE_NUM];
		Physical_address = (frame_number << OFFSET_BITS) | PAGE_OFFSET;
		printf("Virtual addr is: %s, Page# = %d & Offset = %d. Physical addr = %d ", buff, PAGE_NUM, PAGE_OFFSET, Physical_address);
		
	}
    /*While you read the logical addresses using bitwise operators in C to compute the physical address for each logical address read and print it*/

	/*Close the file.*/
	fclose(fptr);


	return 0;
}
