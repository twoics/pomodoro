#include <malloc.h>
#include <string.h>
#include "config.h"
#include "../../lib/libconfig/lib/libconfig.h"
#include "../exceptions/exceptions.h"

#define PROGRESS_LEN_FIELD "progress_bar_len"
#define PROGRESS_LEFT_BORDER_FIELD "progress_left_border"
#define PROGRESS_RIGHT_BORDER_FIELD "progress_right_border"
#define PROGRESS_COMPLETED_FIELD "progress_completed_cell"
#define PROGRESS_UNCOMPLETED_FIELD "progress_uncompleted_cell"
#define PROGRESS_CURRENT_FIELD "progress_current_cell"
#define MESSAGE_BEFORE_PROGRESS_BAR "message_before_progress_bar"

#define SESSION_LEFT_BORDER_FIELD "session_left_border"
#define SESSION_RIGHT_BORDER_FIELD "session_right_border"
#define SESSION_COMPLETED_FIELD "session_completed_cell"
#define SESSION_UNCOMPLETED_FIELD "session_uncompleted_cell"
#define SESSION_CURRENT_FIELD "session_current_cell"
#define MESSAGE_BEFORE_SESSION_BAR "message_before_session_bar"

#define EMPTY_STRING ""
#define FAIL_EXIT (-1)
#define BAR_ADDITIONAL_PARAMETERS 4
#define STRING_EQUALS 0

struct bar_config_fields {
    char* left_border_field;
    char* right_border_field;
    char* completed_cell_field;
    char* uncompleted_cell_field;
    char* current_cell_field;
    char* message_field;
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

int get_field_integer_data(const config_t* config, const char* field) {
    int result_storage;
    if (!config_lookup_int(config, field, &result_storage)) {
        fprintf(stderr, "No found `%s` field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }
    return result_storage;
}

struct bar_settings bar_configure(const config_t* config, struct bar_config_fields fields, int bar_len) {
    const char* left_border;
    const char* right_border;
    const char* current;
    const char* fill;
    const char* empty;
    const char* message_before_bar;

    left_border = get_field_string_data(config, fields.left_border_field);
    right_border = get_field_string_data(config, fields.right_border_field);
    fill = get_field_string_data(config, fields.completed_cell_field);
    empty = get_field_string_data(config, fields.uncompleted_cell_field);
    current = get_field_string_data(config, fields.current_cell_field);
    message_before_bar = get_field_string_data(config, fields.message_field);

    if ((strcmp(empty, EMPTY_STRING) == STRING_EQUALS)
        | (strcmp(fill, EMPTY_STRING) == STRING_EQUALS)) {
        fprintf(stderr, "FILL or EMPTY cell can't be empty\n");
        exit_with_code(FAIL_EXIT);
    }

    const char** additional_parameters[BAR_ADDITIONAL_PARAMETERS] = {
            &left_border, &right_border, &current, &message_before_bar};

    for (int i = 0; i < BAR_ADDITIONAL_PARAMETERS; ++i) {
        if (strcmp(*additional_parameters[i], EMPTY_STRING) == STRING_EQUALS) {
            *additional_parameters[i] = NULL;
        }
    }

    struct bar_settings bar_sett = {
            bar_len, left_border, right_border, fill, empty, current, message_before_bar
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

struct progress_bar_settings configure_progress_bar(char* file_path) {
    config_t cfg = init_config_file(file_path);

    int bar_len = get_field_integer_data(&cfg, PROGRESS_LEN_FIELD);
    if (bar_len <= 0) {
        config_destroy(&cfg);
        fprintf(stderr, "Bar len can't be less or equal than zero\n");
        exit_with_code(FAIL_EXIT);
    }

    struct bar_config_fields fields = {
            PROGRESS_LEFT_BORDER_FIELD,
            PROGRESS_RIGHT_BORDER_FIELD,
            PROGRESS_COMPLETED_FIELD,
            PROGRESS_UNCOMPLETED_FIELD,
            PROGRESS_CURRENT_FIELD,
            MESSAGE_BEFORE_PROGRESS_BAR,
    };

    struct bar_settings bar_sett = bar_configure(&cfg, fields, bar_len);
    struct progress_bar_settings progress_sett = {
            bar_sett
    };

    config_destroy(&cfg);
    return progress_sett;
}

struct session_bar_setting configure_session_bar(char* file_path, int bar_len) {
    if (bar_len < 0) {
        fprintf(stderr, "Bar len can't be less or equal than zero\n");
        exit_with_code(FAIL_EXIT);
    }

    config_t cfg = init_config_file(file_path);
    struct bar_config_fields fields = {
            SESSION_LEFT_BORDER_FIELD,
            SESSION_RIGHT_BORDER_FIELD,
            SESSION_COMPLETED_FIELD,
            SESSION_UNCOMPLETED_FIELD,
            SESSION_CURRENT_FIELD,
            MESSAGE_BEFORE_SESSION_BAR,
    };

    struct bar_settings bar_sett = bar_configure(&cfg, fields, bar_len);
    struct session_bar_setting session_sett = {
            bar_sett
    };

    config_destroy(&cfg);
    return session_sett;
}
