#include <stdio.h>

#define N 4

long long how_far(long long x, long long t, long long d) {
  if (x >= t) return 0;
  return (t - x) * x;
}

long long get_valid(long long t, long long d) {
  long long l = 0, u = t;
  for(;;) {
    if (l >= u - 1) return l;
    long long m = (l + 1 + u) / 2;
    long long lmd = how_far(m, t, d);
    long long lmnd = how_far(m + 1, t, d);
    if (lmnd > lmd) l = m + 1;
    else u = m; 
  }
}

void get_lb_ub(long long t, long long d, long long *ans) {
  long long disp = ans[0] = ans[1] = get_valid(t, d);
  while(disp > 0) {
    if(how_far(ans[0] - disp, t, d) > d) ans[0] -= disp;
    if(how_far(ans[1] + disp, t, d) > d) ans[1] += disp;
    disp = disp == 1 ? 0 : (disp + 1) / 2;
  }
}

int main() {
  int times[N];
  int dists[N];
  long long time, dist;
  char stime[20], sdist[20];
  for(int i = 0; i < 9; ++i) getchar();
  for(int i = 0; i < N; ++i) scanf("%d", times + i);
  for(int i = 0; i < 10; ++i) getchar();
  for(int i = 0; i < N; ++i) scanf("%d", dists + i);
  long long ans1 = 1;
  long long bounds[2];
  for(int i = 0; i < N; ++i) {
    get_lb_ub(times[i], dists[i], bounds);
    ans1 *= (bounds[1] - bounds[0] + 1);
  }

  printf("%lld\n", ans1);

  int lwt = 0, lwd = 0;
  for(int i = 0; i < N; ++i) {
    lwt += sprintf(stime + lwt, "%d", times[i]);
    lwd += sprintf(sdist + lwd, "%d", dists[i]);
  }
  stime[lwt] = '\0';
  sdist[lwd] = '\0';

  sscanf(stime, "%lld", &time);
  sscanf(sdist, "%lld", &dist);
  get_lb_ub(time, dist, bounds);
  printf("%lld\n", bounds[1] - bounds[0] + 1);

  return 0;
}
