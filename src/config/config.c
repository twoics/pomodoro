#include "config.h"
#include "../../lib/libconfig/lib/libconfig.h"
#include "../exceptions/exceptions.h"

#define BAR_LEN_FIELD "bar_len"
#define LEFT_BORDER_FIELD "left_border"
#define RIGHT_BORDER_FIELD "right_border"
#define COMPLETED_CELL_FIELD "fill"
#define EMPTY_CELL_FIELD "empty"
#define CURRENT_CELL_FIELD "current"

#define FAIL_EXIT (-1)

void get_string_field(const config_t* config, const char** result_storage, const char* field) {
    if (!config_lookup_string(config, field, result_storage)) {
        fprintf(stderr, "No found %s field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }
}

void get_integer_field(const config_t* config, int* result_storage, const char* field) {
    if (!config_lookup_int(config, field, result_storage)) {
        fprintf(stderr, "No found %s field in configuration\n", field);
        exit_with_code(FAIL_EXIT);
    }
}

struct bar_settings bar_configure(const config_t* config) {
    int bar_len;
    const char* left_border;
    const char* right_border;
    const char* fill;
    const char* empty;
    const char* current;

    get_integer_field(config, &bar_len, BAR_LEN_FIELD);
    get_string_field(config, &left_border, LEFT_BORDER_FIELD);
    get_string_field(config, &right_border, RIGHT_BORDER_FIELD);
    get_string_field(config, &fill, COMPLETED_CELL_FIELD);
    get_string_field(config, &empty, EMPTY_CELL_FIELD);
    get_string_field(config, &current, CURRENT_CELL_FIELD);

    struct bar_settings bar_sett = {
            bar_len, left_border, right_border, fill, empty, current
    };

    return bar_sett;
}

struct configuration configure(char* file_path) {
    config_t cfg;
    config_setting_t* setting;
    const char* str;

    config_init(&cfg);

    if (!config_read_file(&cfg, file_path)) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        exit_with_code(FAIL_EXIT);
    }
    struct bar_settings bar_sett = bar_configure(&cfg);


}
