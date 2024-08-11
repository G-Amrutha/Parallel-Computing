/* Generate 2000 random integers between 0 and 99 inclusive */
#include <stdlib.h>  /* for using random numbers and memory allocation functions */
int i;

main() {
  for (i = 1; i <= 400; i++)  /* variables cannot be declared in the for control block */
    cout << rand() % 100 << "  " << rand() % 100 << "  " << rand() % 100 << "  " << rand() % 100 << "  " << rand() % 100 << endl;
}

/* C++ style comments starting with // are not supported  */