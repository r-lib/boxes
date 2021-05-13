
#include <Rinternals.h>
#include <progress.h>

SEXP test0() {
  int i;
  int res = 0;
  for (i = 0; i < 2000000000; i++) {
    res += i % 2;
  }
  return ScalarInteger(res);
}

SEXP test1() {
  int i;
  int res = 0;
  cli_progress_bar();
  for (i = 0; i < 2000000000; i++) {
    if (SHOULD_TICK) cli_progress_update();
    res += i % 2;
  }
  return ScalarInteger(res);
}

SEXP test2() {
  int i = 0;
  int res = 0;
  cli_progress_bar();
  int s, final, step = 2000000000 / 100000;
  for (s = 0; s < 100000; s++) {
    final = (s + 1) * step;
    for (i = s * step; i < final; i++) {
      res += i % 2;
    }
    if (SHOULD_TICK) cli_progress_update();
  }
  return ScalarInteger(res);
}

static const R_CallMethodDef CallEntries[] = {
  { "test0", (DL_FUNC) test0, 0 },
  { "test1", (DL_FUNC) test1, 0 },
  { "test2", (DL_FUNC) test2, 0 },
  { NULL, NULL, 0 }
};

void R_init_progresstest(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
