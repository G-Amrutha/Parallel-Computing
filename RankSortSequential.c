/* PROGRAM RankSortSequential */
#include <stdlib.h>
#define n 100
int values[n+1], final[n+1];
int i;

void PutinPlace( int src ) {
  int testval, j, rank;

  testval = values[src];
  j = src;   /* j moves through the whole array */
  rank = 1;  /* position of the first number in the arrays */
  do {
    j = j % n + 1; /* j moves to the next circular position */
    if (testval > values[j] ||
       (testval == values[j] && src > j)) 
       rank = rank + 1;
  } while (j != src);
  final[rank] = testval;  /*put into position*/
}

main() {
  for (i = 1; i <= n; i++)
    values[i] = rand() % 100;  /* initialize values */
    /* cin >> values[i]; */    /* if to initialize with input values */
  for (i = 1; i <= n; i++) {
    cout << values[i] << " "; 
    if (i % 10 == 0) cout << endl;
  }
  cout << endl;
  for (i = 1; i <= n; i++)
    PutinPlace(i);  /* put values[i] in place */
  for (i = 1; i <= n; i++) {
    cout << final[i] << " ";
    if (i % 10 == 0) cout << endl;
  }    
  cout << endl;
}
