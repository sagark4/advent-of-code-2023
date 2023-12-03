#include <stdio.h>

#include "include/psed.h"

int main() {
  const char *pats[2] = {"one", "two"};
  const char *subs[2] = {"1", "2"};
  Psed psed;
  init_psed(&psed, pats, subs, 2);
  const char *nxt;
  while((nxt = next(&psed))) printf("%s\n", nxt);
}
