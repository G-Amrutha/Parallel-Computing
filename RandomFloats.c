/* Generate 2000 random floats between 0.00 and 99.99 inclusive */
#include <stdlib.h>  /* for using random numbers and memory allocation functions */
int i;

main() {
  cout.precision(4); /* use 4 significant digits for float output */
  for (i = 1; i <= 400; i++)  /* variables cannot be declared in the for control block */
    cout << (rand() % 10000)/100.0 << " " << (rand() % 10000)/100.0 << " " << (rand() % 10000)/100.0 << " " 
         << (rand() % 10000)/100.0 << " " << (rand() % 10000)/100.0 << endl;
}

/* C++ style comments starting with // are not supported  */