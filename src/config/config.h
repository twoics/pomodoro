#ifndef POMODORO_CONFIG_H
#define POMODORO_CONFIG_H

#include "../progress_bar/progress_bar.h"
#include "../session_bar/session_bar.h"

struct progress_bar_settings configure_progress_bar(char* config_path);

struct session_bar_setting configure_session_bar(char* file_path, int bar_len);

#endif //POMODORO_CONFIG_H
