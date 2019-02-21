#ifndef WINMAN_H
#define WINMAN_H
#include "../termlib/termlib.h"

winman_context* winman_init();

void add_window(winman_context* ctx, int posX, int posY, int width, int height);

void del_window(winman_context* ctx, winman_window* win);

void display_windows(winman_context* ctx);

// PRIV void display_window(winman_window* win, termlib_screen* screen);

// PRIV void display_widget(winman_window* win, termlib_screen* screen, widget* wid);

void add_widget_to_win(widget* wid, winman_window* win);

void del_widget_from_win(widget* wid, winman_window* win);

widget* create_widget(widget_type_enum type);

void move_window(winman_window* win, int newPosX, int newPosY);

#endif