#include "winman_types.h"
#include <stdlib.h>
#include <string.h>

widget_dot* create_widget_dot(int posX, int posY, char rep)
{
    widget_dot* widget_data = malloc(sizeof(widget_dot));
    widget_data->posX = posX;
    widget_data->posY = posY;
    widget_data->rep = rep;
    return widget_data;
}

widget_line* create_widget_line(int posX, int posY, int posX2, int posY2, char rep)
{
    widget_line* widget_data = malloc(sizeof(widget_line));
    widget_data->A = create_widget_dot(posX, posY, rep);
    widget_data->B = create_widget_dot(posX2, posY2, rep);
    widget_data->rep = rep;
    return widget_data;
}

widget_text* create_widget_text(int posX, int posY, char* text)
{
    widget_text* widget_data = malloc(sizeof(widget_text));
    widget_data->position = create_widget_dot(posX, posY, ' ');
    widget_data->text = text;
    return widget_data;
}


widget* create_widget(widget_type_enum type, void* widget_data) 
{
    widget* wid = malloc(sizeof(widget));
    wid->widget_data = widget_data;
    wid->type = type;
    return wid;
}