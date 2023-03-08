#include <stdio.h>
#include <stdbool.h>

#include "global.h"
#include "field.h"

int main() {
  char **buf = alloc_new_frame();
  init_frame(buf);
  while (true) {
    clear_frame(buf);
    draw(buf);
    break;
  }
  
  return 0;
}