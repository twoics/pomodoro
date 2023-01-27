#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../exceptions/exceptions.h"

#define MAX_PERCENT 100
#define BORDERS_COUNT 2
#define LEFT_BOARD_INDEX 0
#define RIGHT_BORDER_BIAS 1
#define START_BAR_INDEX 1
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

size_t bar_byte_size(int count_filled, int bar_len) {
    size_t current_cell_size = sizeof(char*);
    size_t fill_cells_size = count_filled * sizeof(char*);
    size_t empty_cells_size = (bar_len - count_filled - CURRENT_CELL_LEN) * sizeof(char*);
    size_t borders_size = BORDERS_COUNT * sizeof(char*);

    size_t bar_size = fill_cells_size + current_cell_size + empty_cells_size + borders_size;
    return bar_size;
}

void set_bar_cell(char** bar, int max_index, int index, char* cell) {
    if (index < 0 | index > max_index) {
        fatal_exit("Index out of total bar range", __FUNCTION__, __LINE__);
    }

    bar[index] = cell;
}

void fill_cells(char** bar, int bar_len, int start_index, int end_index, char* cell) {
    if (start_index <= LEFT_BOARD_INDEX | end_index <= LEFT_BOARD_INDEX) {
        fatal_exit("Start or end_index <= left board", __FUNCTION__, __LINE__);
    }
    if (start_index > end_index) {
        fatal_exit("Start index > End index", __FUNCTION__, __LINE__);
    }
    if (end_index > bar_len) {
        fatal_exit("End index > Bar len", __FUNCTION__, __LINE__);
    }

    for (int i = start_index; i <= end_index; ++i) {
        set_bar_cell(bar, end_index, i, cell);
    }
}

char** progress_build(int percentage, int bar_len, char* fill, char* empty, char* current) {
    if (fill == NULL | empty == NULL) {
        fatal_exit("Fill or empty cell can't be NULL", __FUNCTION__, __LINE__);
    }
    if (current == NULL) {
        current = empty;
    }

    int filled_cells = count_filled_cells(percentage, bar_len);
    size_t bar_size = bar_byte_size(filled_cells, bar_len);
    char** progress_bar = (char**) malloc(bar_size);

    const int right_board_index = bar_len + RIGHT_BORDER_BIAS;
    set_bar_cell(progress_bar, right_board_index, LEFT_BOARD_INDEX, "[");

    if (filled_cells != 0) {
        fill_cells(progress_bar, bar_len, START_BAR_INDEX, filled_cells, fill);
    }

    const int current_cell_index = filled_cells + 1;
    if (filled_cells != bar_len) {
        set_bar_cell(progress_bar, right_board_index, current_cell_index, current);
    }

    const int start_empty_cell_index = current_cell_index + 1;
    if (start_empty_cell_index <= bar_len) {
        fill_cells(progress_bar, bar_len, start_empty_cell_index, bar_len, empty);
    }

    set_bar_cell(progress_bar, right_board_index, right_board_index, "]");

    return progress_bar;
}


void draw_progress(int percentage, int bar_len, char* fill, char* empty, char* current) {
    char** bar = progress_build(percentage, bar_len, fill, empty, current);

    for (int i = 0; i < bar_len + BORDERS_COUNT; ++i) {
        printf("%s", bar[i]);
    }

    fflush(stdout);
    printf("\r");
    free(bar);
}