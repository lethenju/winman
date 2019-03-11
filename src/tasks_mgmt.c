#include "tasks_mgmt.h"
#include <string.h>
#include "screen.h"
#include <stdlib.h>
#include <stdio.h>

void add_input_task(winman_window* win, void (*task_function))
{
    win->input_manager = task_function;
}

