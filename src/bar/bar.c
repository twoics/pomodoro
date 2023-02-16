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
//        fatal_exit("Percentage can't be > 100", __FUNCTION__, __LINE__);
    }

    if (bar_len <= 0) {
        return FAIL_STATUS;
//        fatal_exit("Bar len can't be < 0", __FUNCTION__, __LINE__);
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

int set_bar_cell(const char** bar, int index, const char* const cell) {
    if (index < 0) {
        return FAIL_STATUS;
//        fatal_exit("Index out of total bar range", __FUNCTION__, __LINE__);
    }

    bar[index] = cell;

    return SUCCESS_STATUS;
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
        int status = set_bar_cell(bar, i, cell);

        if (status == FAIL_STATUS) {
            return FAIL_STATUS;
        }
    }

    return SUCCESS_STATUS;
}

int set_left_boarder(const char** bar, struct bar_settings settings) {
    int status = SUCCESS_STATUS;
    if (settings.left_border != NULL) {
        status = set_bar_cell(bar, LEFT_BOARD_INDEX, settings.left_border);
    }
    return status;
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
    int index = count_completed;
    if (settings.left_border != NULL) {
        index++;
    }

    const char* current_cell = settings.current;
    if (current_cell == NULL) {
        current_cell = settings.empty;
    }

    int status = SUCCESS_STATUS;
    if (count_completed != settings.bar_len) {
        status = set_bar_cell(bar, index, current_cell);
    }

    return status;
}

int set_empty_cells(const char** bar, struct bar_settings settings, int count_completed) {
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

int set_right_boarder(const char** bar, struct bar_settings settings) {
    int index = settings.bar_len;
    if (settings.left_border != NULL) {
        index++;
    }

    int status = SUCCESS_STATUS;
    if (settings.right_border != NULL) {
        status = set_bar_cell(bar, index, settings.right_border);
    }
    return status;
}

const char** build(int completed_percentage, struct bar_settings settings) {
    if (settings.fill == NULL | settings.empty == NULL) {
        return NULL;
//        fatal_exit("Fill or empty cell can't be NULL", __FUNCTION__, __LINE__);
    }

    int filled_cells = count_filled_cells(completed_percentage, settings.bar_len);

    if (filled_cells == FAIL_STATUS) {
        return NULL;
    }

    size_t bar_size = bar_byte_size(filled_cells, settings);
    const char** progress_bar = (const char**) malloc(bar_size);
    if (progress_bar == NULL) {
        return NULL;
    }

    set_left_boarder(progress_bar, settings);
    set_completed_cells(progress_bar, settings, filled_cells);
    set_current_cell(progress_bar, settings, filled_cells);
    set_empty_cells(progress_bar, settings, filled_cells);
    set_right_boarder(progress_bar, settings);

    return progress_bar;
}

