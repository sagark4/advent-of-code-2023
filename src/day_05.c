#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/dyn_arr.h"

typedef struct {
  long long d;
  long long s;
  long long l;
} Map;

int comp_map(const void *m1v, const void *m2v) {
  Map *m1 = (Map *)m1v;
  Map *m2 = (Map *)m2v;
  if (m1->s < m2->s) return -1;
  if (m1->s > m2->s) return 1;
  return 0;
}

typedef struct {
  int ct;
  int cap;
  Map *maps;
} MapList;
CREATE_DYN_ARR_FUNCS_STD_NAMES(MapList, Map, ct, cap, maps)

void read_map(MapList *pmp) {
  while (getchar() != '\n')
    ;
  for (;;) {
    Map mp;
    int status = scanf("%lld %lld %lld", &mp.d, &mp.s, &mp.l);
    if (status != 0 && status != EOF)
      push_MapList(pmp, mp);
    else
      break;
  }
  getchar();
}

typedef struct {
  int ct;
  int cap;
  long long *arr;
} LongLongList;
CREATE_DYN_ARR_FUNCS_STD_NAMES(LongLongList, long long, ct, cap, arr)

int comp_pair_ll(const void *p1v, const void *p2v) {
  long long *p1 = (long long *)p1v;
  long long *p2 = (long long *)p2v;
  if (*p1 < *p2) return -1;
  if (*p1 > *p2) return 1;
  return 0;
}

long long map(long long s, MapList *pmp) {
  for (int i = 0; i < pmp->ct; ++i) {
    if (pmp->maps[i].s <= s && s < pmp->maps[i].s + pmp->maps[i].l)
      return pmp->maps[i].d + s - pmp->maps[i].s;
  }
  return s;
}

void map_interval(MapList *pml, LongLongList *src, LongLongList *dest) {
  int i = 0;
  int j = 0;
  long long curs, cure;
  curs = src->arr[0];
  cure = src->arr[1];
  while (i < src->ct) {
    while (j < pml->ct && pml->maps[j].s + pml->maps[j].l <= curs) ++j;
    if (j == pml->ct || pml->maps[j].s > cure) {
      push_LongLongList(dest, curs);
      push_LongLongList(dest, cure);
      i += 2;
      curs = src->arr[i];
      cure = src->arr[i + 1];
    } else if (curs < pml->maps[j].s) {
      push_LongLongList(dest, curs);
      push_LongLongList(dest, pml->maps[j].s - 1);
      curs = pml->maps[j].s;
    } else if (cure >= pml->maps[j].s + pml->maps[j].l) {
      push_LongLongList(dest, pml->maps[j].d + curs - pml->maps[j].s);
      push_LongLongList(dest, pml->maps[j].d + pml->maps[j].l - 1);
      curs = pml->maps[j].s + pml->maps[j].l;
    } else {
      push_LongLongList(dest, pml->maps[j].d + curs - pml->maps[j].s);
      push_LongLongList(dest, pml->maps[j].d + cure - pml->maps[j].s);
      i += 2;
      curs = src->arr[i];
      cure = src->arr[i + 1];
    }
  }
}

int main() {
  for (int i = 0; i < 5; ++i) getchar();
  LongLongList seeds;
  init_dynarr_LongLongList(&seeds);
  long long cur = 0;
  while (getchar() != '\n') {
    scanf(" %lld", &cur);
    push_LongLongList(&seeds, cur);
  }
  getchar();
  MapList maps[7];
  for (int i = 0; i < 7; ++i) {
    init_dynarr_MapList(&maps[i]);
    read_map(&maps[i]);
    qsort(maps[i].maps, maps[i].ct, sizeof(Map), comp_map);
  }

  long long ans1 = LLONG_MAX;
  for (int i = 0; i < seeds.ct; ++i) {
    long long s = seeds.arr[i];
    for (int j = 0; j < 7; ++j) s = map(s, &maps[j]);
    ans1 = ans1 < s ? ans1 : s;
  }
  printf("%lld\n", ans1);

  for (int i = 0; i < seeds.ct; i += 2) seeds.arr[i + 1] += seeds.arr[i];
  LongLongList temp;
  init_dynarr_LongLongList(&temp);
  LongLongList *cur_intervals = &seeds;
  LongLongList *dest_intervals = &temp;
  for (int i = 0; i < 7; ++i) {
    qsort(cur_intervals->arr, cur_intervals->ct / 2, 2 * sizeof(long long), comp_pair_ll);
    map_interval(&maps[i], cur_intervals, dest_intervals);
    LongLongList *temp = cur_intervals;
    cur_intervals = dest_intervals;
    dest_intervals = temp;
    dest_intervals->ct = 0;
  }
  qsort(cur_intervals->arr, cur_intervals->ct / 2, 2 * sizeof(long long), comp_pair_ll);
  printf("%lld\n", cur_intervals->arr[0]);

  delete_dynarr_LongLongList(&seeds);
  delete_dynarr_LongLongList(&temp);
  for (long long i = 0; i < 7; ++i) delete_dynarr_MapList(&maps[i]);
  return 0;
}
