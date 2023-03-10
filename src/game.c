#include <stdbool.h>
#include <stdlib.h>

#include "field.h"
#include "game.h"


Shape random_shape() {
  Shape shape;
  shape.kind = (ShapeDef)rand() % 4;
  char buf[2][3] = {' '};
  switch (shape.kind) {
  case L:
    break;
  case Z:
  case T:
  case I:
  case O:
    break;
  }

  shape.shape = buf;
  return shape;
}

GameState init() {
  GameState state;
  state.buf = init_frame();
  state.shape = random_shape();
  state.tick = 0;
  state.score = 0;
  return state;
}

bool is_line_completed(GameState *state, size_t height) {
  for (size_t i = 1; i < FIELD_WIDTH - 1; i++) {
    if (state->buf[height][i] == ' ')
      return false;
  }

  return true;
}

bool is_line_empty(GameState *state, size_t heigth) {
  for (size_t i = 1; i < FIELD_WIDTH - 1; i++) {
    if (state->buf[heigth][i] != ' ')
      return false;
  }

  return true;
}

void move_all_down(GameState *state) { TODO("move_all_down"); }

void clear_line(GameState *state, size_t heigth) {
  if (heigth <= 0 || heigth >= FIELD_HEIGHT)
    return;

  for (size_t i = 1; i < FIELD_WIDTH - 1; i++)
    state->buf[heigth][i] = ' ';
}

void tick(GameState *state) {
#if DEBUG
  printf("info > tick called\n");
#endif

  state->tick++;
}