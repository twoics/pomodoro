#ifndef POMODORO_DRAW_BAR_H
#define POMODORO_DRAW_BAR_H

#include "bar.h"

void draw_progress_bar(int percentage, struct bar_settings settings);

void draw_sessions_bar(int completed_cells, struct bar_settings settings);

#endif //POMODORO_DRAW_BAR_H
