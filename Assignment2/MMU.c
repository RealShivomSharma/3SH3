#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256
#define TLB_SIZE 16
#define FRAME_SIZE PAGE_SIZE
#define FRAME_COUNT (1 << 15) // 2^15 frames in physical memory
#define PAGE_COUNT (1 << 16) // 2^16 pages in virtual memory
#define BACKING_STORE_FILE "BACKING_STORE.bin"
#define ADDRESS_FILE "addresses.txt"

typedef struct {
    int page_number;
    int frame_number;
} tlb_entry_t;

tlb_entry_t tlb[TLB_SIZE];
int page_table[PAGE_TABLE_SIZE];
char physical_memory[FRAME_SIZE * FRAME_COUNT];
bool frame_is_loaded[FRAME_COUNT];
int oldest_loaded_frame_index = 0;
int next_unassigned_frame_index = 0;
int tlb_hit_count = 0;
int tlb_miss_count = 0;
int page_fault_count = 0;

void init_tlb() {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].page_number = -1;
        tlb[i].frame_number = -1;
    }
}

void init_page_table() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }
}

int load_page_into_memory(int page_number) {
    FILE *backing_store_file = fopen(BACKING_STORE_FILE, "rb");
    if (backing_store_file == NULL) {
        fprintf(stderr, "Error opening backing store file.\n");
        exit(EXIT_FAILURE);
    }

    if (fseek(backing_store_file, page_number * PAGE_SIZE, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking to page %d in backing store file.\n", page_number);
        exit(EXIT_FAILURE);
    }

    if (fread(physical_memory + next_unassigned_frame_index * FRAME_SIZE, 1, FRAME_SIZE, backing_store_file) != FRAME_SIZE) {
        fprintf(stderr, "Error reading page %d from backing store file.\n", page_number);
        exit(EXIT_FAILURE);
    }

    int frame_number = next_unassigned_frame_index;
    next_unassigned_frame_index = (next_unassigned_frame_index + 1) % FRAME_COUNT;
    frame_is_loaded[frame_number] = true;
    page_table[page_number] = frame_number;

    fclose(backing_store_file);
    return frame_number;
}

int lookup_tlb(int page_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].page_number == page_number) {
            tlb_hit_count++;
            return tlb[i].frame_number;
        }
    }
    tlb_miss_count++;
    return -1;
}

void add_to_tlb(int page_number, int frame_number) {
    tlb[oldest_loaded_frame_index].page_number = page_number;
    tlb[oldest_loaded_frame_index].frame_number = frame_number;
    oldest_loaded_frame_index = (oldest_loaded_frame_index + 1) % TLB_SIZE;
}

int translate_logical_to_physical_address(int logical_address) {
    int page_number = (logical_address >> 8) & 0xff;
    int page_offset = logical_address & 0xff;

    int frame_number = lookup_tlb(page_number);
    if (frame_number == -1) {
        frame_number = page