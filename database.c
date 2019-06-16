#include "database.h"

#include <stdlib.h>
#include <stdio.h>

void database_prefixPath(const char *path, char *out) {
  sprintf(out, ".rolex/%s", path);
}

enum DatabaseError_t database_pushEntry(const char *path, struct TimeEnty_t *entry) {
  return OUT_OF_SPACE;
}

enum DatabaseError_t database_getEntries(const char *path, struct TimeEnty_t *out, int *size) {
  return OUT_OF_SPACE;
}
