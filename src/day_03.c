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

typedef struct {
  int ct;
  int cap;
  int *arr;
} IntList;
CREATE_DYN_ARR_FUNCS_STD_NAMES(IntList, int, ct, cap, arr)

bool is_digit(char c) { return '0' <= c && c <= '9'; }

bool is_valid(int r, int c) { return 0 <= r && r < R && 0 <= c && c < C; }

bool point_list_contains(PointList *ppl, Point p) {
  for(int i = 0; i < ppl->ct; ++i) {
    if(p.r == ppl->points[i].r && p.c == ppl->points[i].c) return true;
  }
  return false;
}
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

void push_valid_unique_neighbors_onto(int r, int c, PointList *ppl) {
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (is_valid(r + i, c + j)) {
        Point p;
        p.r = r + i;
        p.c = c + j;
        if(!point_list_contains(ppl, p)) push_PointList(ppl, p);
      }
    }
  }
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
      if (!(is_digit(arr[i][j]) || arr[i][j] == '.')) {
        PointList vn = get_valid_neighbors(i, j);
        for (int k = 0; k < vn.ct; ++k) adj_symb[vn.points[k].r][vn.points[k].c] = true;
        delete_dynarr_PointList(&vn);
      }
    }
  }

  int part1 = 0;
  for (int i = 0; i < R; ++i) {
    int cur = 0;
    bool cur_flag = false;
    int j = 0;
    while (j < C) {
      char c = arr[i][j];
      if (is_digit(c)) {
        cur = cur * 10 + (c - '0');
        cur_flag = cur_flag || adj_symb[i][j];
      }
      if (!is_digit(c) || j == C - 1) {
        if (cur_flag) part1 += cur;
        cur = 0;
        cur_flag = false;
      }
      ++j;
    }
  }
  printf("%d\n", part1);

  int part2 = 0;
  // This should ideally be a hash table.
  IntList gear_neighbors[R][C];
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      init_dynarr_IntList(&gear_neighbors[i][j]);
    }
  }

  for (int i = 0; i < R; ++i) {
    int cur = 0;
    PointList cur_neighs;
    init_dynarr_PointList(&cur_neighs);
    int j = 0;
    while (j < C) {
      char c = arr[i][j];
      if (is_digit(c)) {
        cur = cur * 10 + (c - '0');
        push_valid_unique_neighbors_onto(i, j, &cur_neighs);
      }
      if (!is_digit(c) || j == C - 1) {
        for (int k = 0; k < cur_neighs.ct; ++k) {
          Point p = cur_neighs.points[k];
          if (arr[p.r][p.c] == '*') push_IntList(&gear_neighbors[p.r][p.c], cur);
        }
        cur_neighs.ct = 0;
        cur = 0;
      }
      ++j;
    }
  }
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (gear_neighbors[i][j].ct == 2)
        part2 += gear_neighbors[i][j].arr[0] * gear_neighbors[i][j].arr[1];
    }
  }
  printf("%d\n", part2);
  return 0;
}
