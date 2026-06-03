/**
 * @file    memory_monitor.h
 * @brief   Public interface for memory usage monitoring.
 *
 * Reads memory statistics from /proc/meminfo and calculates
 * the percentage of RAM currently in use.
 *
 * @author  smeetnasit
 * @date    2025
 */

#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

/**
 * @brief  Calculate current memory usage as a percentage.
 *
 * Uses MemAvailable (not MemFree) to correctly account for
 * reclaimable cache memory, matching the behaviour of tools
 * such as htop and free(1).
 *
 * @return Memory usage in percent (0.0 - 100.0), or -1.0 on error.
 */
float get_memory_usage(void);

/**
 * @brief  Return total physical RAM in kilobytes.
 *
 * Useful for displaying system information in the log header.
 *
 * @return Total RAM in kB, or -1 on error.
 */
long get_total_ram_kb(void);

#endif /* MEMORY_MONITOR_H *//* memory_monitor.h */
