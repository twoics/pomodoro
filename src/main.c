#include <unistd.h>
#include "timer/timer.h"
#include "config/config.h"
#include "./cli_cleaner/cli_cleaner.h"
#include "bar/draw_bar.h"

#define CONFIG_FILE_PATH "../conf/configuration.cfg"

int main() {
    int SESSIONS_COUNT = 2;
    int SESSION_DURATION_SECONDS = 5;

    struct bar_settings progress_sett = configure_progress_bar(CONFIG_FILE_PATH);
    struct bar_settings session_sett = configure_session_bar(CONFIG_FILE_PATH, SESSIONS_COUNT);

    int percentage;
    for (int completed_cells = 0; completed_cells < SESSIONS_COUNT; ++completed_cells) {
        time_t start_session_time = time(NULL);
        time_t end_session_time = start_session_time + SESSION_DURATION_SECONDS;
        percentage = 0;

        draw_sessions(completed_cells, session_sett);

        while (percentage < 100) {
            percentage = percent_passed_time(time(NULL), start_session_time, end_session_time);
            draw_progress(percentage, progress_sett);
            sleep(1);
        }

        clear_cli();
    }

    return 0;
}
