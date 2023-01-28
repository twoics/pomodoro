#ifndef POMODORO_PROGRESS_H
#define POMODORO_PROGRESS_H

struct bar_settings {
    const int bar_len;
    const char* const left_border;
    const char* const right_border;
    const char* const fill;
    const char* const empty;
    const char* const current;
};

void draw_progress(int percentage, struct bar_settings settings);

#endif //POMODORO_PROGRESS_H
