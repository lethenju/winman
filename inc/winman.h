/**
 * winman version 0.1 (c) Julien LE THENO
 * (c) MIT LICENSE
 */
#ifndef WINMAN_H
#define WINMAN_H
/** Winman is built on top of termlib, which provides some useful building blocks.
 */
#include "termlib.h"
/** In order to understand the internals, begin with winman_types
 */
#include "winman_types.h"

/** Initializes the winman module. 
 *  @returns a ptr to the new winman_context 
 */
winman_context* winman_init();

/** Launches the winman event loop given in parameters
 */ 
void winman_event_loop(winman_context *ctx, void(*event_loop)(winman_context*));


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

/** Deletes the last window (in other words the currently selected one)
 *  @param ctx : the context
 */
void del_last_window(winman_context* ctx);

/** Shifts the order of the currently displayed windows. The last becomes first, the first second etc..
 * @param ctx : the context
 */
void shift_window_layer(winman_context* ctx);
#endif
