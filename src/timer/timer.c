#include "timer.h"
#include "time.h"

#define PERCENT_IN_SHARE 100

int percent_passed_time(time_t current_time, time_t start_time, time_t end_time) {
    double interval = (double) (end_time - start_time);
    double passed = (double) (current_time - start_time);

    if (interval == 0) {
        return -1;
    }

    double share_passed = passed / interval;

    return (int) (share_passed * PERCENT_IN_SHARE);
}
