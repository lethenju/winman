#ifndef WINMAN_H
#define WINMAN_H
#include "../termlib/termlib.h"
#include "winman_types.h"
winman_context* winman_init();

void add_window(winman_context* ctx, int posX, int posY, int width, int height);

void del_window(winman_context* ctx, winman_window* win);

void display_windows(winman_context* ctx);

void add_widget_to_win(widget* wid, winman_window* win);

void del_widget_from_win(widget* wid, winman_window* win);
 
widget_dot* create_widget_dot(int posX, int posY, char rep);

widget_line* create_widget_line(int posX, int posY, int posX2, int posY2, char rep);

widget* create_widget(widget_type_enum type, void* widget_data);

void del_widget(widget* wid);

void move_window(winman_window* win, int newPosX, int newPosY);

winman_window* get_last_window(winman_context* ctx);

void shift_window_layer(winman_context* ctx);
#endif