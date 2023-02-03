#ifndef POMODORO_SESSION_BAR_H
#define POMODORO_SESSION_BAR_H

#include "../bar/bar.h"

struct session_bar_setting {
    struct bar_settings bar_settings;
};

void draw_session_bar(int passed_sessions, struct session_bar_setting settings);

#endif //POMODORO_SESSION_BAR_H
