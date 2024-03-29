#pragma once

#include "global.h"

static const char Shape_L[2][3] = {
  { 'X', ' ', ' ' },
  { 'X', 'X', 'X' }
};

static const char Shape_Z[2][3] = {
  { 'X', 'X', ' ' },
  { ' ', 'X', 'X' }
};

static const char Shape_I[2][3] = {
  { ' ', ' ', ' ' },
  { 'X', 'X', 'X' }
};

static const char Shape_T[2][3] = {
  { ' ', 'X', ' ' },
  { 'X', 'X', 'X' }
};

static const char Shape_O[2][3] = {
  { 'X', 'X', ' ' },
  { 'X', 'X', ' ' }
};

static const char Shape_Empty[2][3] = {
  { ' ', ' ', ' '},
  { ' ', ' ', ' '}
};

typedef enum { L, Z, T, I, O } ShapeDef;

typedef struct {
  ShapeDef kind;
  size_t x;
  size_t y;
  char shape[2][3];
} Shape;

typedef struct {
  char **buf;
  long long tick;
  int score;
  Shape shape;
  bool run;
} GameState;

GameState game_state_init();
void draw(GameState *state);
Shape random_shape();
bool move_shape(GameState *state, char control);
void tick(GameState *state, char input);
