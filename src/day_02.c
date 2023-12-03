#include <stdio.h>

#include "include/psed.h"

int main() {
  const char *pats[2] = {"red", "blue"};
  const char *subs[2] = {"1", "2"};
  Psed psed;
  init_psed(&psed, pats, subs, 2);
}
