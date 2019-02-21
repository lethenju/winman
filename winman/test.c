// TEST.C for testing winman

#include "winman.h"
#include "winman_types.h"
#include "../termlib/screen.h"
#include "../termlib/termlib.h"


void* init(winman_context* ctx){
    add_window(ctx, 10,10,10,10);
    add_window(ctx, 20, 20, 30, 30);
}

void* event_loop(winman_context* ctx) {
    char c;
    display_windows(ctx);    

    while((c=getchar())!= '.') {
        switch (c){

        }       
    }
}


// DO NOT TOUCH MAIN
int main(int argc, char *argv[])
{
    winman_context* ctx = winman_init((void*)init);
    winman_event_loop(ctx, (void*)event_loop);
    return 0;
}
