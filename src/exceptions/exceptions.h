#ifndef POMODORO_EXCEPTIONS_H
#define POMODORO_EXCEPTIONS_H

void fatal_exit(char* message, const char* func_name, int line_number);

void exit_with_code(int code);

#endif //POMODORO_EXCEPTIONS_H
