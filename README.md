# system_monitor

![Language](https://img.shields.io/badge/Language-C-blue)
![Standard](https://img.shields.io/badge/Standard-C11-blue)
![Platform](https://img.shields.io/badge/Platform-Linux-green)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen)
![License](https://img.shields.io/badge/License-MIT-yellow)

A lightweight system monitoring daemon written in C for Linux.  
Reads CPU and memory usage directly from the `/proc` virtual filesystem,
evaluates user-defined thresholds, and writes timestamped alerts to a log file.

---

## Demo

```
===========================================
  Linux System Monitor started
  CPU threshold : 80%
  MEM threshold : 75%
  Poll interval : 2s
  Log file      : logs/monitor.log
===========================================

CPU:   9.7%  |  Memory:  17.8%
CPU:   7.1%  |  Memory:  17.8%
CPU:   3.0%  |  Memory:  17.8%
  [ALERT] CPU usage critical: 81.2%
```

---

## Motivation

Low-level system monitoring is a fundamental task in embedded Linux and
IoT environments. This project demonstrates direct interaction with the
Linux kernel via the `/proc` filesystem using only the C standard library —
no external dependencies required.

---

## Features

- Real-time CPU usage calculation from `/proc/stat`
- Memory usage monitoring from `/proc/meminfo`
- Configurable alert thresholds via `config.h`
- Timestamped alert logging to `logs/monitor.log`
- Modular architecture — one responsibility per module
- Zero external dependencies — C standard library only

---

## Project Structure

```
system_monitor/
├── src/
│   ├── main.c              Entry point and polling loop
│   ├── cpu_monitor.c       CPU usage calculation (/proc/stat)
│   ├── memory_monitor.c    Memory usage calculation (/proc/meminfo)
│   └── logger.c            Timestamped alert logging
├── include/
│   ├── config.h            Thresholds and settings
│   ├── cpu_monitor.h
│   ├── memory_monitor.h
│   └── logger.h
├── logs/                   Runtime log output (not tracked in git)
├── Makefile
└── README.md
```

---

## Requirements

| Tool | Version |
|------|---------|
| GCC  | >= 7.0  |
| Make | any     |
| OS   | Linux (reads `/proc` filesystem) |

---

## Build and Run

```bash
# Clone the repository
git clone https://github.com/smeetnasit/system_monitor.git
cd system_monitor

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
#define CPU_THRESHOLD      80.0f  /* Alert if CPU usage exceeds 80%  */
#define MEM_THRESHOLD      75.0f  /* Alert if memory usage exceeds 75% */
#define POLL_INTERVAL_SEC  2      /* Sampling interval in seconds     */
#define LOG_FILE           "logs/monitor.log"
```

---

## How It Works

```
Linux Kernel
    │
    ├── /proc/stat      ← CPU time counters (sampled twice, delta calculated)
    └── /proc/meminfo   ← MemTotal and MemAvailable

         │
         ▼
    system_monitor
         │
         ├── cpu > threshold  → log_alert() → logs/monitor.log
         └── mem > threshold  → log_alert() → logs/monitor.log
```

**CPU usage formula:**
```
cpu % = (delta_total - delta_idle) / delta_total × 100
```

**Memory usage formula:**
```
mem % = (MemTotal - MemAvailable) / MemTotal × 100
```

---

## Log Output Example

```
[Wed Jun  4 10:22:31 2025] ALERT: CPU usage critical: 83.4%
[Wed Jun  4 10:22:33 2025] ALERT: Memory usage critical: 77.1%
```

---

## Git Workflow Used

This project was developed using a professional branching strategy:

```
main          ← stable releases only
  └── smeet_dev    ← integration branch
        ├── feature/config
        ├── feature/cpu-monitor
        ├── feature/memory-monitor
        ├── feature/logger
        └── feature/main
```

---

## What I Learned

- Reading Linux kernel data via the `/proc` virtual filesystem
- Modular C project structure with header/source separation
- File I/O in C (`fopen`, `fscanf`, `fprintf`, `fclose`)
- Static local variables for stateful calculations
- Makefile build system with compiler warning flags
- Professional Git workflow with feature branches and merge commits

---

## Future Improvements

- [ ] CPU temperature monitoring via `/sys/class/thermal`
- [ ] Disk usage monitoring via `statvfs()`
- [ ] Email or desktop notification on alert
- [ ] GPIO LED alert on Raspberry Pi
- [ ] Configurable log rotation

---

## Author

**Smeet Nasit**  
GitHub: [github.com/smeetnasit](https://github.com/smeetnasit)

---

## License

This project is licensed under the MIT License.
