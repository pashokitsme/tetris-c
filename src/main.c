#include <stdio.h>
#include <stdbool.h>

#include "global.h"
#include "game.h"
#include "field.h"

int main() {
  GameState state = init();
  bool run = true;
  while (run) {

#if DEBUG
    printf("\ninfo > frame #%zu\n\n", state.tick);
#endif
    
    clear_frame(state.buf);
    tick(&state);
    draw(state.buf);
  }
  
  return 0;
}

/* 
  char **buf = alloc_new_frame();
  init_frame(buf);
  while (true) {
    clear_frame(buf);
    draw(buf);
    break;
  }
*/