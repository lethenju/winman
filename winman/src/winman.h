/**
 * winman version 0.1 (c) Julien LE THENO
 * (c) MIT LICENSE
 */
#ifndef WINMAN_H
#define WINMAN_H
/** Winman is built on top of termlib, which provides some useful building blocks.
 */
#include "../../termlib/src/termlib/termlib.h"
/** In order to understand the internals, begin with winman_types
 */
#include "winman_types.h"

/** Initializes the winman module. 
 *  @returns a ptr to the new winman_context 
 */
winman_context* winman_init();

/** Creates a window
 *  @param ctx   : the winman context
 *  @param posX  : the X coordinate of the top left position of the new window
 *  @param posY  : the Y coordinate of the top left position of the new window
 *  @param width : the width of the new window
 *  @param height: the height of the new window
 */
void add_window(winman_context* ctx, int posX, int posY, int width, int height);

/** Deletes a window
 *  @param ctx   : the winman context
 *  @param win   : the window to delete
 */
void del_window(winman_context* ctx, winman_window* win);

/** Display the windows. Cycle through the windows to display them all at once.
 *  @param ctx   : the winman context
 */
void display_windows(winman_context* ctx);

/** Adds a widget to a window
 *  @param wid   : the widget to add
 *  @param win   : the window in which the widget will be added
 */
void add_widget_to_win(widget* wid, winman_window* win);

/** Deletes a widget from a window
 *  @param wid   : the widget to delete
 *  @param win   : the window in which the widget will be delete
 */
void del_widget_from_win(widget* wid, winman_window* win);

/** Creates a 'dot' widget
 *  @param posX   : the X position of the dot, relative to the window
 *  @param posY   : the Y position of the dot, relative to the window
 *  @param rep    : the character representation of the dot, will be displayed on screen
 *  @return the widget_dot created
 */
widget_dot* create_widget_dot(int posX, int posY, char rep);


/** Creates a 'line' widget
 *  @param posX   : the X position of the first point, relative to the window
 *  @param posY   : the Y position of the second point, relative to the window
 *  @param rep    : the character representation of the line, will be displayed on screen
 *  @return the widget_line created
 */
widget_line* create_widget_line(int posX, int posY, int posX2, int posY2, char rep);


/** Creates a 'text' widget
 *  @param posX   : the X position of the beginning of text, relative to the window
 *  @param posY   : the Y position of the beginning of text, relative to the window
 *  @param text   : the text to be displayed
 *  @return the widget_text created
 */
widget_text* create_widget_text(int posX, int posY, char* text);


/** Creates a generic widget from a specific widget
 *  @param type        : the type of the widget (see widget_type_enum)
 *  @param widget_data : the specific widget (widget_dot, widget_line or else..)
 *  @return the widget created
 */
widget* create_widget(widget_type_enum type, void* widget_data);

/** Deletes a widget
 *  @param wid         : the widget to be deleted
 */
void del_widget(widget* wid);

/** moves a window to a new location
 *  @param win     : the window to move
 *  @param newPosX : the new X coordinate of the top left corner of the window
 *  @param newPosY : the new Y coordinate of the top left corner of the window
 */
void move_window(winman_window* win, int newPosX, int newPosY);

/** Returns the last window (in other words the currently selected one)
 *  @param ctx  : the context
 *  @return the last window
 */
winman_window* get_last_window(winman_context* ctx);

/** Shifts the order of the currently displayed windows. The last becomes first, the first second etc..
 * @param ctx : the context
 */
void shift_window_layer(winman_context* ctx);
#endif
