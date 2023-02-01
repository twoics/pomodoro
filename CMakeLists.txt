cmake_minimum_required(VERSION 3.24)
project(pomodoro C)

set(CMAKE_C_STANDARD 99)

add_executable(pomodoro src/main.c src/timer/timer.h src/timer/timer.c src/progress_bar/progress_bar.c src/progress_bar/progress_bar.h src/cli_cleaner/cli_cleaner.h src/cli_cleaner/cli_cleaner.c src/exceptions/exceptions.h src/exceptions/exceptions.c src/bar/bar.c src/session_bar/session_bar.c src/session_bar/session_bar.h)
