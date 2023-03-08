#pragma once

#define FIELD_HEIGHT 16
#define FIELD_WIDTH 12

char **alloc_new_frame();
void clear_frame(char **buf);
void init_frame(char **buf);
void draw(char **buf);