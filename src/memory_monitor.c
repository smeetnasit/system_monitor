/**
 * @file    memory_monitor.c
 * @brief   Implementation of memory usage monitoring.
 *
 * /proc/meminfo exposes memory statistics maintained by the
 * Linux kernel. Unlike /proc/stat (which needs two readings),
 * memory usage is calculated from a single snapshot.
 *
 * Formula:
 *   used_percent = (MemTotal - MemAvailable) / MemTotal * 100
 *
 * @author  smeetnasit
 * @date    2026
 */

#include <stdio.h>
#include "memory_monitor.h"

#define PROC_MEMINFO "/proc/meminfo"

static int read_meminfo_field(const char *field, long *value)
{

    static char line[128];

    FILE *fp = fopen(PROC_MEMINFO, "r");
    if (fp == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {

        char label[128];
        long temp;

        if (sscanf(line, "%127s %ld", label, &temp) == 2) {

            char field_with_colon[128];
            snprintf(field_with_colon, sizeof(field_with_colon),
                     "%s:", field);

            if (strcmp(label, field_with_colon) == 0) {
                *value = temp;
                fclose(fp);
                return 0;  /* success */
            }
        }
    }

    fclose(fp);
    return -1;  /* field not found */
}

float get_memory_usage(void)
{
    long total     = 0;
    long available = 0;

    if (read_meminfo_field("MemTotal",     &total)     != 0) {
        return -1.0f;
    }
    if (read_meminfo_field("MemAvailable", &available) != 0) {
        return -1.0f;
    }

    if (total == 0) {
        return -1.0f;
    }


    return (float)(total - available) / (float)total * 100.0f;
}

long get_total_ram_kb(void)
{
    long total = 0;

    if (read_meminfo_field("MemTotal", &total) != 0) {
        return -1;
    }

    return total;
}
