#include "include/psed.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char last_nth(Psed *ppsed, int n) {
  return ppsed->history[(ppsed->hist_ind + ppsed->longest_len - n) % ppsed->longest_len];
}

void print_history(Psed *ppsed) {
  printf("hist_ind = %d\n", ppsed->hist_ind);
  for (int k = 0; k < ppsed->longest_len; ++k) {
    printf("%c ", ppsed->history[k]);
  }
  printf("\n");
}

void clear_history(Psed *ppsed) {
  for (int i = 0; i < ppsed->longest_len; ++i) *(ppsed->history + i) = -1;
  ppsed->hist_ind = 0;
  ppsed->valid_hist_count = 0;
}

char advance(Psed *ppsed) {
  char c = ppsed->eof_seen ? -1 : getchar();
  int vhc = ppsed->valid_hist_count;
  int ll = ppsed->longest_len;
  // Dummy value to signify that no character was discarded when moving.
  char to_ret = -2;
  if (vhc == ll)
    to_ret = *(ppsed->history + ppsed->hist_ind);
  else
    ppsed->valid_hist_count += 1;
  ppsed->history[ppsed->hist_ind] = c;
  ppsed->hist_ind = (ppsed->hist_ind + 1) % ppsed->longest_len;
  if (c == EOF) ppsed->eof_seen = true;
  return to_ret;
}

const char *process_history(Psed *ppsed, int match_ind) {
  if (ppsed->valid_hist_count == ppsed->plengths[match_ind]) {
    clear_history(ppsed);
    advance(ppsed);
    return ppsed->subs[match_ind];
  } else {
    ppsed->temp[0] =
        ppsed->history[(ppsed->hist_ind + ppsed->longest_len - ppsed->valid_hist_count) %
                       ppsed->longest_len];
    --ppsed->valid_hist_count;
    return ppsed->temp;
  }
}

void init_psed(Psed *ppsed, const char **pats, const char **subs, int count) {
  ppsed->count = count;
  ppsed->pats = pats;
  ppsed->subs = subs;
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
  clear_history(ppsed);
  ppsed->eof_seen = false;
  ppsed->temp[1] = '\0';
}
const char *next(Psed *ppsed) {
  for (;;) {
    for (int i = 0; i < ppsed->count; ++i) {
      int len = *(ppsed->plengths + i);
      if (len <= ppsed->valid_hist_count) {
        bool is_match = true;
        for (int j = 0; j < len; ++j) {
          if (ppsed->pats[i][j] != last_nth(ppsed, len - j)) {
            is_match = false;
            break;
          }
        }
        if (is_match) {
          return process_history(ppsed, i);
        }
      }
    }
    char discard = advance(ppsed);
    if (discard != -2) {
      ppsed->temp[0] = discard;
      return ppsed->temp;
    }
  }
}
void destroy_psed(Psed *ppsed) {
  free((void *)ppsed->plengths);
  free((void *)ppsed->history);
}
