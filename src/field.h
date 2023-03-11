#pragma once

#define FIELD_HEIGHT 16
#define FIELD_WIDTH 12

#define HEIGHT_CHECK(value) value > 0 && value < FIELD_HEIGHT
#define WIDTH_CHECK(value) value > 0 && value < FIELD_WIDTH

char **alloc_new_buffer(size_t heigth, size_t width);
void free_buf(char **buf, size_t heigth);
void clear_buf(char **buf, size_t heigth, size_t width);
char **init_frame();