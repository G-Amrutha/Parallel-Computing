ARCHITECTURE HYPERCUBE(6); /* 2 ^ 6 = 64 processors*/
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#define n 640 /* dimension - n by n image:  Binoculars640square_new.pgm */
#define m 10 /* number of rows in each partition */
/* declarations to handle reading image header*/
#define header_lines 4
#define MaxGrayComponentValue 255
#define carriage_return '\n'
/* end declarations to handle reading image header*/
int inrows[m+2][n+2];
int outrows[m][n];
MPI_Status status;
int myrank, totalproc, blocksize;
/*int filter[3][3] = {1,1,1,1,1,1,1,1,1}; */ /*subtle smoothing*/
int filter[3][3] = {-1, -1, -1, -1, 8, -1, -1, -1, -1}; /*edge detection*/

void read_image_header() {/*read header characters -these are discarded*/
  int m;
  char c;
    for (m = 1; m <= header_lines; ++m)
    do
    {
      cin >> c;  /* input next character */
    } while (c != carriage_return);
}

void input_image( ) { /*input and partition the image*/
    int image[n+2][n+2];
  int i, j, k, tag, source, dest;
  read_image_header();
  /* input pixel values for image */
  for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++)
      cin >> image[i][j];

  /* send partition to each process */
  for (k = 0; k < totalproc; k++) {
    dest = k;
    tag = 1;
    MPI_Send(&image[k*m][0], blocksize, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
}

int main( ) {
  MPI_Init( );
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  blocksize = (m+2)*(n+2);
  
  int i, j, k, tag, source, dest;
  
    if (myrank == 0){
        input_image( );
    }

  /* receive my block of image*/
  source = 0;
  tag = 1;
  MPI_Recv(&inrows[0][0], blocksize, MPI_INT,
           source, tag, MPI_COMM_WORLD, &status);

  /* apply filter mask to my partition*/
  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++)
      outrows[i-1][j-1] =
        (int) ((filter[0][0]*inrows[i-1][j-1] 
                + filter[0][1]*inrows[i-1][j]
                + filter[0][2]*inrows[i-1][j+1]
                + filter[1][0]*inrows[i][j-1]
                + filter[1][1]*inrows[i][j]
                + filter[1][2]*inrows[i][j+1]
                + filter[2][0]*inrows[i+1][j-1]
                + filter[2][1]*inrows[i+1][j]
                + filter[2][2]*inrows[i+1][j+1]) / 9);
    
    blocksize = m*n;
    dest = 0; tag =2;
    MPI_Send(&outrows[0][0], blocksize, MPI_INT, dest, tag, MPI_COMM_WORLD);
    
    if (myrank == 0) {
    cout << "P2" << endl;
    cout << n << " " << n << endl;
    cout << MaxGrayComponentValue << endl;
    for (k = 0; k < totalproc; k++) {
      source = k; tag = 2;
      MPI_Recv(&outrows[0][0], blocksize,MPI_INT, source, tag, MPI_COMM_WORLD, &status);
      for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
          cout << outrows[i][j];
          if ((j % 20) == 19) {
            cout << endl;
          }
        }
        cout << endl;
      }
    }
  }

  MPI_Finalize( );
}
