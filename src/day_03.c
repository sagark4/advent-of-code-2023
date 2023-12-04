#include <stdbool.h>
#include <stdio.h>

#include "include/dyn_arr.h"

#define R 140
#define C 140

typedef struct {
  int r;
  int c;
} Point;

typedef struct {
  int ct;
  int cap;
  Point *points;
} PointList;

CREATE_DYN_ARR_FUNCS_STD_NAMES(PointList, Point, ct, cap, points)

bool is_digit(char c) {
  return '0' <= c && c <= '9';
}

bool is_valid(int r, int c) { return 0 <= r && r < R && 0 <= c && c < C; }

PointList get_valid_neighbors(int r, int c) {
  PointList pl;
  init_dynarr_PointList(&pl);
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (is_valid(r + i, c + j)) {
        Point p;
        p.r = r + i;
        p.c = c + j;
        push_PointList(&pl, p);
      }
    }
  }
  return pl;
}

int main() {
  char arr[R][C];
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      arr[i][j] = getchar();
    }
    getchar();
  }

  bool adj_symb[R][C];
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      adj_symb[i][j] = false;
    }
  }

  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if(!(is_digit(arr[i][j]) || arr[i][j] == '.')) {
        PointList vn = get_valid_neighbors(i, j);
        for(int k = 0; k < vn.ct; ++k) adj_symb[vn.points[k].r][vn.points[k].c] = true;
        delete_dynarr_PointList(&vn);
      }
    }
  }

  int part1 = 0;
  for (int i = 0; i < R; ++i) {
    int cur = 0;
    bool cur_flag = false;
    int j = 0;
    while(j < C) {
      char c = arr[i][j];
      if(is_digit(c)) {
        cur = cur * 10 + (c - '0');
        cur_flag = cur_flag || adj_symb[i][j];
      }
      if(!is_digit(c) || j == C - 1) {
        if(cur_flag) part1 += cur;
        cur = 0;
        cur_flag = false;
      }
      ++j;
    }
  }
  printf("%d\n", part1);
  
  return 0;
}
