/* PROGRAM Summation of float numbers input from keyboard */
#include <stdlib.h>
#define n 10    /* macro definition: n is now alias of 10, making code more readable */
float values[n+1];
int i;

main() {
  /* read n float numbers from keyboard */
  for (i = 1; i <= n; i++)
    cin >> values[i];  /* C++ style input */
  float sum = 0;
  for (i = 1; i <= n; i++)
    sum += values[i];
  cout.precision(4);
  cout << "sum = " << sum;  /* C++ style output */
}
