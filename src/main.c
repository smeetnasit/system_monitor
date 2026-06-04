#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "logger.h"

int main(void)
{
    /* Buffer to build alert messages */
    char msg[64];

    printf("===========================================\n");
    printf("  Linux System Monitor started\n");
    printf("  CPU threshold : %.0f%%\n", CPU_THRESHOLD);
    printf("  MEM threshold : %.0f%%\n", MEM_THRESHOLD);
    printf("  Poll interval : %ds\n",    POLL_INTERVAL_SEC);
    printf("  Log file      : %s\n",     LOG_FILE);
    printf("===========================================\n\n");

    while (1) {
        float cpu = get_cpu_usage();
        float mem = get_memory_usage();

        printf("CPU: %5.1f%%  |  Memory: %5.1f%%\n", cpu, mem);

        if (cpu > CPU_THRESHOLD) {
            snprintf(msg, sizeof(msg),
                     "CPU usage critical: %.1f%%", cpu);
            log_alert(msg);
        }

        if (mem > MEM_THRESHOLD) {
            snprintf(msg, sizeof(msg),
                     "Memory usage critical: %.1f%%", mem);
            log_alert(msg);
        }

        sleep(POLL_INTERVAL_SEC);
    }

    return 0;
}
