#include "winman_types.h"
#include "resman.h"
#include <stdlib.h>
#include <string.h>

widget_dot* create_widget_dot(int posX, int posY, char rep)
{
    widget_dot* widget_data = resman_alloc("widget_dot",sizeof(widget_dot));
    widget_data->posX = posX;
    widget_data->posY = posY;
    widget_data->rep = rep;
    return widget_data;
}

widget_line* create_widget_line(int posX, int posY, int posX2, int posY2, char rep)
{
    widget_line* widget_data = resman_alloc("widget_line", sizeof(widget_line));
    widget_data->A = create_widget_dot(posX, posY, rep);
    widget_data->B = create_widget_dot(posX2, posY2, rep);
    widget_data->rep = rep;
    return widget_data;
}

widget_text* create_widget_text(int posX, int posY, char* text)
{
    widget_text* widget_data = resman_alloc("widget_text", sizeof(widget_text));
    widget_data->position = create_widget_dot(posX, posY, ' ');
    widget_data->text = text;
    return widget_data;
}

widget_rectangle* create_widget_rectangle(int posX, int posY, int posX2, int posY2, char rep)
{
    widget_rectangle* widget_data = resman_alloc("widget_rectangle",sizeof(widget_rectangle));
    widget_data->top_left_corner = create_widget_dot(posX, posY, rep);
    widget_data->bottom_right_corner = create_widget_dot(posX2, posY2, rep);
    widget_data->filled = 0;
    widget_data->rep = rep;
    return widget_data;
}

widget_rectangle* create_widget_rectangle_filled(int posX, int posY, int posX2, int posY2, char rep)
{
    widget_rectangle* widget_data = create_widget_rectangle(posX, posY, posX2, posY2, rep);
    widget_data->filled = 1;
    return widget_data;
}

widget_circle* create_widget_circle(int posX, int posY, int radius, char rep)
{
    widget_circle* widget_data = resman_alloc("widget_circle", sizeof(widget_circle));
    widget_data->center = create_widget_dot(posX, posY, rep);
    widget_data->radius = radius;
    widget_data->filled = 0;
    widget_data->rep = rep;
    return widget_data;
}

widget_circle* create_widget_circle_filled(int posX, int posY, int radius, char rep)
{
    widget_circle* widget_data = create_widget_circle(posX, posY, radius, rep);
    widget_data->filled = 1;
    return widget_data;
}


widget* create_widget(widget_type_enum type, void* widget_data) 
{
    widget* wid = resman_alloc("widget", sizeof(widget));
    wid->widget_data = widget_data;
    wid->type = type;
    return wid;
}
