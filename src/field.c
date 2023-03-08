#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "field.h"
#include "global.h"

char **alloc_new_frame() {
#ifdef DEBUG
  printf("info > alloc_frame_buf frame_info: ");
  printf("h: %d w: %d\n", FIELD_HEIGHT, FIELD_WIDTH);
#endif

  char **buf = (char **)malloc(sizeof(char *) * FIELD_HEIGHT);
  NOT_NULL(buf);
  for (size_t i = 0; i < FIELD_HEIGHT; i++) {
    buf[i] = (char *)malloc(sizeof(char) * FIELD_WIDTH);
    NOT_NULL(buf[i]);
  }

  return buf;
}

void init_frame(char **buf) {
#ifdef DEBUG
  printf("info > init_frame called\n");
#endif

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

  clear_frame(buf);
}

void clear_frame(char **buf) {
#ifdef DEBUG
  printf("info > clear_frame called\n");
#endif

  for (size_t i = 1; i < FIELD_HEIGHT; i++)
    for (size_t j = 1; j < FIELD_WIDTH; j++)
      buf[i][j] = ' ';
}

void draw(char **buf) {
  NOT_NULL(buf);

#ifdef DEBUG
  printf("info > draw called\n");
#endif

  for (size_t i = 0; i < FIELD_HEIGHT; i++) {
    for (size_t j = 0; j < FIELD_WIDTH; j++)
      putchar(buf[i][j]);
    putchar('\n');
    free((void *)buf[i]);
  }

  free((void *)buf);
}