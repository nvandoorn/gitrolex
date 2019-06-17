#include "test-lib.h"
#include "database.h"

#include <stdlib.h>
#include <stdio.h>

// You've really fucking done it now, Mark.
// Not impressed.
const static char* SAMPLE_PATH = "features/facebook-crypto-currency";

int databasePutGetTest() {
  struct TimeEnty_t input = {
    .direction = IN,
    .datetime = time(NULL)
  };
  struct TimeEnty_t output[1024];
  int size = 1024;
  database_pushEntry(SAMPLE_PATH, &input);
  database_getEntries(SAMPLE_PATH, output, &size);
  if(size != 1) {
    goto fail;
  }
  if(output[0].direction != input.direction) {
    goto fail;
  }
  if(output[0].datetime != input.datetime) {
    goto fail;
  }
  return 0;
fail:
  return -1;
}

void database_test() {
  syncTest("database_pushEntry and database_getEntries", "Failed to put then get", databasePutGetTest);
}

