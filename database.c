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
  fprintf(f, "%d %d\n", entry->direction, entry->datetime);
  fclose(f);
  return DB_OK;
}

enum DatabaseError_t database_getEntries(const char *path, struct TimeEnty_t *out, int *size) {
  char filePath[1024], line[2048];
  int lineDirection;
  long lineTime;
  FILE *f;
  int i = 0;
  database_prefixPath(path, filePath);
  f = fopen(filePath, "r");
  if(f == NULL) goto done;
  while(fgets(line, 2048, f)) {
    sscanf(line, "%d %ld", &lineDirection, &lineTime);
    out[i].direction = lineDirection;
    out[i].datetime = lineTime;
    i++;
  }
done:
  fclose(f);
  *size = i;
  return DB_OK;
}

enum DatabaseError_t database_nuke(const char *path) {
  char *filePath[1024];
  database_prefixPath(path, filePath);
  remove(filePath);
}
