#include "timer.h"
#include "time.h"

#define PERCENT_IN_SHARE 100
#define FAILURE_CODE (-1)

int percent_passed_time(time_t current_time, time_t start_time, time_t end_time) {
    double interval = (double) (end_time - start_time);
    double passed = (double) (current_time - start_time);

    if (interval == 0) {
        return FAILURE_CODE;
    }

    double share_passed = passed / interval;

    return (int) (share_passed * PERCENT_IN_SHARE);
}
