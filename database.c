#include "database.h"

#include <stdlib.h>
#include <stdio.h>

void database_prefixPath(const char *path, char *out) {
  sprintf(out, ".rolex/%s", path);
}

enum DatabaseError_t database_pushEntry(const char *path, struct TimeEnty_t *entry) {
  char filePath[1024];
  FILE *f;
  database_prefixPath(path, filePath);
  mkdir(".rolex", 0777);
  f = fopen(filePath, "a");
  fprintf(f, "%d %ld\n", entry->direction, entry->datetime);
  fclose(f);
  return DB_OK;
}

enum DatabaseError_t database_getEntries(const char *path, struct TimeEnty_t *out, int *size) {
  *size = 0;
  return OUT_OF_SPACE;
}
