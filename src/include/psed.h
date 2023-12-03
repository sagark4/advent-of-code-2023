#ifndef PSED_H
#define PSED_H

#include<stdbool.h>

// No ownership taken of fields, except plengths and history.
typedef struct {
  const char **pats;
  const char **subs;
  int count;
  const int *plengths;
  int longest_len;
  char *history;
  int hist_ind;
  int valid_hist_count;
  bool eof_seen;
  char *temp;
} Psed ;

void init_psed(Psed *ppsed, const char **, const char **, int);
const char *next(Psed *);
char last_nth(Psed *, int n);
void destroy_psed(Psed *);

#endif // PSED_H
