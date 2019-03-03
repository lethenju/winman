/**
 * winman version 0.1 (c) Julien LE THENO
 * (c) MIT LICENSE
 */
#ifndef WINMAN_TYPES
#define WINMAN_TYPES
/** Winman is built on top of termlib, which provides some useful building blocks.
 */
#include "termlib_types.h"

/** widget type, available widget types
 */
typedef enum {
    ZERO,       // void widget, never used
    DOT,        // dot widget, just a pixel
    LINE,       // line widget (between 2 dots)
    TEXT,       // text widget (display text)
    RECTANGLE,  // rectangle widget
    CIRCLE,     // circle widget (and disk)
    NB_WIDGETS  
} widget_type_enum;

/** dot widget data structure
 */
typedef struct {
    int posX; // X position in cols of the dot, relative to the window in which the widget it
    int posY; // Y position in rows of the dot, relative to the window in which the widget it
    char rep; // character representation of the dot
} widget_dot;

/** line widget data structure
 */
typedef struct {
    widget_dot* A; // first end of the line
    widget_dot* B; // second end of the line
    char rep;      // character representation during the whole lenght
} widget_line;

/** text widget data structure
 */
typedef struct {
    widget_dot* position; // position of the left end of the text
    char* text;           // pointer to the actual text
} widget_text;

/** rectangle widget data structure
 */
typedef struct {
    widget_dot* top_left_corner;     // top left corner of the rectangle
    widget_dot* bottom_right_corner; // bottom right corner of the rectangle
    int filled;                      // filled flag : if 1, then the rectangle is filled with rep
    char rep;                        // character representation of the edges of the rectangle, and the inside if 'filled'
} widget_rectangle;

/** circle widget data structure
 */
typedef struct {
    widget_dot* center; // center of the circle
    int radius;         // radius of the circle
    int filled;         // filled flag : if 1, then the circle is filled with rep
    char rep;           // character representation of the edges of the circle, and the inside if 'filled
} widget_circle;

/** generic chained widget data structure
 */
typedef struct widget_t widget;
typedef struct widget_t {
    int type;           // type of the widget 
    void* widget_data;  // pointer to the actual specific widget
    widget* next;       // next widget
} widget;

/** chained window data structure 
 */
typedef struct winman_window_t winman_window;
typedef struct winman_window_t {
    int posX;            // X coordinate of the top left corner of the window
    int posY;            // Y coordinate of the top left corner of the window
    int width;           // width of the window (in cols)
    int height;          // height of the window (in rows)
    widget* widget_list; // pointer to the widget chained list
    winman_window* next; // next window
} winman_window;

/** full winman context, top of the winman data tree
 */
typedef struct {
    winman_window* window_list;   // pointer to the window list
    termlib_context* termlib_ctx; // pointer to the termlib data structures
} winman_context;

#endif
