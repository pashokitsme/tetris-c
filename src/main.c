#include <conio.h>
#include <stdbool.h>
#include <stdio.h>

#include "field.h"
#include "game.h"
#include "global.h"

int main() {
  GameState state = init();
  bool run = true;
  char control;
  while (run) {
    control = _getch();
    if (control == 'q')
      break;
#if DEBUG
    printf("\ninfo > frame %zu\n\n", state.tick);
#endif

    tick(&state);
    draw_game_frame(state.buf);
  }

  return 0;
}