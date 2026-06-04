#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

/*
 * Returns CPU usage as a percentage (0.0 to 100.0).
 * Returns -1.0 if something goes wrong.
 * Call this in a loop — it compares each reading to the last one.
 */
float get_cpu_usage(void);

#endif
