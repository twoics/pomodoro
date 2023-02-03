#include <unistd.h>
#include "timer/timer.h"
#include "config/config.h"
#include "./cli_cleaner/cli_cleaner.h"

#define CONFIG_FILE_PATH "../conf/configuration.cfg"

int main() {
    int SESSIONS_COUNT = 2;
    int SESSION_DURATION_SECONDS = 5;

    struct progress_bar_settings progress_sett = configure_progress_bar(CONFIG_FILE_PATH);
    struct session_bar_setting session_sett = configure_session_bar(CONFIG_FILE_PATH, SESSIONS_COUNT);

    int percentage;
    for (int session_index = 0; session_index < SESSIONS_COUNT; ++session_index) {
        time_t start_session_time = time(NULL);
        time_t end_session_time = start_session_time + SESSION_DURATION_SECONDS;
        percentage = 0;

        draw_session_bar(session_index, session_sett);

        while (percentage < 100) {
            percentage = percent_passed_time(time(NULL), start_session_time, end_session_time);
            draw_progress(percentage, progress_sett);
            sleep(1);
        }

        clear_cli();
    }

    return 0;
}
