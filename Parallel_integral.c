/* PROGRAM NumericalIntegration */
#include <stdlib.h>
#include <math.h>
#define numproc 100 /*number of processes*/
#define numpoints 30 /*number of points per process*/
float a,b,w,globalsum,answer;
int i;
spinlock L;

float f(float t) {
    return( sqrt(4 - t*t) );
}
void Integrate(int myindex){
  float localsum = 0;
  float t;
  int j;
  t = a + myindex*(b-a)/numproc; /*My start position*/
  for (j = 1; j <= numpoints; j++) {
    localsum = localsum + f(t); /*Add next point*/
    t = t + w;
  }
  localsum = w * localsum;
  Lock(L);
  globalsum = globalsum+localsum; /*atomic update*/
  Unlock(L);
}
main( )
{ /*Initialize values of end points “a” and “b”*/
  a=  0.0;
  b = 2.0;
  w = (b-a)/(numproc*numpoints); /*spacing of points*/
  forall i = 0 to numproc-1 do  /*Create processes*/
    Integrate(i);
  answer = globalsum + w/2*(f(b)-f(a)); /*end points*/
  cout.precision(8);
  cout << answer;
}
