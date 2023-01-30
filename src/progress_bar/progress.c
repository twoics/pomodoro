#include <malloc.h>
#include "progress.h"

void draw_progress(int percentage, struct progress_bar_settings settings) {
    const char** bar = build(percentage, settings.bar_setting);

    struct bar_settings bar_setting = settings.bar_setting;

    int total_bar_len = bar_setting.bar_len;
    if (bar_setting.left_border != NULL) {
        total_bar_len++;
    }
    if (bar_setting.right_border != NULL) {
        total_bar_len++;
    }

    for (int i = 0; i < bar_setting.bar_len + total_bar_len; ++i) {
        printf("%s", bar[i]);
    }

    fflush(stdout);
    printf("\r");
    free(bar);
}