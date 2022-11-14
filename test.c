#include <stdio.h>
int x[1000] = {0};
int n;
void solution() {
  for( int i = 1; i <= n; i++) {
    for ( int j = 1; j <= n; j++) {
      if(x[i] == j) printf("| Q ");
      else printf("|   ");
    }
    printf("|\n");
    printf("|___|___|___|___|___|___|___|___|\n");
  }
  printf("______________________________________________________________\n");
}
int check(int v, int k) {
  for (int i = 1; i <= k - 1; i++)
  {
    if (x[i] == v)
      return 0;
    if (x[i] + i == v + k)
      return 0;
    if (x[i] - i == v - k)
      return 0;
  }
  return 1;
}
void try(int k)
{
  for (int v = 1; v <= n; v++)
  {
    if (check(v, k))
    {
      x[k] = v;
      if (k == n)
        solution();
      else
        try(k + 1);
    }
  }
}

int main()
{
  printf("nhap n:");
  scanf("%d", &n);
  try(1);
  return 0;
}