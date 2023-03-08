#include <stdlib.h>

#include "game.h"
#include "field.h"

Shape random_shape() {
  return (Shape) rand() % 4;
}

GameState init() {
  GameState state;
  state.buf = alloc_new_frame();
  init_frame(state.buf);
  state.shape = random_shape();
  state.tick = 0;
  state.score = 0;
  return state;
}

void tick(GameState *state) {
#if DEBUG
  printf("info > tick called\n");
#endif

  state->tick++;
}