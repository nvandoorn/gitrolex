import { writeFileSync } from "fs";
import { argv } from "process";

interface LibPack {
  header: string;
  source: string;
  test: string;
  testHeader: string;
}

const std = `
#include <stdlib.h>
#include <stdio.h>
`;

const makeHeader = (includeGuard: string, stdinclude: boolean) =>
  `
#ifndef ${includeGuard}
#define ${includeGuard}

${stdinclude ? std : ""}

#endif
`;

const makeSource = (libname: string, stdinclude: boolean) => `
#include "${libname}.h"
${stdinclude ? std : ""}
`;

const makeTest = (libname: string) =>
  `
#include "test-lib.h"
#include "${libname}.h"

${std}
`;

const makeTestHeader = (includeGuard: string, stdinclude: boolean) =>
  makeHeader(`${includeGuard}_TEST`, stdinclude);

function makeCLib(
  libname: string,
  includeGuard: string,
  stdinclude: boolean = true
): LibPack {
  return {
    header: makeHeader(includeGuard, stdinclude),
    source: makeSource(libname, stdinclude),
    test: makeTest(libname),
    testHeader: makeTestHeader(includeGuard, stdinclude)
  };
}

function write(filename: string, blob: string) {
  return writeFileSync(`${__dirname}/${filename}`, blob);
}

function writeCLib(libname: string, libpack: LibPack) {
  write(`${libname}.c`, libpack.source);
  write(`${libname}.h`, libpack.header);
  write(`${libname}.test.c`, libpack.test);
  write(`${libname}.test.h`, libpack.testHeader);
}

(function() {
  const pack = makeCLib(argv[2], argv[3], argv[4] === "true");
  writeCLib(argv[2], pack);
})();
