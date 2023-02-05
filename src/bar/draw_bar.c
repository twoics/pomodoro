#include <stdio.h>
#include <malloc.h>
#include "draw_bar.h"

void draw_progress(int percentage, struct bar_settings settings) {
    const char** bar = build(percentage, settings);

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

    fflush(stdout);
    printf("\r");
    free(bar);
}