#pragma once

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define ASSERTATIONS 1

#define HELLO_WORLD "Hello, World"

#if ASSERTATIONS
#define ASSERT(condition)                                                      \
  if (!(condition)) {                                                          \
    fprintf(stderr, "error > assert failed: %s", #condition);                  \
    return;                                                                    \
  }

#define ASSERT_RETURN(condition, return_value)                                 \
  if (!(condition)) {                                                          \
    fprintf(stderr, "error > assert failed: %s. returning %s", #condition,     \
            #return_value);                                                    \
    return return_value;                                                       \
  }
#else
#define ASSERT(condition) ;
#define ASSERT_RETURN(condition, return_value) ;
#endif

#define NOT_NULL(var)                                                          \
  if (!var) {                                                                  \
    fprintf(stderr, "error > check failed: var `%s` is null", #var);           \
    exit(EXIT_FAILURE);                                                        \
  }

#define NOT_NULL_THEN(var, code)                                               \
  if (var)                                                                     \
    code;

#define TODO(msg)                                                              \
  fprintf(stderr, "error > todo reached: %s", msg);                            \
  exit(EXIT_FAILURE);

#define UNIMPLEMENTED(msg)                                                     \
  fprintf(stderr, "error > unimplemented reached: %s", msg);                   \
  exit(EXIT_FAILURE);