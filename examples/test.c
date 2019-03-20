/**
 * winman version 0.1 (c) Julien LE THENO
 * (c) MIT LICENSE
 */
#include "winman.h"
#include "widgets.h"
#include "winman_types.h"
#include "tasks_mgmt.h"
#include "screen.h"
#include "termlib.h"
#include "resman.h"
#include "log_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING_LENGTH 1024

// our test application can toggle between inter window (move and manage the windows)
// and intra-window : modify the widgets inside the window. 
static int mode_intra_window = 0;

// we'll deal with that later
void task_of_changing_window_name(winman_window *win, char c);

void* init(winman_context* ctx){
    DEBUG_TRACE("init");

    // Create a window, we link the context, the coordinate of the position and the size (width, and height)
    winman_window* first_window = add_window(ctx, 10, 10, 20, 20);

    // and a second one
    winman_window* second_window = add_window(ctx, 20, 20, 20, 25);
    
    // and finally a last one
    winman_window* third_window = add_window(ctx, 30, 5, 30, 20);

    // Lets create a text widget for the name of the first window.
    // it will be on coordinate 2:2
    widget_text* our_text = create_widget_text(2,2,"1st Window");

    // Now we have a widget_text, but we want a generic widget. 
    // we can transform it like so
    widget *name_window_1 = create_widget(TEXT, (void*) our_text);

    // and we can add it to the window
    add_widget_to_win(name_window_1, first_window);

    // To be faster, we create the widget directly in param of the add widget function
    // so now we're creating the name of the second window
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"2nd window")), second_window);
    
    // and the name of the third one
    add_widget_to_win(create_widget(TEXT, (void*) create_widget_text(2,2,"3rd window")), third_window);

    // lets get creative and create a circle also
    // the create_widget_circle takes the the center coordinates, the radius and the representation (how the edges will be shown)
    // we'll add the circle in the first window
    add_widget_to_win(create_widget(CIRCLE, (void*) create_widget_circle (5, 5, 10, '.')), first_window);

    DEBUG_TRACE("Adding input tasks");

    // Each window can have his input listener.
    // we can link a function we designed as a input task, so that the window will manage properly the keyboard when focused
    // lets give the same task to each window : changing the window name.
    add_input_task(first_window,(void*) task_of_changing_window_name);
    add_input_task(second_window,(void*) task_of_changing_window_name);
    add_input_task(third_window,(void*) task_of_changing_window_name);

    // Lets get the screen ready by filling spaces in it
    // the screen properties are in the termlib controller
    fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ', FG_DEFAULT, BG_DEFAULT);
    
    // and display_windows will get the windows on the screen
    display_windows(ctx);    

    // Now that our frame is ready to be displayed, unlock it for real display
    screen_frame_ready(ctx->termlib_ctx->screen);
    DEBUG_TRACE("init done");
}

void* event_loop(winman_context* ctx) {
    // The event loop is the main loop, that will manage events from the keyboard
    char c;

    // getting the char pressed on keyboard. 
    while((c=getchar())!= '.') { // exit loop on '.'

        // this commented out code allows you to monitor the allocations made in the program, through the resource manager    
            // WARNING_TRACE("Total allocated bytes : %d",resman_get_total_size_allocated());
            // int nb_resource_allocated = resman_get_number_of_resources();
            // int counter;
            // for (counter = 0; counter < nb_resource_allocated; counter++)
            // {
            //     WARNING_TRACE("%d | S: %d | %s", counter, resman_get_size_of_resource(counter), resman_get_name_of_resource(counter));
            // }
        
        // lets get the window task system functional
        // get the current window
        winman_window *win= get_last_window(ctx);
        // if an input_manager has been created, and we're in focused mode
        if (win->input_manager != NULL && mode_intra_window)
        {
            if (c == '0') // pressing '0' gets you out of focused mode, ready to move and manage the windows 
                mode_intra_window = 0;
            else
                win->input_manager(win, c); // trigger the input manager of the window
        }
        else  // we're in mode INTER_WINDOW, or there is no input_manager
        {
            switch (c){
                case 'v':
                    // like alt tab on modern DE, shift the current window the the next one
                    shift_window_layer(ctx);
                    break;
                case 'z':
                    // move up current window
                    win->posY--;
                    break;
                case 'q':
                    // move left current window
                    win->posX--;
                    break;
                case 's':
                    // move down current window
                    win->posY++;
                    break;
                case 'd':
                    // move right current window
                    win->posX++;
                    break;
                case 'c':
                    // create new window
                    add_window(ctx, 40, 40,30,30);
                    break;
                case 'x':
                    // delete current window
                    del_last_window(ctx);
                    break;
                case '0':
                    // Change mode to the intra window
                    mode_intra_window = 1;
                    break;
            }
        }
        // lets get the screen ready and display it.
        fill_rectangle(ctx->termlib_ctx->screen, 0, 0, ctx->termlib_ctx->screen->width, ctx->termlib_ctx->screen->height, ' ', FG_DEFAULT, BG_DEFAULT);
        display_windows(ctx);    
        screen_frame_ready(ctx->termlib_ctx->screen);

    }
}

// the main function deals at the highest level
int main(int argc, char *argv[])
{
    // initialize the resource manager
    resman_init();
    // initialize the log system
    log_init();
    // initialize the window manager
    winman_context* ctx = winman_init((void*)init);
    // launches the event loop
    winman_event_loop(ctx, (void*)event_loop);
    // end and free the resources and resource manager
    resman_end();
    return 0;
}

// The task of changing window name, as given to the windows
void task_of_changing_window_name(winman_window *win, char c)
{
    WARNING_TRACE("Char C = %d --- %c", c, c);

    // retrieves the widget_text in a quite dirty way TODO!
    widget_text *wid = win->widget_list->widget_data;
    
    if (c==127) // backspace
    {   
        if (safe_strlen(wid->text, MAX_STRING_LENGTH)>0)
            wid->text[safe_strlen(wid->text, MAX_STRING_LENGTH) -1] = '\0';
    }
    else
    {
        char* new_text = malloc(sizeof(wid->text)+1);  
        strcpy(new_text, wid->text);
        new_text[safe_strlen(wid->text, MAX_STRING_LENGTH)] = c;
        wid->text = new_text;
    }
}
