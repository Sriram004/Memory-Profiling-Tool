#!/bin/bash

mkdir -p build

gcc -fPIC -shared -o build/libmemprof.so \
    src/memprof.c src/tracker.c utils/logger.c -Iinclude -ldl -pthread

gcc -o build/test test/test_program.c

echo "[+] Build complete."
