#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include "../include/memprof.h"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* malloc(size_t size) {
    static void* (*real_malloc)(size_t) = NULL;
    if (!real_malloc) real_malloc = dlsym(RTLD_NEXT, "malloc");
    void* ptr = real_malloc(size);

    pthread_mutex_lock(&lock);
    track_alloc(ptr, size);
    log_allocation("malloc", ptr, size);
    pthread_mutex_unlock(&lock);

    return ptr;
}

void free(void* ptr) {
    static void (*real_free)(void*) = NULL;
    if (!real_free) real_free = dlsym(RTLD_NEXT, "free");

    pthread_mutex_lock(&lock);
    log_deallocation(ptr);
    track_free(ptr);
    pthread_mutex_unlock(&lock);

    real_free(ptr);
}

// (Similar wrapping for calloc and realloc...)

__attribute__((constructor))
void on_start() {
    initialize_logger();
}

__attribute__((destructor))
void on_exit() {
    dump_memory_usage();
    close_logger();
}
