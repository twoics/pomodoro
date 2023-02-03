#include <malloc.h>
#include "session_bar.h"

void draw_session_bar(int percentage, struct session_bar_setting settings) {
    const char** bar = build(percentage, settings.bar_settings);
    struct bar_settings bar_setting = settings.bar_settings;

    int total_bar_len = bar_setting.bar_len;
    if (bar_setting.left_border != NULL) {
        total_bar_len++;
    }
    if (bar_setting.right_border != NULL) {
        total_bar_len++;
    }

    for (int i = 0; i < total_bar_len; ++i) {
        printf("%s", bar[i]);
    }
    printf("\n");
    free(bar);
}
