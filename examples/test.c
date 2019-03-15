// TEST.C for testing winman
#include "winman.h"
#include "widgets.h"
#include "winman_types.h"
#include "tasks_mgmt.h"
#include "screen.h"
#include "termlib.h"
#include "resman.h"
#include "log_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int MODE_INTRA_WINDOW = 0;

void task_of_changing_window_name(winman_window *win, char c)
{
    WARNING_TRACE("Char C = %d --- %c", c, c);
    widget_text *wid = win->widget_list->widget_data;
    if (c==127) // backspace
    {
        if (strlen(wid->text)>0)
            wid->text[strlen(wid->text) -1] = '\0';
    }
    else
    {
        char* new_text = malloc(sizeof(wid->text)+1);  
        strcpy(new_text, wid->text);
        new_text[strlen(wid->text)] = c;
        wid->text = new_text;
    }
}


void* init(winman_context* ctx){
    DEBUG_TRACE("init");
    add_window(ctx, 10, 10, 20, 20);
    add_window(ctx, 20, 20, 20, 25);
    add_window(ctx, 30, 5, 30, 20);
    widget *fenetre1_name = create_widget(TEXT, (void*) create_widget_text(2,2,"FENETRE 1"));
    add_widget_to_win(fenetre1_name, ctx->window_list);
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"FENETRE 2")), ctx->window_list->next);
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"FENETRE 3")), ctx->window_list->next->next);
    add_widget_to_win(create_widget(CIRCLE, (void*) create_widget_circle (5, 5, 10, '.')), ctx->window_list);
    DEBUG_TRACE("Adding input tasks");

    add_input_task(ctx->window_list,(void*) task_of_changing_window_name);
    add_input_task(ctx->window_list->next,(void*) task_of_changing_window_name);
    add_input_task(ctx->window_list->next->next,(void*) task_of_changing_window_name);
    fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ', FG_DEFAULT, BG_DEFAULT);
    display_windows(ctx);    
    screen_frame_ready(ctx->termlib_ctx->screen);
    DEBUG_TRACE("init done");

}

void* event_loop(winman_context* ctx) {
    char c;
    fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ',FG_DEFAULT, BG_DEFAULT);
    display_windows(ctx);    
    
    while((c=getchar())!= '.') {
        winman_window *win= get_last_window(ctx);
        if (win->input_manager != NULL && MODE_INTRA_WINDOW)
        {
            if (c == '0')
                MODE_INTRA_WINDOW = 0;
            else
                win->input_manager(win, c);
        } 
        else 
        {
            switch (c){
                case 'v':
                    // like alt tab
                    shift_window_layer(ctx);
                    break;
                case 'z':
                    // move up current window
                    win->posY--;
                    break;
                case 'q':
                    // move left current window
                    win->posX--;
                    break;
                case 's':
                    // move down current window
                    win->posY++;
                    break;
                case 'd':
                    // move right current window
                    win->posX++;
                    break;
                case 'c':
                    // create new window
                    add_window(ctx, 40,40,30,30);
                    break;
                case 'x':
                    // delete current window
                    del_last_window(ctx);
                    break;
                case '0':
                    // Change mode
                    MODE_INTRA_WINDOW = 1;
                    break;
            }
        }
        fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ', FG_DEFAULT, BG_DEFAULT);
        display_windows(ctx);    
        screen_frame_ready(ctx->termlib_ctx->screen);

    }
}




// DO NOT TOUCH MAIN
int main(int argc, char *argv[])
{
    resman_init();
    log_init();
    DEBUG_TRACE("2");
    winman_context* ctx = winman_init((void*)init);
    DEBUG_TRACE("3");
    winman_event_loop(ctx, (void*)event_loop);
    resman_end();
    return 0;
}
