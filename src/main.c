#include <stdbool.h>
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <unistd.h>
#endif

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

#if defined(_WIN32) || defined(_WIN64)
    Sleep(1000);
#else
    sleep(1)
#endif
  }

  return 0;
}