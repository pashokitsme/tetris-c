#include <stdio.h>
#include <stdbool.h>

#include "global.h"
#include "game.h"
#include "field.h"

int main() {
  GameState state = init();
  tick(&state);
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