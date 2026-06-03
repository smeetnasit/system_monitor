# system_monitor

A lightweight system monitoring daemon written in C for Linux.  
Reads CPU and memory usage directly from the `/proc` virtual filesystem,
evaluates user-defined thresholds, and writes timestamped alerts to a log file.

---

## Motivation

Low-level system monitoring is a fundamental task in embedded Linux and
IoT environments. This project demonstrates direct interaction with the
Linux kernel via the `/proc` filesystem using only the C standard library —
no external dependencies.

---

## Features

- Real-time CPU usage calculation from `/proc/stat`
- Memory usage monitoring from `/proc/meminfo`
- Configurable alert thresholds via `config.h`
- Timestamped log output to `logs/monitor.log`
- Modular architecture — one module per responsibility

---

## Project structure

system_monitor/
├── src/
│   ├── main.c              Entry point and polling loop
│   ├── cpu_monitor.c       CPU usage calculation
│   ├── memory_monitor.c    Memory usage calculation
│   └── logger.c            Alert logging to file
├── include/
│   ├── config.h            Thresholds and settings
│   ├── cpu_monitor.h
│   ├── memory_monitor.h
│   └── logger.h
├── logs/                   Runtime log output (not tracked)
├── Makefile
└── README.md

---

## Requirements

- GCC (>= 7.0)
- GNU Make
- Linux kernel (reads `/proc` filesystem)

---

## Build and run

```bash
# Build
make

# Run
./system_monitor

# Build and run in one step
make run

# Remove binary and logs
make clean
```

---

## Configuration

Edit `include/config.h` to adjust thresholds and poll interval:

```c
#define CPU_THRESHOLD      80.0   /* Alert if CPU usage exceeds 80% */
#define MEM_THRESHOLD      75.0   /* Alert if memory usage exceeds 75% */
#define POLL_INTERVAL_SEC  2      /* Sampling interval in seconds     */
#define LOG_FILE           "logs/monitor.log"
```

---

## Log output example
[Wed Jun  4 10:22:31 2025] ALERT: CPU usage critical: 83.4%
[Wed Jun  4 10:22:33 2025] ALERT: Memory usage critical: 77.1%

---

## Author

Smeet Nasit
GitHub:https://github.com/smeetnasit
