#include <malloc.h>
#include <string.h>
#include "config.h"
#include "../../lib/libconfig/lib/libconfig.h"
#include "../exceptions/exceptions.h"

#define PROGRESS_NAME_LEN_FIELD "progress_bar_len"
#define PROGRESS_NAME_LEFT_BORDER_FIELD "progress_left_border"
#define PROGRESS_NAME_RIGHT_BORDER_FIELD "progress_right_border"
#define PROGRESS_NAME_COMPLETED_FIELD "progress_completed_cell"
#define PROGRESS_NAME_UNCOMPLETED_FIELD "progress_uncompleted_cell"
#define PROGRESS_NAME_CURRENT_FIELD "progress_current_cell"

#define FAIL_EXIT (-1)

struct bar_config_fields {
    char* left_border_field;
    char* right_border_field;
    char* completed_cell_field;
    char* uncompleted_cell_field;
    char* current_cell_field;
};

char* get_field_string_data(const config_t* config, const char* field) {
    const char* buffer;
    if (!config_lookup_string(config, field, &buffer)) {
        fprintf(stderr, "No found `%s` field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }

    char* string_outside_conf_area = (char*) malloc(strlen(buffer));
    strcpy(string_outside_conf_area, buffer);
    return string_outside_conf_area;
}

void get_field_integer_data(const config_t* config, int* result_storage, const char* field) {
    if (!config_lookup_int(config, field, result_storage)) {
        fprintf(stderr, "No found `%s` field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }
}

struct bar_settings bar_configure(const config_t* config, struct bar_config_fields fields) {
    int bar_len;
    get_field_integer_data(config, &bar_len, PROGRESS_NAME_LEN_FIELD);

    const char* left_border;
    const char* right_border;
    const char* fill;
    const char* empty;
    const char* current;

    left_border = get_field_string_data(config, fields.left_border_field);
    right_border = get_field_string_data(config, fields.right_border_field);
    fill = get_field_string_data(config, fields.completed_cell_field);
    empty = get_field_string_data(config, fields.uncompleted_cell_field);
    current = get_field_string_data(config, fields.current_cell_field);

    // TODO Check by uncompleted_cell_field string
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
    struct bar_config_fields fields = {
            PROGRESS_NAME_LEFT_BORDER_FIELD,
            PROGRESS_NAME_RIGHT_BORDER_FIELD,
            PROGRESS_NAME_COMPLETED_FIELD,
            PROGRESS_NAME_UNCOMPLETED_FIELD,
            PROGRESS_NAME_CURRENT_FIELD
    };

    struct bar_settings bar_sett = bar_configure(config, fields);
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
