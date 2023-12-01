#include <stdio.h>

int first_d = -1;
int last_d = -1;

int first_wd = -1;
int last_wd = -1;
char c1, c2, c3, c4;

int sum1 = 0;
int sum2 = 0;

void process1(char c) {
  if (c == '\n') {
    sum1 += 10 * first_d + last_d;
    first_d = -1;
    last_d = -1;
    return;
  }
  if ('0' <= c && c <= '9') {
    int i = c - '0';
    if (first_d == -1) {
      first_d = last_d = i;
    } else {
      last_d = i;
    }
  }
}

void cycle(char c) {
  c1 = c2;
  c2 = c3;
  c3 = c4;
  c4 = c;
}

void process2(char c) {
  if (c == '\n') {
    sum2 += 10 * first_wd + last_wd;
    first_wd = -1;
    last_wd = -1;
    c1 = c2 = c3 = c4 = -1;
    return;
  }
  int parsed = -1;
  switch (c) {
    case 'e':
      if (c3 == 'o' && c4 == 'n') parsed = 1;
      if (c1 == 't' && c2 == 'h' && c3 == 'r' && c4 == 'e') parsed = 3;
      if (c2 == 'f' && c3 == 'i' && c4 == 'v') parsed = 5;
      if (c2 == 'n' && c3 == 'i' && c4 == 'n') parsed = 9;
      break;

    case 'o':
      if (c3 == 't' && c4 == 'w') parsed = 2;
      break;

    case 'r':
      if (c2 == 'f' && c3 == 'o' && c4 == 'u') parsed = 4;
      break;

    case 'x':
      if (c3 == 's' && c4 == 'i') parsed = 6;
      break;

    case 'n':
      if (c1 == 's' && c2 == 'e' && c3 == 'v' && c4 == 'e') parsed = 7;
      break;

    case 't':
      if (c1 == 'e' && c2 == 'i' && c3 == 'g' && c4 == 'h') parsed = 8;
      break;
  }
  int i = c - '0';
  if (0 <= i && i <= 9) {
    parsed = i;
  }

  cycle(c);
  if (parsed >= 0) {
    if (first_wd == -1) {
      first_wd = last_wd = parsed;
    } else {
      last_wd = parsed;
    }
  }
}

int main() {
  char c;
  c1 = c2 = c3 = c4 = (char)-1;
  while ((c = getchar()) != EOF) {
    process1(c);
    process2(c);
  }
  printf("%d\n", sum1);
  printf("%d\n", sum2);
}
