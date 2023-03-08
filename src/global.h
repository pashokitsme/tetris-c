#pragma once

#include <stdio.h>
#include <stdlib.h>

#define HELLO_WORLD "Hello, World"

#define NOT_NULL(var)                                                          \
  if (!var) {                                                                  \
    fprintf(stderr, "error > check failed: var `%s` is null", #var);          \
    exit(EXIT_FAILURE);                                                        \
  }

#define NOT_NULL_THEN(var, code)                                               \
  if (var)                                                                     \
    code;