#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "field.h"
#include "game.h"

bool is_down_empty(GameState *state, size_t height, size_t width);
bool is_line_empty(GameState *state, size_t heigth);
void clear_line(GameState *state, size_t height);

Shape random_shape() {
  Shape shape;
  shape.kind = (ShapeDef)rand() % 4;
  shape.x = FIELD_WIDTH / 2;
  shape.y = 3;
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

GameState game_state_init() {
  printf("info > random seed set to: %zu\n", RANDOM_SEED);
  srand(RANDOM_SEED);
  GameState state;
  state.buf = init_frame();
  state.shape = random_shape();
  state.tick = 0;
  state.score = 0;
  state.run = true;
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
  return state->buf[height + 1][width] == ' ';
}

bool is_line_empty(GameState *state, size_t heigth) {
  for (size_t i = 1; i < FIELD_WIDTH - 1; i++) {
    if (state->buf[heigth][i] != ' ')
      return false;
  }

  return true;
}

bool move_all_down(GameState *state) {
  bool moved = false;
  for (size_t i = 1; i < FIELD_HEIGHT - 2; i++) {
    for (size_t j = 1; j < FIELD_WIDTH - 1; j++) {
      if (state->buf[i][j] != 'O' || !is_down_empty(state, i, j))
        continue;
      if (!moved)
        moved = true;

      state->buf[i + 1][j] = state->buf[i][j];
      state->buf[i][j] = ' ';
    }

    if (is_line_fully(state, i)) {
      clear_line(state, i);
      i--;
    }
  }

  return moved;
}

void clear_line(GameState *state, size_t height) {
  ASSERT(HEIGHT_CHECK(height));
  for (size_t i = 1; i < FIELD_WIDTH - 1; i++)
    state->buf[height][i] = ' ';
}

void move_shape(GameState *state, char control) {
  TODO("move_shape")
  switch (control) {
  case 'a':
    if (state->buf[state->shape.y][state->shape.x + 3] != ' ')
      return;

    if (state->buf[state->shape.y + 1][state->shape.x + 3] != ' ')
      return;

    break;
  case 'd':
    break;
  }
}

bool has_space_for_new_shape(GameState *state) {
  return is_line_empty(state, 1) && is_line_empty(state, 2);
}

bool spawn_shape(GameState *state) {
  if (!has_space_for_new_shape(state))
    return false;

  state->shape = random_shape();

  return true;
}

void freeze_shape(GameState *state) {
  for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (state->shape.shape[i][j] == 'X')
        state->buf[state->shape.y + i][state->shape.x + j] = 'O';
    }
  }
}

void tick(GameState *state) {
#if DEBUG
  printf("info > tick called\n");
#endif

  if (move_all_down(state)) {
  }

  state->tick++;
}

// ↓
void draw(GameState *state) {
  size_t shape_x = state->shape.x;
  size_t shape_y = state->shape.y;
  size_t cur = 0;

  for (size_t i = 0; i < FIELD_HEIGHT; i++) {
    for (size_t j = 0; j < FIELD_WIDTH; j++) {
      ((shape_y >= i && shape_y < i + 2) && (shape_x >= j && shape_x < j + 3))
          ? _putch(*(*state->shape.shape + cur++))
          : _putch(*(*(state->buf + i) + j));
    }
    _putch('\n');
  }
}