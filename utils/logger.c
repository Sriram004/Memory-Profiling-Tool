#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/memprof.h"

static FILE* log_file = NULL;

void initialize_logger() {
    log_file = fopen("memprof.log", "w");
    if (!log_file) log_file = stderr;
}

void close_logger() {
    if (log_file && log_file != stderr)
        fclose(log_file);
}

void log_allocation(const char* type, void* ptr, size_t size) {
    fprintf(log_file, "[%s] %p (%zu bytes)\n", type, ptr, size);
}

void log_deallocation(void* ptr) {
    fprintf(log_file, "[free] %p\n", ptr);
}
