#include <malloc.h>
#include "progress_bar.h"

void draw_progress(int percentage, struct progress_bar_settings settings) {
    const char** bar = build(percentage, settings.bar_settings);

    struct bar_settings bar_setting = settings.bar_settings;

    int total_bar_len = bar_setting.bar_len;
    if (bar_setting.left_border != NULL) {
        total_bar_len++;
    }
    if (bar_setting.right_border != NULL) {
        total_bar_len++;
    }

    if (bar_setting.message_before_bar != NULL) {
        printf("%s", bar_setting.message_before_bar);
        fflush(stdout);
    }

    for (int i = 0; i < total_bar_len; ++i) {
        printf("%s", bar[i]);
    }

    fflush(stdout);
    printf("\r");
    free(bar);
}