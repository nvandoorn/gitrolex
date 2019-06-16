#include "core.h"
#include "database.h"

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
  else if(!strcmp(task, "pause")) {
    s->task = PAUSE;
  }
  else if(!strcmp(task, "play")) {
    s->task = PLAY;
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

enum Error_t pushNow(struct State_t *s, bool direction) {
  enum DatabaseError_t r;
  struct TimeEnty_t entry = {
    .direction = direction,
    .datetime = time(NULL)
  };
  r = database_pushEntry(s->taskArgs, &entry);
  gitrolex_status(s);
  return r == OK ? OK : DB_ERROR;
}

enum Error_t gitrolex_checkout(struct State_t *s){
  return pushNow(s, OUT);
}

enum Error_t gitrolex_checkin(struct State_t *s){
  return pushNow(s, IN);
}

enum Error_t gitrolex_export(struct State_t *s) {
  return -1;
}

enum Error_t gitrolex_status(struct State_t *s) {
  return -1;
}

void gitrolex_mapStateToTask(struct State_t *s) {
  enum Error_t r;
  switch(s->task) {
    case STATUS:
      gitrolex_status(s);
      break;
    case EXPORT:
      r = gitrolex_export(s);
      break;
    case TRACK:
      r = gitrolex_checkout(s);
      break;
    case PAUSE:
      r = gitrolex_checkin(s);
      break;
    case PLAY:
      r = gitrolex_checkout(s);
      break;
    case ERROR:
    default:
      printError("Usage ./gitrolex status | export | pause | play | track <branch-name>")
      break;
  }
}

int gitrolex_core(int argc, const char* argv[]) {
  struct State_t state;
  gitrolex_parseArgs(&state, argc, argv);
  gitrolex_mapStateToTask(&state);
}

