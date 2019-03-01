#ifndef TASKS_MGMGT_H
#define TASKS_MGMTT_H
#include "winman_types.h"
#include <pthread.h>

/** text input task data structure, to link to an actual text box
 */
typedef struct {
    widget_text *text_box;           // text box used to enter text
    pthread_t thread_input;          // thread input
    // DEBUG - TODO proper event redraw system
    winman_context* link_to_context; // to redraw the screen
} task_text_input;

task_text_input* add_task_text_input(widget_text* widget_text, winman_context* ctx);

#endif