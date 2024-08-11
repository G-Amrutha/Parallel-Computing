/* PROGRAM Summation of random float numbers */
#include <stdlib.h>
#define n 10
float values[n+1];
int i;

main() {
  cout.precision(4);
  /* generate n random float numbers between 0 and 10 */
  for (i = 1; i <= n; i++) {
    values[i] = (rand() % 1000)/100.0; /* generating random int in [0, 10) */
    cout << "values[" << i << "] = " << values[i] << endl;
  }
  float sum = 0.0;
  for (i = 1; i <= n; i++)
    sum += values[i];
  cout << "sum = " << sum;
}
