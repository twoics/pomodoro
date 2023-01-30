#ifndef POMODORO_PROGRESS_BAR_H
#define POMODORO_PROGRESS_BAR_H

#include "../bar/bar.h"

struct progress_bar_settings {
    struct bar_settings bar_setting;
};

void draw_progress(int percentage, struct progress_bar_settings settings);

#endif //POMODORO_PROGRESS_BAR_H
