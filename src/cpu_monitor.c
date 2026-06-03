/**
 * @file    cpu_monitor.c
 * @brief   Implementation of CPU usage monitoring.
 *
 * Reads /proc/stat which exposes cumulative CPU time counters
 * maintained by the Linux kernel since system boot.
 *
 * /proc/stat format (first line):
 *   cpu  user nice system idle iowait irq softirq
 *
 * CPU usage % = (delta_total - delta_idle) / delta_total * 100
 *
 * @author  smeetnasit
 * @date    2025
 */

#include <stdio.h>
#include "cpu_monitor.h"

#define PROC_STAT "/proc/stat"

float get_cpu_usage(void)
{
    /* Static variables persist between function calls.
     * They store the previous sample for delta calculation. */
    static long prev_idle  = 0;
    static long prev_total = 0;

    FILE *fp = fopen(PROC_STAT, "r");
    if (fp == NULL) {
        return -1.0f;
    }

    /* Read all seven CPU time fields from /proc/stat */
    long user, nice, system, idle, iowait, irq, softirq;
    int matched = fscanf(fp, "cpu %ld %ld %ld %ld %ld %ld %ld",
                         &user, &nice, &system,
                         &idle, &iowait, &irq, &softirq);
    fclose(fp);

    /* Validate that all fields were read correctly */
    if (matched != 7) {
        return -1.0f;
    }

    /* idle time includes iowait — CPU is idle during I/O waits */
    long idle_time  = idle + iowait;

    /* total time is the sum of all CPU states */
    long total_time = user + nice + system +
                      idle + iowait + irq + softirq;

    /* Calculate deltas between this sample and previous sample */
    long delta_idle  = idle_time  - prev_idle;
    long delta_total = total_time - prev_total;

    /* Save current values for next call */
    prev_idle  = idle_time;
    prev_total = total_time;

    /* Avoid division by zero on first call */
    if (delta_total == 0) {
        return 0.0f;
    }

    return (float)(delta_total - delta_idle) / (float)delta_total * 100.0f;
}/* cpu_monitor.c - CPU usage monitor (implementation pending) */
