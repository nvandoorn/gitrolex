#include "test-lib.h"
#include "core.h"

#include <stdlib.h>
#include <stdio.h>

int parseArgsTest() {
  // mocks
  int argc = 1;
  char *argv[10];
  struct State_t s;

  // should fail with no args
  gitrolex_parseArgs(&s, argc, argv);
  if(s.task != ERROR) {
    goto fail;
  }

  // should fail if we track without a name
  argc = 2;
  argv[1] = "track";
  gitrolex_parseArgs(&s, argc, argv);
  if(s.task != ERROR) {
    goto fail;
  }

  // should track a named task
  argc = 3;
  argv[1] = "track";
  argv[2] = "my-feature-branch";
  gitrolex_parseArgs(&s, argc, argv);
  if(s.task != TRACK) {
    goto fail;
  }
  if(strcmp(s.taskArgs, argv[2])) {
    goto fail;
  }
  return 0;
fail:
  return -1;
}

int main() {
  syncTest("gitrolex_parseArgs", "Failed to parse command line arguments", parseArgsTest);
}
