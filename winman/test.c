// TEST.C for testing winman

#include "src/winman.h"
#include "src/winman_types.h"
#include "../termlib/src/termlib/screen.h"
#include "../termlib/src/termlib/termlib.h"


void* init(winman_context* ctx){
    add_window(ctx, 10, 10, 50, 50);
    add_window(ctx, 20, 20, 50, 50);
    add_window(ctx, 30, 5, 50, 20);
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"FENETRE 1")), ctx->window_list);
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"FENETRE 2")), ctx->window_list->next);
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"FENETRE 3")), ctx->window_list->next->next);
    add_widget_to_win(create_widget(LINE, (void*) create_widget_line(10,10,40,45,'o')), ctx->window_list->next);
}

void* event_loop(winman_context* ctx) {
    char c;
    
    fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ');
    display_windows(ctx);    
    
    while((c=getchar())!= '.') {
        winman_window *win= get_last_window(ctx);
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
                

        }

        fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ');
        display_windows(ctx);    
    

    }
}


// DO NOT TOUCH MAIN
int main(int argc, char *argv[])
{
    winman_context* ctx = winman_init((void*)init);
    winman_event_loop(ctx, (void*)event_loop);
    return 0;
}
