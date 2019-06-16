# segfault-suite

A small test framework that catches segmentation faults.

## Dependencies

1. POSIX compliant OS (`fork`, `waitpid`)

## Usage

```C
#include "test-lib.h"

int badTest() {
  int* ptr = (int*)0;
  *ptr = 5;
  return 0;
}

int main() {
  syncTest("badTest", "it segfaulted", badTest);
  return 0;
}
```
