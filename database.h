#ifndef GITROLEX_DATABASE_H
#define GITROLEX_DATABASE_H

#include <stdlib.h>
#include <stdio.h>

#define IN true
#define OUT false

struct TimeEnty_t {
  int datetime;
  bool direction; // IN || OUT
};

enum DatabaseError_t {
  OK = 0,
  OUT_OF_SPACE
};

enum DatabaseError_t database_pushEntry(const char *path, struct TimeEnty_t *entry);
enum DatabaseError_t database_getEntries(const char *path, struct TimeEnty_t *out, int *size);

#endif
