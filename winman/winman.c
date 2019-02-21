#include "winman_types.h"
#include "../termlib/termlib.h"
#include "../termlib/screen.h"
#include <stdlib.h>
winman_window* get_last_window(winman_context* ctx) ;
winman_context* winman_init(void (*init_func)(winman_context*))
{
    winman_context* ctx =  (winman_context*) malloc(sizeof(winman_context));
    ctx->termlib_ctx = termlib_init2();
    (*init_func)(ctx);
    return ctx;
}

void winman_event_loop(winman_context *ctx, void(*event_loop)(winman_context*))
{
    (*event_loop)(ctx);
    system("clear");
    ctx->termlib_ctx->exit = 1;

}

void add_window(winman_context* ctx, int posX, int posY, int width, int height) 
{
    winman_window* win;
    if (ctx->window_list == NULL) 
    {
        // first window
        ctx->window_list = malloc(sizeof(winman_window));
        win = ctx->window_list;
    } else {
        win = ctx->window_list;
        //getting to last window
        while (win->next != NULL)
            win = win->next;
        win->next = (winman_window*) malloc(sizeof(winman_window));
        win = win->next;
    }

    win->posX = posX;
    win->posY = posY;
    win->width = width;
    win->height = height;
}
void del_last_window(winman_context* ctx)
{
    winman_window *win = ctx->window_list;
    winman_window *last = get_last_window(ctx);
    while (win->next != last)
        win = win->next;
    win->next = NULL;
    free(last);
}
void display_windows(winman_context* ctx)
{
    winman_window* win = ctx->window_list;
    //getting to last window
    while (win != NULL)
    {
        fill_rectangle(ctx->termlib_ctx->screen, win->posX, win->posY, win->width, win->height, ' ');
        draw_rectangle(ctx->termlib_ctx->screen, win->posX, win->posY, win->width, win->height, '*');
        widget* wid = win->widget_list;
        while (wid != NULL) {
            switch (wid->type) 
            {
                case DOT:;
                    widget_dot* dot = (widget_dot*) wid->widget_data;
                    set_pixel(ctx->termlib_ctx->screen, win->posX+ dot->posX, win->posY + dot->posY, dot->rep);
                    break;
                case LINE:;
                    widget_line* line = (widget_line*) wid->widget_data;
                    draw_line(ctx->termlib_ctx->screen, win->posX + line->A->posX, win->posY + line->A->posY,
                                                        win->posX + line->B->posX, win->posY + line->B->posY, line->rep);
                    break;
                case TEXT:;
                    widget_text* text = (widget_text*) wid->widget_data;
                    write_text(ctx->termlib_ctx->screen, win->posX + text->position->posX, win->posY + text->position->posY, text->text);
                    break;
                case RECTANGLE:;
                    widget_rectangle* rect = (widget_rectangle*) wid->widget_data;
                    if (rect->filled) 
                    {
                        fill_rectangle(ctx->termlib_ctx->screen, win->posX + rect->top_left_corner->posX, win->posY + rect->top_left_corner->posY,
                                                             win->posX + rect->bottom_right_corner->posX, win->posY + rect->bottom_right_corner->posY,rect->rep );
                    } else {
                        draw_rectangle(ctx->termlib_ctx->screen, win->posX + rect->top_left_corner->posX, win->posY + rect->top_left_corner->posY,
                                                             win->posX + rect->bottom_right_corner->posX, win->posY + rect->bottom_right_corner->posY,rect->rep );
                    }
                    break;
                case CIRCLE:;
                    widget_circle* circ = (widget_circle*) wid->widget_data;
                    if (circ->filled) 
                    {
                        fill_circle(ctx->termlib_ctx->screen, win->posX + circ->center->posX, win->posY + circ->center->posY,
                                                             circ->radius, rect->rep );
                    } else {
                        draw_circle(ctx->termlib_ctx->screen, win->posX + circ->center->posX, win->posY + circ->center->posY,
                                                             circ->radius, rect->rep );
                    }
                    break;
            }
            wid = wid->next;
        }

        win = win->next;
    }
    
}

void add_widget_to_win(widget* wid, winman_window* win)
{
    if (win->widget_list == NULL) 
    {
        // first widget
        win->widget_list = wid;
    } else {
        widget* widg = win->widget_list;
        //getting to last window
        while (widg->next != NULL)
            widg = widg->next;
        widg->next = wid;
    }
}
void del_widget_from_win(widget* wid, winman_window* win)
{
    widget* widg = win->widget_list;
    while (wid != widg && widg->next != NULL)
        widg = widg->next;
    if (wid == widg) 
    {
        // TODO put the parent's child on the child of wid, then free wid
    }
}

 
widget_dot* create_widget_dot(int posX, int posY, char rep)
{
    widget_dot* widget_data = malloc(sizeof(widget_dot));
    widget_data->posX = posX;
    widget_data->posY = posY;
    widget_data->rep = rep;
    return widget_data;
}

widget_line* create_widget_line(int posX, int posY, int posX2, int posY2, char rep)
{
    widget_line* widget_data = malloc(sizeof(widget_line));
    widget_data->A = create_widget_dot(posX, posY, rep);
    widget_data->B = create_widget_dot(posX2, posY2, rep);
    widget_data->rep = rep;
    return widget_data;
}

widget* create_widget(widget_type_enum type, void* widget_data) 
{
    widget* wid = malloc(sizeof(widget));
    wid->widget_data = widget_data;
    wid->type = type;
    return wid;
}

int get_number_windows(winman_context* ctx)
{
    if (ctx->window_list == NULL) 
    {
        return 0;
    } 
    winman_window* win = ctx->window_list;
    int count = 0;
    while (win->next != NULL) {
        win = win->next;
        count++;
    }
    return count;
}

winman_window* get_last_window(winman_context* ctx) 
{
    if (ctx->window_list == NULL) 
    {
        return NULL;
    } 
    winman_window* win = ctx->window_list;
    while (win->next != NULL)
        win = win->next;
    return win;

}


void shift_window_layer(winman_context* ctx) 
{
    int nb_windows = get_number_windows(ctx);
    int i;
    winman_window* win = get_last_window(ctx);
    win->next = ctx->window_list;
    ctx->window_list = win;
    winman_window* close = ctx->window_list;
    for (i=0; i<nb_windows; i++)
        close = close->next; 
    close->next = NULL;        
}
