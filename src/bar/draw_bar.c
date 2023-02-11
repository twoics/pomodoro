#include <stdio.h>
#include <malloc.h>
#include "draw_bar.h"

#define PERCENT_IN_ONE_SHARE 100

void draw_bar(const char** bar, struct bar_settings settings)
{
    int total_bar_len = settings.bar_len;
    if (settings.left_border != NULL) {
        total_bar_len++;
    }
    if (settings.right_border != NULL) {
        total_bar_len++;
    }

    if (settings.message_before_bar != NULL) {
        printf("%s", settings.message_before_bar);
        fflush(stdout);
    }

    for (int i = 0; i < total_bar_len; ++i) {
        printf("%s", bar[i]);
    }

}

void draw_progress_bar(int percentage, struct bar_settings settings) {
    const char** bar = build(percentage, settings);

    draw_bar(bar, settings);

    printf(" %d%%", percentage);
    fflush(stdout);

    printf("\r");
    free(bar);
}


void draw_sessions_bar(int completed_cells, struct bar_settings settings) {
    int percentage;
    double share_passed_sessions = (double) completed_cells / (double) settings.bar_len;
    percentage = (int) (share_passed_sessions * PERCENT_IN_ONE_SHARE);

    const char** bar = build(percentage, settings);
    draw_bar(bar, settings);

    printf("\n");
}
