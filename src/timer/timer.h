#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include "time.h"

int percent_passed_time(time_t current_time, time_t start_time, time_t end_time);

#endif //POMODORO_TIMER_H
