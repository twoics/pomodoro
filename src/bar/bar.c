#include "bar.h"
#include <malloc.h>
#include <errno.h>

#define MAX_PERCENT 100
#define LEFT_BOARD_INDEX 0
#define CURRENT_CELL_LEN 1

#define FAIL_STATUS (-1)
#define SUCCESS_STATUS 0

int count_filled_cells(int percentage, int bar_len) {
    if (percentage > MAX_PERCENT) {
        return FAIL_STATUS;
    }

    if (bar_len <= 0) {
        return FAIL_STATUS;
    }

    int filled_cells = bar_len * percentage / MAX_PERCENT;
    return filled_cells;
}

size_t bar_byte_size(int count_filled, struct bar_settings settings) {
    size_t current_cell_size = sizeof(char*);
    size_t fill_cells_size = count_filled * sizeof(char*);
    size_t empty_cells_size = (settings.bar_len - count_filled - CURRENT_CELL_LEN) * sizeof(char*);

    size_t borders_size = 0;
    if (settings.right_border != NULL) {
        borders_size += sizeof(char*);
    }
    if (settings.left_border != NULL) {
        borders_size += sizeof(char*);
    }

    size_t bar_size = fill_cells_size + current_cell_size + empty_cells_size + borders_size;
    return bar_size;
}

int fill_cells(const char** bar, int bar_len, int start_index, int count, const char* const cell) {
    int end_index = start_index + count - 1;

    // Index out of range
    if ((start_index < 0 | end_index < 0) |
        (start_index > end_index) |
        (end_index > bar_len)) {
        return FAIL_STATUS;
    }

    for (int i = start_index; i <= end_index; ++i) {
        bar[i] = cell;
    }

    return SUCCESS_STATUS;
}

void set_left_boarder(const char** bar, struct bar_settings settings) {
    if (settings.left_border != NULL) {
        bar[LEFT_BOARD_INDEX] = settings.left_border;
    }
}

int set_completed_cells(const char** bar, struct bar_settings settings, int count) {
    int start_index = 0;
    if (settings.left_border != NULL) {
        start_index = 1;
    }

    int status = SUCCESS_STATUS;
    if (count != 0) {
        status = fill_cells(bar, settings.bar_len, start_index, count, settings.fill);
    }
    return status;
}

int set_current_cell(const char** bar, struct bar_settings settings, int count_completed) {
    if (count_completed < 0) {
        return FAIL_STATUS;
    }

    int index = count_completed;
    if (settings.left_border != NULL) {
        index++;
    }

    const char* current_cell = settings.current;
    if (current_cell == NULL) {
        current_cell = settings.empty;
    }

    if (count_completed != settings.bar_len) {
        bar[index] = current_cell;
    }

    return SUCCESS_STATUS;
}

int set_empty_cells(const char** bar, struct bar_settings settings, int count_completed) {
    if (count_completed < 0) {
        return FAIL_STATUS;
    }

    int start_index = count_completed + 1;
    int max_start_bias = 0;
    if (settings.left_border != NULL) {
        start_index++;
        max_start_bias = 1;
    }

    int count = settings.bar_len - count_completed - 1;
    int max_start_index = settings.bar_len + max_start_bias;

    int status = SUCCESS_STATUS;
    if (start_index < max_start_index) {
        status = fill_cells(bar, settings.bar_len, start_index, count, settings.empty);
    }
    return status;
}

void set_right_boarder(const char** bar, struct bar_settings settings) {
    int index = settings.bar_len;
    if (settings.left_border != NULL) {
        index++;
    }

    if (settings.right_border != NULL) {
        bar[index] = settings.right_border;
    }
}

const char** build(int completed_percentage, struct bar_settings settings) {
    if (completed_percentage < 0) {
        errno=EINVAL;
        return NULL;
    }

    if (settings.fill == NULL | settings.empty == NULL) {
        errno=EINVAL;
        return NULL;
    }

    int filled_cells = count_filled_cells(completed_percentage, settings.bar_len);

    if (filled_cells == FAIL_STATUS) {
        errno = EINVAL;
        return NULL;
    }

    size_t bar_size = bar_byte_size(filled_cells, settings);
    const char** progress_bar = (const char**) malloc(bar_size);
    if (progress_bar == NULL) {
        errno = ENOEXEC;
        return NULL;
    }

    int build_status = SUCCESS_STATUS;

    set_left_boarder(progress_bar, settings);

    build_status = set_completed_cells(progress_bar, settings, filled_cells);
    if (build_status == FAIL_STATUS) {
        errno = ENOEXEC;
        return NULL;
    }

    build_status = set_current_cell(progress_bar, settings, filled_cells);
    if (build_status == FAIL_STATUS) {
        errno = ENOEXEC;
        return NULL;
    }

    build_status = set_empty_cells(progress_bar, settings, filled_cells);
    if (build_status == FAIL_STATUS) {
        errno = ENOEXEC;
        return NULL;
    }

    set_right_boarder(progress_bar, settings);

    return progress_bar;
}

