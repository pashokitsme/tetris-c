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
  shape.x = 4; // FIELD_WIDTH / 2;
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

GameState game_state_init() {
#if DEBUG
  printf("info > random seed set to: %zu\n", RANDOM_SEED);
#endif

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

bool move_shape(GameState *state, char control) {
  if (state->shape.x == 2 || state->shape.x == FIELD_WIDTH - 3)
    return false;

  switch (control) {
  case 'd':
    for (size_t i = 0; i < 2; i++) {
      for (size_t j = 0; j < 3; j++) {
        size_t y = state->shape.y + i;
        size_t x = state->shape.x + j;
        if (state->shape.shape[i][j] == 'X' && state->buf[y][x + 1] != ' ')
          return false;
      }
    }
    state->shape.x++;
    break;
  case 'a':
    for (size_t i = 0; i < 2; i++) {
      for (size_t j = 0; j < 3; j++) {
        size_t y = state->shape.y + i;
        size_t x = state->shape.x + j;
        if (state->shape.shape[i][j] == 'X' && state->buf[y][x - 1] != ' ')
          return false;
      }
    }
    state->shape.x--;
    break;
  default:
    return false;
  }

  return true;
}

bool can_move_down(GameState *state) {
  if (state->shape.y < 1)
    return true;

  if (state->shape.y + 2 == FIELD_HEIGHT)
    return false;

  for (size_t y = 0; y < 2; y++) {
    for (size_t x = 0; x < 3; x++) {
      if (state->shape.shape[y][x] != 'X')
        continue;

      if (state->buf[state->shape.y + y][state->shape.x + x] != ' ')
        return false;
    }
  }

  return true;
}

void commit(GameState *state) {
  for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (state->shape.shape[i][j] == 'X')
        state->buf[state->shape.y + i - 1][state->shape.x + j] = 'O';
    }
  }
}

void tick(GameState *state, char input) {
  state->tick++;

  if (move_shape(state, input))
    return;

  if (!can_move_down(state)) {
    commit(state);
    state->shape = random_shape();
#if DEBUG
    printf("info > new shape: %d\n", state->shape.kind);
#endif
    return;
  }

  state->shape.y++;
}

void draw(GameState *state) {
  char *shape_ptr = *state->shape.shape;
  size_t shape_x = state->shape.x;
  size_t shape_y = state->shape.y;

  for (size_t i = 0; i < FIELD_HEIGHT; i++) {
    for (size_t j = 0; j < FIELD_WIDTH; j++) {
      NOT_NULL(shape_ptr);
      if ((shape_y >= i + 1 && shape_y < i + 3) &&
          (shape_x >= j - 2 && shape_x < j + 1)) {
        if (*shape_ptr == 'X') {
          _putch(*shape_ptr++);
          continue;
        }
        shape_ptr++;
      }
      _putch(*(*(state->buf + i) + j));
    }
    _putch('\n');
  }
}