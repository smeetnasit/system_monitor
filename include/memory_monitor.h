#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

/*
 * Returns memory usage as a percentage (0.0 to 100.0).
 * Returns -1.0 if something goes wrong.
 */
float get_memory_usage(void);

#endif
