#include <stdio.h>
#include <unistd.h>
#include "timer/timer.h"

int main() {
    time_t time1 = time(NULL);
    printf("%d", percent_passed_time(time(NULL) + 100, time(NULL), time1 + 60 * 10));
    return 0;
}
