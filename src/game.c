#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"
#include "game.h"

Shape random_shape() {
  Shape shape;
  shape.kind = (ShapeDef)rand() % 4;
  shape.x = 0;
  shape.y = 0;
  switch (shape.kind) {
  case L:
    memcpy(shape.shape, Shape_L, sizeof(char) * 2 * 3);
    break;
  case Z:
    memcpy(shape.shape, Shape_Z, sizeof(char) * 2 * 3);
    break;
  case T:
    memcpy(shape.shape, Shape_T, sizeof(char) * 2 * 3);
    break;
  case I:
    memcpy(shape.shape, Shape_I, sizeof(char) * 2 * 3);
    break;
  case O:
    memcpy(shape.shape, Shape_O, sizeof(char) * 2 * 3);
    break;
  }

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

bool is_line_fully(GameState *state, size_t height) {
  ASSERT_RETURN(HEIGHT_CHECK(height), false);

  for (size_t i = 1; i < FIELD_WIDTH - 1; i++) {
    if (state->buf[height][i] == ' ')
      return false;
  }

  return true;
}

bool is_down_empty(GameState *state, size_t height, size_t width) {
  ASSERT_RETURN(HEIGHT_CHECK(height), false);
  ASSERT_RETURN(WIDTH_CHECK(width), false);
  TODO("is_down_empty");
}

bool is_line_empty(GameState *state, size_t heigth) {
  for (size_t i = 1; i < FIELD_WIDTH - 1; i++) {
    if (state->buf[heigth][i] != ' ')
      return false;
  }

  return true;
}

void move_all_down(GameState *state) { TODO("move_all_down"); }

void clear_line(GameState *state, size_t height) {
  ASSERT(HEIGHT_CHECK(height));
  for (size_t i = 1; i < FIELD_WIDTH - 1; i++)
    state->buf[height][i] = ' ';
}

void tick(GameState *state) {
#if DEBUG
  printf("info > tick called\n");
#endif

  state->tick++;
}