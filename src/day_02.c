#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "include/dyn_arr.h"
#include "include/psed.h"

typedef struct {
  int counts[3];
} Play;

void init_play(Play *p) {
  for (int i = 0; i < 3; ++i) p->counts[i] = 0;
}
typedef struct {
  int id;
  int ct;
  int cap;
  Play *game;
} Game;

CREATE_DYN_ARR_FUNCS_STD_NAMES(Game, Play, ct, cap, game)

typedef struct {
  int ct;
  int cap;
  Game *games;
} GameCollection;

CREATE_DYN_ARR_FUNCS_STD_NAMES(GameCollection, Game, ct, cap, games)

Game string_to_play_collection(const char *line) {
  Game game;
  init_dynarr_Game(&game);
  sscanf(line, "%d:", &game.id);
  int pos = 0;
  while (line[pos] != ' ') {
    ++pos;
  }
  ++pos;
  do {
    if (line[pos] == ';') pos += 2;
    Play p;
    init_play(&p);
    do {
      if (line[pos] == ',') pos += 2;
      int count, color;
      sscanf(line + pos, "%d %d", &count, &color);
      for (char c = line[pos]; c != ',' && c != ';' && c != '\0'; c = line[++pos])
        ;
      p.counts[color] = count;
    } while (line[pos] == ',');
    push_Game(&game, p);
  } while (line[pos] == ';');
  return game;
}
int main() {
  const char *pats[4] = {"red", "blue", "green", "Game "};
  const char *subs[4] = {"0", "1", "2", ""};
  Psed psed;
  init_psed(&psed, pats, subs, 4);
  char line[100];
  char ind = 0;
  GameCollection gc;
  init_dynarr_GameCollection(&gc);
  for (const char *nxt = next(&psed); nxt[0] != EOF; nxt = next(&psed)) {
    if (nxt[0] != '\n') {
      strcpy(line + ind, nxt);
      ind += strlen(nxt);
    } else {
      line[ind] = '\0';
      push_GameCollection(&gc, string_to_play_collection(line));
      ind = 0;
    }
  }
  /*
  for(int i = 0; i < gc.ct; ++i) {
    printf("\n\nGame id = %d: ", gc.games[i].id);
    for(int j = 0; j < gc.games[i].ct; ++j) {
      printf("Play #%d: ", j);
      for(int k = 0; k < 3; ++k) {
        int *cts = gc.games[i].game[j].counts;
        printf("Color = %d, count = %d.", k, cts[k]);
      }
    }
  }
  */
  int sum_ids = 0;
  for (int i = 0; i < gc.ct; ++i) {
    int id = gc.games[i].id;
    bool poss = true;
    for (int j = 0; j < gc.games[i].ct; ++j) {
      int *cts = gc.games[i].game[j].counts;
      if (cts[0] > 12 || cts[1] > 14 || cts[2] > 13) {
        poss = false;
        break;
      }
    }
    if (poss) sum_ids += id;
  }
  printf("%d\n", sum_ids);

  int power = 0;
  int mins[3];
  for (int i = 0; i < gc.ct; ++i) {
    for (int j = 0; j < 3; ++j) mins[j] = 0;
    for (int j = 0; j < gc.games[i].ct; ++j) {
      int *cts = gc.games[i].game[j].counts;
      for (int k = 0; k < 3; ++k) mins[k] = mins[k] < cts[k] ? cts[k] : mins[k];
    }
    int prod = mins[0] * mins[1] * mins[2];
    power += prod;
  }
  printf("%d\n", power);

  // Free memory like a nice human.
  for (int i = 0; i < gc.ct; ++i) {
    delete_dynarr_Game(&gc.games[i]);
  }
  delete_dynarr_GameCollection(&gc);
  destroy_psed(&psed);
  return 0;
}
