#ifndef POMODORO_CONFIG_H
#define POMODORO_CONFIG_H

#include "../progress_bar/progress_bar.h"
#include "../session_bar/session_bar.h"

struct configuration {
    struct progress_bar_settings progress_settings;
    struct session_bar_setting session_settings;

};

struct configuration configure(char* config_path);

#endif //POMODORO_CONFIG_H
