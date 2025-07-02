#include <stdio.h>
#include <stdlib.h>
#include "../include/memprof.h"

typedef struct MemEntry {
    void* ptr;
    size_t size;
    struct MemEntry* next;
} MemEntry;

static MemEntry* head = NULL;

void track_alloc(void* ptr, size_t size) {
    if (!ptr) return;
    MemEntry* entry = malloc(sizeof(MemEntry));
    entry->ptr = ptr;
    entry->size = size;
    entry->next = head;
    head = entry;
}

void track_free(void* ptr) {
    MemEntry **curr = &head, *temp;
    while (*curr) {
        if ((*curr)->ptr == ptr) {
            temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            return;
        }
        curr = &((*curr)->next);
    }
}

size_t get_tracked_size(void* ptr) {
    MemEntry* curr = head;
    while (curr) {
        if (curr->ptr == ptr)
            return curr->size;
        curr = curr->next;
    }
    return 0;
}

void dump_memory_usage() {
    MemEntry* curr = head;
    size_t leak_total = 0;
    fprintf(stderr, "\n🧠 Memory Leak Report:\n");
    while (curr) {
        fprintf(stderr, "Leaked: %p (%zu bytes)\n", curr->ptr, curr->size);
        leak_total += curr->size;
        curr = curr->next;
    }
    fprintf(stderr, "Total Leaked: %zu bytes\n", leak_total);
}
