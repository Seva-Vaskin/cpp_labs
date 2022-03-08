#include "algorithm.h"
#include "util.h"
#include "io.h"

int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
}
