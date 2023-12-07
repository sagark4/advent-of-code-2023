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

int compare_hands_card_ord(const void *h1, const void *h2, const char *card_ord) {
  Hand **hh1 = (Hand **)h1;
  Hand **hh2 = (Hand **)h2;
  if ((*hh1)->rank < (*hh2)->rank) return -1;
  if ((*hh1)->rank > (*hh2)->rank) return 1;
  int i = 0;
  while (i < 5 && (*hh1)->hand[i] == (*hh2)->hand[i]) ++i;
  if (i == 5) return 0;
  for (int j = 0; j < 13; ++j) {
    if (card_ord[j] == (*hh1)->hand[i]) return -1;
    if (card_ord[j] == (*hh2)->hand[i]) return 1;
  }
  return 0;
}
int compare_hands1(const void *h1, const void *h2) {
  return compare_hands_card_ord(h1, h2, cord);
}

int compare_hands2(const void *h1, const void *h2) {
  return compare_hands_card_ord(h1, h2, cord2);
}

void populate_hand_rank_from_counts(Hand *hand, int *counts) {
    if (counts[0] == 5)
      hand->rank = 0;
    else if (counts[0] == 4)
      hand->rank = 1;
    else if (counts[0] == 3 && counts[1] == 2)
      hand->rank = 2;
    else if (counts[0] == 3)
      hand->rank = 3;
    else if (counts[0] == 2 && counts[1] == 2)
      hand->rank = 4;
    else if (counts[0] == 2)
      hand->rank = 5;
    else
      hand->rank = 6;
}
void populate_ranks(Hand **hands, int sz) {
  for (int k = 0; k < sz; ++k) {
    int counts[13];
    for (int i = 0; i < 13; ++i) {
      counts[i] = 0;
      for (int j = 0; j < 5; ++j)
        if (cord[i] == hands[k]->hand[j]) ++counts[i];
    }
    qsort(counts, 13, sizeof(int), compare);
    populate_hand_rank_from_counts(hands[k], counts);
  }
}

void populate_ranks2(Hand **hands, int sz) {
  for (int k = 0; k < sz; ++k) {
    int counts[13];
    int jct = 0;
    for (int i = 0; i < 13; ++i) {
      counts[i] = 0;
      for (int j = 0; j < 5; ++j)
        if (cord2[i] == hands[k]->hand[j]) ++counts[i];
      if (cord2[i] == 'J') {
        jct = counts[i];
        counts[i] = 0;
      }
    }
    qsort(counts, 13, sizeof(int), compare);
    counts[0] += jct;
    populate_hand_rank_from_counts(hands[k], counts);
  }
}

int main() {
  Hand *hands[N];
  int sz = populate(hands);

  populate_ranks(hands, sz);
  qsort(hands, sz, sizeof(Hand *), compare_hands1);
  int ans = 0;
  for (int i = 0; i < sz; ++i) ans += (hands[i]->bet * (sz - i));
  printf("%d\n", ans);
  populate_ranks2(hands, sz);
  qsort(hands, sz, sizeof(Hand *), compare_hands2);
  ans = 0;
  for (int i = 0; i < sz; ++i) {
    ans += (hands[i]->bet * (sz - i));
    free(hands[i]);
  }
  printf("%d\n", ans);
}
