#include <stdio.h>

#include "include/dyn_arr.h"

typedef struct {
  long long d;
  long long s;
  long long l;
} Map;

typedef struct {
  int ct;
  int cap;
  Map *maps;
} MapList;
CREATE_DYN_ARR_FUNCS_STD_NAMES(MapList, Map, ct, cap, maps)

void read_map(MapList *pmp) {
  while(getchar() != '\n')
    ;
  for(;;){
    Map mp;
    int status = scanf("%lld %lld %lld", &mp.d, &mp.s, &mp.l);
    if(status != 0 && status != EOF)
      push_MapList(pmp, mp);
    else break;
  }
  getchar();
}

typedef struct {
  int ct;
  int cap;
  long long *arr;
} IntList;
CREATE_DYN_ARR_FUNCS_STD_NAMES(IntList, long long, ct, cap, arr)

int main() {
  for(int i = 0; i < 5; ++i) getchar();
  IntList seeds;
  init_dynarr_IntList(&seeds);
  long long cur = 0;
  while(getchar() != '\n') {
    scanf(" %lld", &cur);
    push_IntList(&seeds, cur);
  }
  getchar();
  MapList maps[7];
  for(int i = 0; i < 7; ++i){
    init_dynarr_MapList(&maps[i]);
    read_map(&maps[i]);
  }

  for(long long i = 0; i < 7; ++i) delete_dynarr_MapList(&maps[i]);
  return 0;
}
