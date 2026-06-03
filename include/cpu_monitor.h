/**
 * @file    cpu_monitor.h
 * @brief   Public interface for CPU usage monitoring.
 *
 * Reads CPU time counters from /proc/stat and calculates
 * the CPU usage percentage between two consecutive samples.
 *
 * @author  smeetnasit
 * @date    2026
 */

#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

/**
 * @brief  Calculate current CPU usage as a percentage.
 *
 * Must be called at least twice to return a meaningful value.
 * The first call always returns 0.0 as it establishes the
 * baseline snapshot.
 *
 * @return CPU usage in percent (0.0 - 100.0), or -1.0 on error.
 */
float get_cpu_usage(void);

#endif /* CPU_MONITOR_H *//* cpu_monitor.h */
