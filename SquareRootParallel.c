/* PROGRAM Parallel version of SquareRoot */
/* Figure 2.1 */
#include <stdlib.h>
#include <math.h>
#define n 100
float a[n+1];
int i;

void print(float[] p, int n) { 
  int j;
  for (j = 1; j <= n; j++)
    cout << "[" << j << " : " << p[j] << "] ";
  cout << "\n";
} 

main() {
  cout.precision(4); /* use 4 significant digits for float output */
  for (i = 1; i <= n; i++)
    a[i] = (rand() % 10000)/100.0;
  print(a, n); 
  forall i = 1 to n grouping 10 do  
    a[i] = sqrt(a[i]);
  print(a, n); 
}

