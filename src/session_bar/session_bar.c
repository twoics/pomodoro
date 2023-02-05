#include <malloc.h>
#include "session_bar.h"

#define PERCENT_IN_ONE_SHARE 100

void draw_session_bar(int passed_sessions, struct session_bar_setting settings) {
    int percentage;
    double share_passed_sessions = (double) passed_sessions / (double) settings.bar_settings.bar_len;
    percentage = (int) (share_passed_sessions * PERCENT_IN_ONE_SHARE);

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
    printf("\n");
    free(bar);
}
