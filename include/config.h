/**
 * @file    config.h
 * @brief   Global configuration constants for system_monitor.
 *
 * Adjust these values to tune alert thresholds and
 * sampling behaviour without modifying any source file.
 *
 * @author  smeetnasit
 * @date    2026
 */

#ifndef CONFIG_H
#define CONFIG_H

/** Alert threshold for CPU usage in percent (0.0 - 100.0) */
#define CPU_THRESHOLD       70.0f

/** Alert threshold for memory usage in percent (0.0 - 100.0) */
#define MEM_THRESHOLD       70.0f

/** Sampling interval in seconds between each measurement */
#define POLL_INTERVAL_SEC   5

/** Path to the log file where alerts are written */
#define LOG_FILE            "logs/monitor.log"

/** Application version string */
#define APP_VERSION         "1.0.0"

#endif /* CONFIG_H *//* config.h - Configuration constants */
