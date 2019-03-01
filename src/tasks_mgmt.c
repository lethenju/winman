#include "tasks_mgmt.h"
#include <string.h>
#include "../termlib/src/screen.h"
#include <stdlib.h>

void* thread_task_text_input(void* tti)
{
    task_text_input* wid = (task_text_input*) tti;
    char c;
    while ((c = getchar()) != '.') // TODO proper centralized key inputs
    {
        char* new_text = malloc(sizeof(wid->text_box->text)+1);
        strcpy(new_text, wid->text_box->text);
        new_text[strlen(wid->text_box->text)] = c;
        wid->text_box->text = new_text;
        screen_frame_ready(wid->link_to_context->termlib_ctx->screen);
    }
}

task_text_input* add_task_text_input(widget_text* widget_text, winman_context* ctx)
{
    task_text_input* tti = malloc(sizeof(task_text_input));
    tti->text_box = widget_text;
    tti->link_to_context = ctx;
    pthread_create(&(tti->thread_input), NULL, thread_task_text_input, tti);
    return tti;
}

