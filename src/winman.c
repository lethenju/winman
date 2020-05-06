#include "winman_types.h"
#include "termlib.h"
#include "log_system.h"
#include "resman.h"
#include <string.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 1024

// prevents CWE-126, to protect not \0-terminated strings 
size_t safe_strlen(const char *str, size_t max_len)
{
    const char * end = (const char *)memchr(str, '\0', max_len);
    if (end == NULL)
        return max_len;
    else
        return end - str;
}

winman_window* get_last_window(winman_context* ctx) ;
winman_context* winman_init(void (*init_func)(winman_context*))
{
    DEBUG_TRACE("winman_init");
    winman_context* ctx = resman_alloc("winman_context", sizeof(winman_context));
    ctx->termlib_ctx = termlib_init2();
    (*init_func)(ctx);
    DEBUG_TRACE("winman_init done");
    return ctx;
}

void winman_event_loop(winman_context *ctx, void(*event_loop)(winman_context*))
{
    DEBUG_TRACE("winman event loop");
    (*event_loop)(ctx);
    system("clear");
    ctx->termlib_ctx->exit = 1;
    DEBUG_TRACE("exiting");

}

winman_window* add_window(winman_context* ctx, int posX, int posY, int width, int height) 
{
    INFO_TRACE("adding windows");
    winman_window* win;
    if (ctx->window_list == NULL) 
    {
        // first window
        ctx->window_list = resman_alloc("first window", sizeof(winman_window));
        win = ctx->window_list;
        win->next = NULL;
    } else {
        win = ctx->window_list;
        //getting to last window
        while (win->next != NULL) {
            win = win->next;
        }
        win->next = resman_alloc("winman window", sizeof(winman_window));
        win = win->next;
        win->next = NULL;
    }

    win->posX = posX;
    win->posY = posY;
    win->width = width;
    win->height = height;
    INFO_TRACE("window added");
    return win;
}
void del_last_window(winman_context* ctx)
{
    winman_window *win = ctx->window_list;
    winman_window *last = get_last_window(ctx);
    if (last == NULL) return; // no windows
    while (win->next != last)
        win = win->next;
    win->next = NULL;
    resman_free(last);
}
void display_windows(winman_context* ctx)
{
    INFO_TRACE("display windows");
    winman_window* win = ctx->window_list;

    //getting to last window
    while (win != NULL)
    {
        rectangle_filter(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, 
                                                     ctx->termlib_ctx->screen->height, 0);
        rectangle_filter(ctx->termlib_ctx->screen, win->posX, win->posY, 
                                                   win->width+1, 
                                                   win->height+1, 1);

        fill_rectangle(ctx->termlib_ctx->screen, win->posX, win->posY, win->width, win->height, ' ', FG_DEFAULT, BG_DARK_GRAY);
        if (win->next != NULL)
            draw_rectangle(ctx->termlib_ctx->screen, win->posX, win->posY, win->width, win->height, '*', FG_DEFAULT, BG_DARK_GRAY);
        else 
            draw_rectangle(ctx->termlib_ctx->screen, win->posX, win->posY, win->width, win->height, '*', FG_DEFAULT, BG_LIGHT_GRAY);

        widget* wid = win->widget_list;
        while (wid != NULL) {
            switch (wid->type) 
            {
                case DOT:;
                    widget_dot* dot = (widget_dot*) wid->widget_data;
                    set_pixel(ctx->termlib_ctx->screen, win->posX+ dot->posX, win->posY + dot->posY, dot->rep, FG_DEFAULT, BG_DEFAULT);
                    break;
                case LINE:;
                    widget_line* line = (widget_line*) wid->widget_data;
                    draw_line(ctx->termlib_ctx->screen, win->posX + line->A->posX, win->posY + line->A->posY,
                                                        win->posX + line->B->posX, win->posY + line->B->posY, line->rep, FG_DEFAULT, BG_DEFAULT);
                    break;
                case TEXT:;
                    widget_text* text = (widget_text*) wid->widget_data;
                    if (win->width < text->position->posX + safe_strlen(text->text, MAX_STRING_LENGTH)) // TODO general managing of window edges
                    {
                        WARNING_TRACE("Text box too large");
                        int available_size =  win->width - text->position->posX;
                        if (available_size <0) 
                        {
                            ERROR_TRACE("Text outbound!");
                            break;
                        }
                        text->text[available_size] = '\0'; // cutting the text
                    }
                    write_text(ctx->termlib_ctx->screen, win->posX + text->position->posX, win->posY + text->position->posY, text->text, FG_DEFAULT, BG_DEFAULT);
                    break;
                case RECTANGLE:;
                    widget_rectangle* rect = (widget_rectangle*) wid->widget_data;
                    if (rect->filled) 
                    {
                        fill_rectangle(ctx->termlib_ctx->screen, win->posX + rect->top_left_corner->posX, win->posY + rect->top_left_corner->posY,
                                                             win->posX + rect->bottom_right_corner->posX, win->posY + rect->bottom_right_corner->posY,rect->rep, FG_DEFAULT, BG_DEFAULT);
                    } else {
                        draw_rectangle(ctx->termlib_ctx->screen, win->posX + rect->top_left_corner->posX, win->posY + rect->top_left_corner->posY,
                                                             win->posX + rect->bottom_right_corner->posX, win->posY + rect->bottom_right_corner->posY,rect->rep, FG_DEFAULT, BG_DEFAULT);
                    }
                    break;
                case CIRCLE:;
                    widget_circle* circ = (widget_circle*) wid->widget_data;
                    if (circ->filled) 
                    {
                        fill_circle(ctx->termlib_ctx->screen, win->posX + circ->center->posX, win->posY + circ->center->posY,
                                                             circ->radius, circ->rep, FG_DEFAULT, BG_DEFAULT);
                    } else {
                        draw_circle(ctx->termlib_ctx->screen, win->posX + circ->center->posX, win->posY + circ->center->posY,
                                                             circ->radius, circ->rep, FG_DEFAULT, BG_DEFAULT);
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
