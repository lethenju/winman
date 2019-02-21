#include "winman_types.h"
#include "../termlib/termlib.h"
#include "../termlib/screen.h"
#include <stdlib.h>
winman_context* winman_init(void (*init_func)(winman_context*))
{
    winman_context* ctx =  (winman_context*) malloc(sizeof(winman_context));
    ctx->termlib_ctx = termlib_init2();
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
    winman_window* win = ctx->window_list;
    //getting to last window
    while (win != NULL)
        win = win->next;
    ctx->window_list = (winman_window*) malloc(sizeof(winman_window));

    win->posX = posX;
    win->posY = posY;
    win->width = width;
    win->height = height;
}
void del_window(winman_context* ctx, winman_window* win)
{
    // TODO IMPLEMENT
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
                                                        win->posY + line->B->posX, win->posY + line->B->posY, line->rep);
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
    // TODO IMPLEMENT
}
void del_widget_from_win(widget* wid, winman_window* win)
{
    // TODO IMPLEMENT
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

void move_window(winman_window* win, int newPosX, int newPosY)
{
    // TODO IMPLEMENT
}