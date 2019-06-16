#ifndef TEST_LIB_H
#define TEST_LIB_H

typedef int (*syncTestHandler_t)();

int syncTest(char *testName, char *errMsg, int (*testCallback)());

#endif
