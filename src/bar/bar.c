#include "bar.h"
#include <malloc.h>
#include "../exceptions/exceptions.h"

#define MAX_PERCENT 100
#define LEFT_BOARD_INDEX 0
#define CURRENT_CELL_LEN 1

int count_filled_cells(int percentage, int bar_len) {
    if (percentage > MAX_PERCENT) {
        fatal_exit("Percentage can't be > 100", __FUNCTION__, __LINE__);
    }
    if (bar_len <= 0) {
        fatal_exit("Bar len can't be < 0", __FUNCTION__, __LINE__);
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

void set_bar_cell(const char** bar, int index, const char* const cell) {
    if (index < 0) {
        fatal_exit("Index out of total bar range", __FUNCTION__, __LINE__);
    }

    bar[index] = cell;
}

void fill_cells(const char** bar, int bar_len, int start_index, int count, const char* const cell) {
    int end_index = start_index + count - 1;

    if (start_index < 0 | end_index < 0) {
        fatal_exit("Start or end_index can't be < 0", __FUNCTION__, __LINE__);
    }
    if (start_index > end_index) {
        printf("%d, %d, %s", start_index, end_index, cell);
        fatal_exit("Start index > End index", __FUNCTION__, __LINE__);
    }
    if (end_index > bar_len) {
        fatal_exit("End index > Bar len", __FUNCTION__, __LINE__);
    }

    for (int i = start_index; i <= end_index; ++i) {
        set_bar_cell(bar, i, cell);
    }
}

void set_left_boarder(const char** bar, struct bar_settings settings) {
    if (settings.left_border != NULL) {
        set_bar_cell(bar, LEFT_BOARD_INDEX, settings.left_border);
    }
}

void set_completed_cells(const char** bar, struct bar_settings settings, int count) {
    int start_index = 0;
    if (settings.left_border != NULL) {
        start_index = 1;
    }

    if (count != 0) {
        fill_cells(bar, settings.bar_len, start_index, count, settings.fill);
    }
}

void set_current_cell(const char** bar, struct bar_settings settings, int count_completed) {
    int index = count_completed;
    if (settings.left_border != NULL) {
        index++;
    }

    const char* current_cell = settings.current;
    if (current_cell == NULL) {
        current_cell = settings.empty;
    }

    if (count_completed != settings.bar_len) {
        set_bar_cell(bar, index, current_cell);
    }
}

void set_empty_cells(const char** bar, struct bar_settings settings, int count_completed) {
    int start_index = count_completed + 1;
    int max_start_bias = 0;
    if (settings.left_border != NULL) {
        start_index++;
        max_start_bias = 1;
    }

    int count = settings.bar_len - count_completed - 1;
    int max_start_index = settings.bar_len + max_start_bias;
    if (start_index < max_start_index) {
        fill_cells(bar, settings.bar_len, start_index, count, settings.empty);
    }
}

void set_right_boarder(const char** bar, struct bar_settings settings) {
    int index = settings.bar_len;
    if (settings.left_border != NULL) {
        index++;
    }

    if (settings.right_border != NULL) {
        set_bar_cell(bar, index, settings.right_border);
    }
}

const char** build(int completed_percentage, struct bar_settings settings) {
    if (settings.fill == NULL | settings.empty == NULL) {
        fatal_exit("Fill or empty cell can't be NULL", __FUNCTION__, __LINE__);
    }

    int filled_cells = count_filled_cells(completed_percentage, settings.bar_len);
    size_t bar_size = bar_byte_size(filled_cells, settings);
    const char** progress_bar = (const char**) malloc(bar_size);

    set_left_boarder(progress_bar, settings);
    set_completed_cells(progress_bar, settings, filled_cells);
    set_current_cell(progress_bar, settings, filled_cells);
    set_empty_cells(progress_bar, settings, filled_cells);
    set_right_boarder(progress_bar, settings);

    return progress_bar;
}

