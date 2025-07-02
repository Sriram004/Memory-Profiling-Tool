#ifndef MEMPROF_H
#define MEMPROF_H

#include <stdlib.h>

void track_alloc(void* ptr, size_t size);
void track_free(void* ptr);
size_t get_tracked_size(void* ptr);
void dump_memory_usage();

void log_allocation(const char* type, void* ptr, size_t size);
void log_deallocation(void* ptr);
void initialize_logger();
void close_logger();

#endif
