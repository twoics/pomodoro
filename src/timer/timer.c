#include "timer.h"
#include "time.h"

#define PERCENT_IN_SHARE 100
#define MAX_PERCENT 100
#define EMPTY_INTERVAL 0
#define FAILURE_CODE (-1)

int passed_percent(double passed, double interval) {
    double share_passed = passed / interval;

    int percent = (int) (share_passed * PERCENT_IN_SHARE);

    if (percent > MAX_PERCENT) {
        return MAX_PERCENT;
    }
    return percent;
}

int percent_passed_time(time_t current_time, time_t start_time, time_t end_time) {
    double interval = (double) (end_time - start_time);
    double passed = (double) (current_time - start_time);

    if (interval == EMPTY_INTERVAL) {
        return FAILURE_CODE;
    }

    return passed_percent(passed, interval);
}
