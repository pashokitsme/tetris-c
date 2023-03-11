#pragma once

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define ASSERTATIONS 1

#define loop while(1)

#if ASSERTATIONS
#define ASSERT(condition)                                                      \
  if (!(condition)) {                                                          \
    fprintf(stderr, "error > assert failed: %s\n", #condition);                  \
    return;                                                                    \
  }

#define ASSERT_RETURN(condition, return_value)                                 \
  if (!(condition)) {                                                          \
    fprintf(stderr, "error > assert failed: %s. returning %s\n", #condition,     \
            #return_value);                                                    \
    return return_value;                                                       \
  }
#else
#define ASSERT(condition) ;
#define ASSERT_RETURN(condition, return_value) ;
#endif

#define NOT_NULL(var)                                                          \
  if (!var) {                                                                  \
    fprintf(stderr, "error > check failed: var `%s` is null\n", #var);           \
    exit(EXIT_FAILURE);                                                        \
  }

#define NOT_NULL_THEN(var, code)                                               \
  if (var)                                                                     \
    code;

#define TODO(msg)                                                              \
  fprintf(stderr, "error > todo reached: %s\n", msg);                            \
  exit(EXIT_FAILURE);

#define UNIMPLEMENTED(msg)                                                     \
  fprintf(stderr, "error > unimplemented reached: %s\n", msg);                   \
  exit(EXIT_FAILURE);