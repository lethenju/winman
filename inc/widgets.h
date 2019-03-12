/**
 * winman version 0.1 (c) Julien LE THENO
 * (c) MIT LICENSE
 */
#ifndef WIDGETS_H
#define WIDGETS_H
/** In order to understand the internals, begin with winman_types
 */
#include "winman_types.h"

/** Creates a 'dot' widget
 *  @param posX   : the X position of the dot, relative to the window
 *  @param posY   : the Y position of the dot, relative to the window
 *  @param rep    : the character representation of the dot, will be displayed on screen
 *  @return the widget_dot created
 */
widget_dot* create_widget_dot(int posX, int posY, char rep);


/** Creates a 'line' widget
 *  @param posX   : the X position of the first point, relative to the window
 *  @param posY   : the Y position of the first point, relative to the window
 *  @param posX2  : the X position of the second point, relative to the window
 *  @param posY2  : the Y position of the second point, relative to the window
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

/** Creates a 'rectangle' widget
 *  @param posX   : the X position of the first point, relative to the window
 *  @param posY   : the Y position of the first point, relative to the window
 *  @param posX2  : the X position of the second point, relative to the window
 *  @param posY2  : the Y position of the second point, relative to the window
 *  @param rep    : the character representation of the rectangle, will be displayed on screen
 *  @return the widget_rectangle created
 */
widget_rectangle* create_widget_rectangle(int posX, int posY, int posX2, int posY2, char rep);

/** Creates a filled 'rectangle' widget
 *  @param posX   : the X position of the first point, relative to the window
 *  @param posY   : the Y position of the first point, relative to the window
 *  @param posX2  : the X position of the second point, relative to the window
 *  @param posY2  : the Y position of the second point, relative to the window
 *  @param rep    : the character representation of the rectangle, will be displayed on screen
 *  @return the widget_rectangle created
 */
widget_rectangle* create_widget_rectangle_filled(int posX, int posY, int posX2, int posY2, char rep);

/** Creates a 'circle' widget
 *  @param posX   : the X position of the center point, relative to the window
 *  @param posY   : the Y position of the center point, relative to the window
 *  @param radius : the radius of the circle, relative to the window
 *  @param rep    : the character representation of the circle, will be displayed on screen
 *  @return the widget_circle created
 */
widget_circle* create_widget_circle(int posX, int posY, int radius, char rep);

/** Creates a filled 'circle' widget
 *  @param posX   : the X position of the center point, relative to the window
 *  @param posY   : the Y position of the center point, relative to the window
 *  @param radius : the radius of the circle, relative to the window
 *  @param rep    : the character representation of the circle, will be displayed on screen
 *  @return the widget_circle created
 */
widget_circle* create_widget_circle_filled(int posX, int posY, int radius, char rep);


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

#endif