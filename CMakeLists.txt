cmake_minimum_required(VERSION 3.24)
project(pomodoro C)

set(CMAKE_C_STANDARD 99)

add_executable(pomodoro src/main.c src/timer/timer.h src/timer/timer.c src/cli_cleaner/cli_cleaner.h src/cli_cleaner/cli_cleaner.c src/exceptions/exceptions.h src/exceptions/exceptions.c src/bar/bar.c src/config/config.c src/config/config.h src/bar/draw_bar.c src/bar/draw_bar.h)

target_link_libraries(pomodoro ${CMAKE_SOURCE_DIR}/lib/libconfig/build/out/libconfig.so)