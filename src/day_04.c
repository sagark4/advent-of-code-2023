#include <stdbool.h>
#include <stdio.h>

int main() {
  int ans = 0;
  char c = getchar();
  int copies[204];
  for (int i = 0; i < 204; ++i) copies[i] = 1;
  int cid = 0;
  while (c == 'C') {
    getchar();
    getchar();
    getchar();
    int id, wins[10], cands[25];
    scanf("%d:", &id);
    int count = 0;
    for (int i = 0; i < 10; ++i) scanf("%d ", wins + i);
    getchar();
    for (int i = 0; i < 25; ++i) scanf("%d", cands + i);
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 25; ++j) {
        if (wins[i] == cands[j]) ++count;
      }
    }
    for (int i = 0; i < count && cid + 1 + i < 204; ++i) copies[cid + 1 + i] += copies[cid];
    if (count) ans += 1 << (count - 1);
    getchar();
    c = getchar();
    ++cid;
  }
  printf("%d\n", ans);
  ans = 0;
  for (int i = 0; i < 204; ++i) ans += copies[i];
  printf("%d\n", ans);
  return 0;
}
