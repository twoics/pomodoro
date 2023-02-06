#ifndef POMODORO_CONFIG_H
#define POMODORO_CONFIG_H

#include "../bar/bar.h"

struct bar_settings configure_progress_bar(char* config_path);

struct bar_settings configure_session_bar(char* file_path, int bar_len);

#endif //POMODORO_CONFIG_H
