#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "config.h"

void log_alert(const char *message)
{
    /* Open log file in append mode — adds to end, never overwrites */
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp == NULL) {
        printf("ERROR: could not open log file\n");
        return;
    }

    /* Get current time as a readable string */
    time_t now       = time(NULL);
    char  *timestamp = ctime(&now);

    /* ctime adds \n at the end — replace it with \0 to remove it */
    timestamp[24] = '\0';

    /* Write to log file */
    fprintf(fp, "[%s] ALERT: %s\n", timestamp, message);
    fclose(fp);

    /* Also show on terminal */
    printf("  [ALERT] %s\n", message);
}
