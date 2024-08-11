ARCHITECTURE TORUS(6); /* Sets up the torus architecture with 6 rows and columns for the processors. - A_Ginkala */
#define m 6 /* Defines the number of rows/columns in the torus architecture. - A_Ginkala */
#define p 8 /* Defines the size of the square partition of the matrices. - A_Ginkala */

/*#define m 8
#define p 6
*/
/*ARCHITECTURE TORUS(12);
#define m 12
#define p 4
*?
/*ARCHITECTURE TORUS(24);
#define m 24
#define p 2
*/
#include <stdlib.h>

typedef float partition[p+1][p+1]; /* Defines a type 'partition' as a 2D array of floats to hold parts of matrices A, B, and C. - A_Ginkala */
partition A[m][m], B[m][m], C[m][m]; /* Declares matrices A, B, and C as arrays of partitions. - A_Ginkala */
partition stream Achan[m][m], stream Bchan[m][m]; /* Declares streams for sending partitions of A and B between processors. - A_Ginkala */
int i,j; /* Loop variables. - A_Ginkala */

/* Function to multiply partitions of matrices A and B, and add the result to partition of C. - A_Ginkala */
void Multiply(int row, int col, value partition myA, value partition myB, partition mainC)
{
  int i,j,k,iter,above,left;
  partition myC = {0}; /* Local partition to store the result of multiplying myA and myB. - A_Ginkala */
  if (row > 0) above = row-1; /* Determines the row of the processor above in the torus. - A_Ginkala */
    else above = m-1;
  if (col > 0) left = col-1; /* Determines the column of the processor to the left in the torus. - A_Ginkala */
    else left = m-1;
  for (iter = 1; iter <= m; iter++) { /* Iterates to cycle through the necessary rotations of partitions. - A_Ginkala */
    send(Achan[row][left], myA); /* Sends myA to the left neighbor. - A_Ginkala */
	  send(Bchan[above][col], myB); /* Sends myB to the neighbor above. - A_Ginkala */
      
      /* Multiplies myA and myB, adding the result to myC. - A_Ginkala */
	  for (i = 1; i <= p; i++)
	   for (j = 1; j <= p; j++)
		  for (k = 1; k <= p; k++)
		    myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j];
	  recv(Achan[row][col], myA); /* Receives the next A partition from the current processor's channel. - A_Ginkala */
	  recv(Bchan[row][col], myB); /* Receives the next B partition from the current processor's channel. - A_Ginkala */
  }
  mainC = myC; /* Copies the result back to the main C matrix. - A_Ginkala */
}

main( ) {

  int k, l;
    /* Initializes matrices A and B with random values. - A_Ginkala */
  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  for (k = 1; k <= p; k++)
	    for (l = 1; l <= p; l++) {
		    A[i][j][k][l] = (rand() % 100)/10.0;
		    B[i][j][k][l] = (rand() % 100)/10.0;
	     }
    
    /* Forks processes to multiply partitions of A and B, adding results to C, for each partition. - A_Ginkala */
  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  fork (@i * m + j)
      Multiply(i, j, A[i][(j+i)%m], B[(i+j)%m][j], C[i][j]);

    /* Waits for all forked processes to complete. - A_Ginkala */
  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  join;
    
/* Prints out the results of the matrix multiplication. - A_Ginkala */
cout << "Multicomputer Matrix Multiply" << ENDL;
cout << "Torus size:     " << m <<  ENDL;
cout << "Partition Size: " << p << ENDL;
cout << "Number of Data elements: "<< m*m*p*p << ENDL;
    
    /* Uncommenting the code below will print the contents of matrix C,
     showing the result of the matrix multiplication. - A_Ginkala */
/*
  cout.precision(4);
  for (i = 0; i < m; i++) {
	 for (j = 0; j < m; j++) {
	  cout << "partition[" << i << ", " << j << "]" << endl;
	  for (k = 1; k <= p; k++) {
		 for (l = 1; l <= p; l++)
		  cout << C[i][j][k][l] << ", ";
	    cout << endl;
	  }
	 }
 }*/
}
