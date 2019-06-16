#ifndef GITROLEX_DATABASE_H
#define GITROLEX_DATABASE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * This file implements a simple key value database using
 * double precision floating point numbers. Strings may need to
 * be supported at some point
 */

struct Database_t {
  char *path;
  int maxSize; // in bytes
};

enum DatabaseError_t {
  OK = 0,
  OUT_OF_SPACE
};

enum DatabaseError_t database_getDouble(struct *Database_t db, const char *path, double *val);
enum DatabaseError_t database_setDouble(struct *Database_t db, const char *path, double *val);


#endif
