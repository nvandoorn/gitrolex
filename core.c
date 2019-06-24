#include "core.h"
#include "database.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void printError(const char *s) {
  printf("ERROR: %s\n", s);
}


void printInfo(const char *s) {
  printf("INFO: %s\n", s);
}

char* replaceChar(char* str, char find, char replace) {
  char *currentPos = strchr(str,find);
  while(currentPos) {
    *currentPos = replace;
    currentPos = strchr(currentPos, find);
  }
  return str;
}

void gitrolex_parseArgs(struct State_t *s, int argc, const char *argv[]) {
  const char *task;
  if(argc < 3) {
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
    s->task = TRACK;
  }
  strcpy(s->taskArgs, argv[2]);
  // lame attempt at path sanitization
  replaceChar(s->taskArgs, '/', '-');
  replaceChar(s->taskArgs, '$', '-');
}

// TODO return a message/status such that we can test this
// (printing directly to the screen makes this hard)
enum Error_t gitrolex_status(struct State_t *s, bool force) {
  enum DatabaseError_t r;
  char msg[512];
  int size = 2048;
  struct TimeEnty_t entries[2048];
  const char *template = "You've been working on %s for %ld seconds";
  r = database_getEntries(s->taskArgs, entries, &size);
  if(r != OK || size <= 0) {
    printError("Failed to read from db");
    return OK;
  }
  else if (size == 1) {
    if(force) {
      sprintf(msg, template, s->taskArgs, time(NULL) - entries[0].datetime);
    }
    else {
      sprintf(msg, "Starting %s", s->taskArgs);
    }
  }
  else {
    long workingTime = gitrolex_calculateWorkingTime(entries, size);
    sprintf(msg, template, s->taskArgs, workingTime);
  }
  printInfo(msg);
  return OK;
}

long gitrolex_calculateWorkingTime(struct TimeEnty_t *t, int size) {
  if (size < 2) return -1;
  long sum;
  sum = 0;
  for(int i = 0; i < size - 1; i += 2) {
    struct TimeEnty_t *start = &t[i];
    struct TimeEnty_t *end = &t[i + 1];
    // we should always be taking the diff
    // between a checkout "e.g working on it" and a
    // check in "e.eg finishing work"
    if(start->direction != OUT || end->direction != IN) {
      return -1;
    }
    sum += end->datetime - start->datetime;
  }
  return sum;
}

enum Error_t pushNow(struct State_t *s, bool direction) {
  enum DatabaseError_t r;
  struct TimeEnty_t entry = {
    .direction = direction,
    .datetime = time(NULL)
  };
  r = database_pushEntry(s->taskArgs, &entry);
  gitrolex_status(s, false);
  return r == DB_OK ? OK : DB_ERROR;
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


void gitrolex_mapStateToTask(struct State_t *s) {
  enum Error_t r;
  switch(s->task) {
    case STATUS:
      gitrolex_status(s, true);
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
      printError("Usage ./gitrolex status | export | pause | play | track <branch-name>");
      break;
  }
}

int gitrolex_core(int argc, const char* argv[]) {
  struct State_t state;
  gitrolex_parseArgs(&state, argc, argv);
  gitrolex_mapStateToTask(&state);
}

