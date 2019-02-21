// TEST.C for testing winman

#include "winman.h"
#include "winman_types.h"
#include "../termlib/screen.h"
#include "../termlib/termlib.h"


void* init(termlib_context* ctx){
    
}

void* event_loop(termlib_context* ctx) {
    char c;
    while((c=getchar())!= '.') {
        switch (c){

        }       
        fill_rectangle(ctx->screen, 1,1, ctx->screen->width-2, ctx->screen->height-2,' ');
    }
}


// DO NOT TOUCH MAIN
int main(int argc, char *argv[])
{
    termlib_context* ctx = termlib_init((void*)init);
    termlib_event_loop(ctx, (void*)event_loop);
    return 0;
}
