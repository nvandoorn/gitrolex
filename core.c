#include "core.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printError(const char *s) {
  printf("ERROR: %s\n", s);
}


void printInfo(const char *s) {
  printf("INFO: %s\n", s);
}

void gitrolex_parseArgs(struct State_t *s, int argc, const char *argv[]) {
  const char *task;
  if(argc < 2) {
    s->task = ERROR;
    return;
  }
  task = argv[1];
  if(!strcmp(task, "status")) {
    s->task = STATUS;
  }
  else if(!strcmp(task, "export")) {
    s->task = EXPORT;
  }
  else if(!strcmp(task, "track")) {
    // if we're tracking time,
    // we need a branch name stored
    // in the args
    if(argc < 3) {
      s->task = ERROR;
      return;
    }
    s->task = TRACK;
    strcpy(s->taskArgs, argv[2]);
  }
}

int gitrolex_core(int argc, const char* argv[]) {
  struct State_t state;
  gitrolex_parseArgs(&state, argc, argv);
  printf("Usage ./gitrolex status | export | track <branch-name>\n");
}

