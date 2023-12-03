#include "include/psed.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char advance(Psed *ppsed) {
  char c = ppsed->eof_seen ? -1 : getchar();
  int vhc = ppsed->valid_hist_count;
  int ll = ppsed->longest_len;
  // Dummy value to signify that no character was discarded when moving.
  char to_ret = -2;
  if (vhc == ll) to_ret = *(ppsed->history + ppsed->hist_ind);
  else ppsed->valid_hist_count += 1;
  ppsed->hist_ind = (ppsed->hist_ind + 1) % ppsed->longest_len;
  ppsed->history[ppsed->hist_ind] = c;
  if (c == EOF) ppsed->eof_seen = true;
  return to_ret;
}

void init_psed(Psed *ppsed, const char **pats, const char **subs, int count) {
  int *plengths = (int *)malloc(sizeof(int) * count);
  int cur_max = 0;
  for (int i = 0; i < count; ++i) {
    int len = strlen(pats[i]);
    *(plengths + i) = len;
    cur_max = cur_max > len ? cur_max : len;
  }
  ppsed->plengths = plengths;
  ppsed->longest_len = cur_max;
  ppsed->history = (char *)malloc(sizeof(char) * cur_max);
  for (int i = 0; i < cur_max; ++i) *(ppsed->history + i) = -1;
  ppsed->hist_ind = 0;
  ppsed->valid_hist_count = 0;
  ppsed->eof_seen = false;
  ppsed->temp = (char *)malloc(sizeof(char) * 2);
}
const char *next(Psed *ppsed) {
  for (;;) {
    for (int i = 0; i < ppsed->count; ++i) {
      int len = ppsed->plengths[i];
      if (len <= ppsed->valid_hist_count) {
	_Bool match = true;
        for (int j = 0; j < len; ++j) {
          if (ppsed->pats[i][j] != last_nth(ppsed, len - j)) {
            match = false;
            break;
          }
        }
	if (match) {
	  advance(ppsed);
	  return ppsed->subs[i];
	}
      }
    }
    char discard = advance(ppsed);
    if (discard != -2) {
      ppsed->temp[0] = discard;
      ppsed->temp[1] = '\0';
      return ppsed->temp;
    }
  }
}
char last_nth(Psed *ppsed, int n) {
  return ppsed->history[(ppsed->hist_ind + ppsed->longest_len - n) % ppsed->longest_len];
}
void destroy_psed(Psed *ppsed) {
  printf("TODO:");
}
