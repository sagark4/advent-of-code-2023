#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

const char *cord = "AKQJT98765432";
const char *cord2 = "AKQT98765432J";
typedef struct {
  char hand[6];
  int bet;
  int rank;
  long long hval;
} Hand;

int populate(Hand **hands) {
  int i = 0, st;
  do {
    Hand *hand = (Hand *)malloc(sizeof(Hand));
    st = scanf("%s %d\n", hand->hand, &hand->bet);
    hands[i] = hand;
    ++i;
  } while (st == 2);
  return i - 1;
}

int compare(const void *a, const void *b) {
  int ia = *((int *)a);
  int ib = *((int *)b);

  return ib - ia;
}

int compare_hands1(const void *h1, const void *h2) {
  Hand **hh1 = (Hand **) h1;
  Hand **hh2 = (Hand **) h2;
  if((*hh1)->rank < (*hh2)->rank) return -1;
  if((*hh1)->rank > (*hh2)->rank) return 1;
  int i = 0;
  while(i < 5 && (*hh1)->hand[i] == (*hh2)->hand[i]) ++i;
  if(i == 5) return 0;
  for(int j = 0; j < 13; ++j) {
    if(cord[j] == (*hh1)->hand[i]) return -1;
    if(cord[j] == (*hh2)->hand[i]) return 1;
  }
  return 0;
}

void populate_ranks(Hand **hands, int sz) {
  for (int k = 0; k < sz; ++k) {
    int counts[13];
    for (int i = 0; i < 13; ++i) {
      counts[i] = 0;
      for (int j = 0; j < 5; ++j)  if (cord[i] == hands[k]->hand[j]) ++counts[i];
    }
    qsort(counts, 13, sizeof(int), compare);
    if(counts[0] == 5) hands[k]->rank = 0;
    else if(counts[0] == 4) hands[k]->rank = 1;
    else if(counts[0] == 3 && counts[1] == 2) hands[k]->rank = 2;
    else if(counts[0] == 3) hands[k]->rank = 3;
    else if(counts[0] == 2 && counts[1] == 2) hands[k]->rank = 4;
    else if(counts[0] == 2) hands[k]->rank = 5;
    else hands[k]->rank = 6;
  }
}

int main() {
  Hand *hands[N];
  int sz = populate(hands);

  populate_ranks(hands, sz);
  qsort(hands, sz, sizeof(Hand *), compare_hands1);
  int ans1 = 0;
  for (int i = 0; i < sz; ++i) {
    ans1 += (hands[i]->bet * (sz - i));
    // printf("%s %d %d\n", hands[i]->hand, hands[i]->bet, hands[i]->rank);
    free(hands[i]);
  }
  printf("%d\n", ans1);
}
