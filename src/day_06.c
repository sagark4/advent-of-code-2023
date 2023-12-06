#include <stdio.h>

#define N 4

int main() {
  int times[N];
  int dists[N];
  long long time, dist;
  char stime[20], sdist[20];
  for(int i = 0; i < 9; ++i) getchar();
  for(int i = 0; i < N; ++i) scanf("%d", times + i);
  for(int i = 0; i < 10; ++i) getchar();
  for(int i = 0; i < N; ++i) scanf("%d", dists + i);

  int lwt = 0, lwd = 0;
  for(int i = 0; i < N; ++i) {
    lwt += sprintf(stime + lwt, "%d", times[i]);
    lwd += sprintf(sdist + lwd, "%d", dists[i]);
  }
  stime[lwt] = '\0';
  sdist[lwd] = '\0';

  sscanf(stime, "%lld", &time);
  sscanf(sdist, "%lld", &dist);

  return 0;
}
