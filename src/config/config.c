#include <malloc.h>
#include <string.h>
#include "config.h"
#include "../../lib/libconfig/lib/libconfig.h"
#include "../exceptions/exceptions.h"

#define PROGRESS_BAR_LEN_FIELD "progress_bar_len"
#define PROGRESS_LEFT_BORDER_FIELD "progress_left_border"
#define PROGRESS_RIGHT_BORDER_FIELD "progress_right_border"
#define PROGRESS_COMPLETED_CELL_FIELD "progress_completed_cell"
#define PROGRESS_EMPTY_CELL_FIELD "progress_uncompleted_cell"
#define PROGRESS_CURRENT_CELL_FIELD "progress_current_cell"

#define FAIL_EXIT (-1)

char* get_string_field(const config_t* config, const char** result_storage, const char* field) {
    if (!config_lookup_string(config, field, result_storage)) {
        fprintf(stderr, "No found `%s` field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }

    char* string_outside_conf_area = (char*) malloc(strlen(*result_storage));
    strcpy(string_outside_conf_area, *result_storage);
    return string_outside_conf_area;
}

void get_integer_field(const config_t* config, int* result_storage, const char* field) {
    if (!config_lookup_int(config, field, result_storage)) {
        fprintf(stderr, "No found `%s` field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }
}

struct bar_settings bar_configure(const config_t* config) {
    int bar_len;
    get_integer_field(config, &bar_len, PROGRESS_BAR_LEN_FIELD);

    const char* left_border;
    const char* right_border;
    const char* fill;
    const char* empty;
    const char* current;

    left_border = get_string_field(config, &left_border, PROGRESS_LEFT_BORDER_FIELD);
    right_border = get_string_field(config, &right_border, PROGRESS_RIGHT_BORDER_FIELD);
    fill = get_string_field(config, &fill, PROGRESS_COMPLETED_CELL_FIELD);
    empty = get_string_field(config, &empty, PROGRESS_EMPTY_CELL_FIELD);
    current = get_string_field(config, &current, PROGRESS_CURRENT_CELL_FIELD);

    struct bar_settings bar_sett = {
            bar_len, left_border, right_border, fill, empty, current
    };

    return bar_sett;
}

config_t init_config_file(char* file_path) {
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, file_path)) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        exit_with_code(FAIL_EXIT);
    }

    return cfg;
}

struct progress_bar_settings progress_configure(const config_t* config) {
    struct bar_settings bar_sett = bar_configure(config);
    struct progress_bar_settings progress_sett = {
            bar_sett
    };
    return progress_sett;
}

struct progress_bar_settings configure_progress_bar(char* file_path) {
    config_t cfg = init_config_file(file_path);

    struct progress_bar_settings progress_sett = progress_configure(&cfg);

    config_destroy(&cfg);
    return progress_sett;
}
