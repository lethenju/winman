#include "winman_types.h"
#include "../termlib/termlib.h"

winman_context* winman_init()
{
    // TODO IMPLEMENT
}
void add_window(winman_context* ctx, int posX, int posY, int width, int height) 
{
    // TODO IMPLEMENT
}
void del_window(winman_context* ctx, winman_window* win)
{
    // TODO IMPLEMENT
}
void display_windows(winman_context* ctx)
{
    // TODO IMPLEMENT
}
void display_window(winman_window* win, termlib_screen* screen)
{
    // TODO IMPLEMENT
}
void display_widget(winman_window* win, termlib_screen* screen, widget* wid)
{
    // TODO IMPLEMENT
}
void add_widget_to_win(widget* wid, winman_window* win)
{
    // TODO IMPLEMENT
}
void del_widget_from_win(widget* wid, winman_window* win)
{
    // TODO IMPLEMENT
}
widget* create_widget(widget_type_enum type)
{
    // TODO IMPLEMENT
}
void move_window(winman_window* win, int newPosX, int newPosY)
{
    // TODO IMPLEMENT
}