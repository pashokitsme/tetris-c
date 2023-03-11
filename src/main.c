#include <stdbool.h>
#include <stdio.h>

#include "field.h"
#include "game.h"
#include "global.h"

int main() {
  GameState state = init();
  bool run = true;
  while (run) {

#if DEBUG
    printf("\ninfo > frame %zu\n\n", state.tick);
#endif

    clear_buf(state.buf, FIELD_HEIGHT, FIELD_WIDTH);
    tick(&state);
    draw_game_frame(state.buf);
  }

  return 0;
}