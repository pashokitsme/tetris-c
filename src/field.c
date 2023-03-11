#include <conio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "field.h"
#include "global.h"

char **alloc_new_buffer(size_t heigth, size_t width) {
  char **buf = (char **)malloc(sizeof(char *) * heigth);
  NOT_NULL(buf);
  for (size_t i = 0; i < heigth; i++) {
    buf[i] = (char *)malloc(sizeof(char) * width);
    NOT_NULL(buf[i]);
  }

  return buf;
}

char **init_frame() {
  char **buf = alloc_new_buffer(FIELD_HEIGHT, FIELD_WIDTH);

  for (size_t i = 1; i < FIELD_WIDTH - 1; i++) {
    buf[0][i] = '-';
    buf[FIELD_HEIGHT - 1][i] = '-';
  }

  for (size_t i = 1; i < FIELD_HEIGHT - 1; i++) {
    buf[i][0] = '|';
    buf[i][FIELD_WIDTH - 1] = '|';
  }

  buf[0][0] = '+';
  buf[0][FIELD_WIDTH - 1] = '+';
  buf[FIELD_HEIGHT - 1][0] = '+';
  buf[FIELD_HEIGHT - 1][FIELD_WIDTH - 1] = '+';

  clear_buf(buf, FIELD_HEIGHT - 1, FIELD_WIDTH - 1);
  return buf;
}

void clear_buf(char **buf, size_t heigth, size_t width) {
  NOT_NULL(buf);

  for (size_t i = 1; i < heigth; i++)
    for (size_t j = 1; j < width; j++)
      buf[i][j] = ' ';
}

void free_buf(char **buf, size_t heigth) {
  for (size_t i = 0; i < heigth; i++)
    free(buf[i]);

  free(buf);
}