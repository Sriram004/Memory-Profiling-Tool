# Memory-Profiling-Tool
# 📦 MemProf — Advanced Memory Profiling Tool

A lightweight yet powerful C memory profiler using `LD_PRELOAD`, designed to intercept allocations (`malloc`, `calloc`, `realloc`, `free`) and provide detailed tracking, leak detection, and customizable logging.

---

## 🔍 Features

- **Accurate Allocation Tracking**  
  Maps each pointer to its allocated size for precise memory usage stats.
- **Leak Detection**  
  Reports any allocations not freed before program exit.
- **Structured Logging**  
  Supports customizable levels and output targets (file or stderr).
- **Configurable via `memprof.conf`**  
  Options include logging level, output destination, and leak tracking.
- **Easy Integration**  
  Inject via `LD_PRELOAD`—no need to modify target source code.

---

## 📁 Project Structure

memprof/
├── include/
│ └── memprof.h # Core function declarations & configuration
├── src/
│ ├── memprof.c # Intercepts memory functions & orchestration
│ └── tracker.c # Hash map logic: tracking ptr → size
├── utils/
│ └── logger.c # Logging engine (file/stderr, levels)
├── test/
│ └── test_program.c # Example app with allocations & leaks
├── build.sh # Quick build script
├── Makefile # Optional build system
├── memprof.conf # Config file for profiler behavior
├── README.md # This file
└── LICENSE # MIT License

yaml
Copy
Edit

---

## ⚙️ Prerequisites

- Linux or UNIX-like environment
- `gcc` compiler
- Basic tools: `make`, `bash`, `LD_PRELOAD` support

---

## 🛠 Build & Run

Build both the profiler and test example:

```bash
chmod +x build.sh
./build.sh
That creates:

build/libmemprof.so — the profiler library

build/test — sample program with memory usage and leaks

Run it like this:

bash
Copy
Edit
LD_PRELOAD=./build/libmemprof.so ./build/test
