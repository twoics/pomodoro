#ifndef POMODORO_BAR_H
#define POMODORO_BAR_H

struct bar_settings {
    const int bar_len;
    const char* const left_border;
    const char* const right_border;
    const char* const fill;
    const char* const empty;
    const char* const current;
};

const char** build(int percentage_completed, struct bar_settings settings);
#endif //POMODORO_BAR_H
