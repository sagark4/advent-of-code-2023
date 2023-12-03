#include <stdio.h>

#include "include/psed.h"

int main() {
  const char *pats[4] = {"red", "blue", "green", "Game "};
  const char *subs[4] = {"1", "2", "3", ""};
  Psed psed;
  init_psed(&psed, pats, subs, 4);
  for (const char *nxt = next(&psed); nxt[0] != EOF; nxt = next(&psed)) {
    printf("%s", nxt);
  }
}
