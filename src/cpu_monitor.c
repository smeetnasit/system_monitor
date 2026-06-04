#include <stdio.h>
#include "cpu_monitor.h"

float get_cpu_usage(void)
{
    /* Remember the last reading between calls */
    static long prev_idle  = 0;
    static long prev_total = 0;

    long user, nice, system, idle, iowait, irq, softirq;

    /* Open /proc/stat — this is where Linux keeps CPU counters */
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        return -1.0f;
    }

    /* Read the 7 numbers from the first "cpu" line */
    fscanf(fp, "cpu %ld %ld %ld %ld %ld %ld %ld",
           &user, &nice, &system,
           &idle, &iowait, &irq, &softirq);
    fclose(fp);

    /* Idle time includes iowait — CPU is doing nothing during both */
    long idle_time  = idle + iowait;
    long total_time = user + nice + system + idle + iowait + irq + softirq;

    /* How much changed since last reading */
    long delta_idle  = idle_time  - prev_idle;
    long delta_total = total_time - prev_total;

    /* Save for next call */
    prev_idle  = idle_time;
    prev_total = total_time;

    /* First call has no previous data — return 0 */
    if (delta_total == 0) {
        return 0.0f;
    }

    /* Busy time / total time × 100 = CPU usage % */
    return (float)(delta_total - delta_idle) / (float)delta_total * 100.0f;
}
