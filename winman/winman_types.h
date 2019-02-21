#ifndef WINMAN_TYPES
#define WINMAN_TYPES

typedef enum {
    ZERO,
    DOT,
    LINE,
    TEXT,
    RECTANGLE,
    CIRCLE,
    NB_WIDGETS
} widget_type_enum;


typedef struct {
    int posX;
    int posY;
    char rep;
} widget_dot;

typedef struct {
    widget_dot* A;
    widget_dot* B; 
    char rep;
} widget_line;

typedef struct {
    widget_dot* position;
    char* text;
} text;

typedef struct {
    widget_dot* top_left_corner;
    widget_dot* down_right_corner;
    int filled;
    char rep;
} widget_rectangle;

typedef struct {
    widget_dot* center;
    int radius;
    int filled;
} widget_circle;

typedef struct widget_t widget;

typedef struct widget_t {
    int posX;
    int posY;
    widget_type_enum type;
    void* widget_data;
    widget* next;
} widget;

typedef struct winman_window_t winman_window;
typedef struct winman_window_t {
    int posX;
    int posY;
    int width;
    int height;
    widget* widget_list;
    winman_window* next;
} winman_window;


typedef struct {
    winman_window* window_list;
} winman_context;

#endif
