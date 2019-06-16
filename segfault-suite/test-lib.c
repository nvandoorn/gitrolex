#include "test-lib.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

static const char *GREEN = "\033[0;32m";
static const char *RED = "\033[0;31m";
static const char *ESCAPE = "\e[0m";

static void printPass() { printf("%s\tPassed\t%s\n", GREEN, ESCAPE); }

static void printFail(char *msg) {
  printf("%s\tFailed\n\t%s%s\n", RED, msg, ESCAPE);
}

int syncTest(char *testName, char *errMsg, syncTestHandler_t callback) {
  int status;
  pid_t pid;
  printf("Running %s...\n", testName);
  pid = fork();
  if(pid == 0) {
    exit(callback());
  }
  else {
    waitpid(pid, &status, 0);
    if(status == 0) {
      printPass();
    }
    else {
      printFail(errMsg);
    }
    return status;
  }
}
