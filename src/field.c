#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "field.h"
#include "global.h"

void prepare(char **buf, size_t heigth, size_t width) {
  for (size_t i = 0; i < width; i++) {
    buf[0][i] = '-';
    // buf[heigth + i] = '-';
  }

  for (size_t i = 0; i < heigth; i++) {
    buf[heigth][width - 1] = '\n';
  }

  for (size_t i = 1; i < FIELD_HEIGHT * FIELD_WIDTH; i += FIELD_HEIGHT) {
    for (size_t j = 0; j < FIELD_HEIGHT - 1; j++) {
      buf[i][j] = '0';
    }

    // buf[i + FIELD_HEIGHT - 1] = '\n';
  }
}

char **new_frame() {
  size_t heigth = FIELD_HEIGHT + 2;
  size_t width = FIELD_WIDTH + 3;

#ifdef DEBUG
  printf(stderr, "info > alloc_frame_buf frame_info:\n");
  printf(stderr, "\th: %zu w: %zu\n", heigth, width);
  printf(stderr, "\tbytes: %zu\n\n", sizeof(char) * heigth * width);
#endif

  char **buf = (char **)malloc(sizeof(char) * heigth);

  for (size_t i = 0; i < FIELD_HEIGHT + 2; i++)
    buf[i] = (char *)malloc(sizeof(char) * heigth);

  prepare(buf, heigth, width);
  return buf;
}

void draw(char **buf, size_t heigth, size_t width) {
  NOT_NULL(buf);
  
#ifdef DEBUG
  printf(stderr, "info > draw (h: %zu; w: %zu)", heigth, width);
#endif

  // todo: replace printf
  for (size_t i = 0; i < heigth; i++) {
    printf("\t%s", buf[i]);
  }

  free(buf);
}