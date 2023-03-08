#pragma once

#include "global.h"

typedef enum {
  L, Z, T, I, O
} Shape;

typedef struct {
  char **buf;
  long long tick;
  int score;
  Shape shape;
} GameState;

GameState init();
void tick(GameState *state);
