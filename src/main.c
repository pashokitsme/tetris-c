#include <conio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "field.h"
#include "game.h"
#include "global.h"

int main() {
  GameState state = game_state_init();
  GameState *state_ptr = &state;
  char control = '\0';

  printf("controls:\n\ta - move shape left\n\td - move shape right\n\tq - "
         "exit\n\tany key - next tick\n");

  loop {
#if DEBUG
    printf("info > tick: %zu\n", state.tick);
    printf("info > shape kind: %d\n", state.shape.kind);
#endif

    tick(state_ptr, control);
    draw(state_ptr);

    control = _getch();
    if (control == 'q')
      break;
  }

  return 0;
}