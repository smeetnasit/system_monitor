#include <stdio.h>
#include "memory_monitor.h"

float get_memory_usage(void)
{
    long total     = 0;
    long free_mem  = 0;
    long available = 0;

    /* Open /proc/meminfo — Linux keeps RAM info here */
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        return -1.0f;
    }

    /*
     * /proc/meminfo always has the same order:
     * Line 1: MemTotal
     * Line 2: MemFree
     * Line 3: MemAvailable
     * So we can read them directly with fscanf — no loop needed.
     */
    fscanf(fp, "MemTotal: %ld kB\n",     &total);
    fscanf(fp, "MemFree: %ld kB\n",      &free_mem);
    fscanf(fp, "MemAvailable: %ld kB\n", &available);
    fclose(fp);

    if (total == 0) {
        return -1.0f;
    }

    /* Used = Total minus what is still available */
    return (float)(total - available) / (float)total * 100.0f;
}
