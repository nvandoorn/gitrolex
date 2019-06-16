#ifndef GITROLEX_CORE_H
#define GITROLEX_CORE_H

#include <stdlib.h>
#include <stdio.h>

int gitrolex_core();

enum Task_t {
  ERROR = -1,
  STATUS = 0,
  EXPORT,
  TRACK
};

struct State_t {
  enum Task_t task;
  char taskArgs[1024];
};

void gitrolex_parseArgs(struct State_t *s, int argc, const char *argv[]);

#endif
