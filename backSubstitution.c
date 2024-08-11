/* PROGRAM BackSubstitution */
#define n 50
float A[n+1][n+1];
float B[n+1], x[n+1];
float stream pipechan[n+2];
int i; 

void PipeProcess(int i) { /*Solves Equation i to compute x[i]*/
    int j;
    float sum, xvalue; 
    sum = 0;
    for (j = 1; j <= i-1; j++) { recv(pipechan[i],xvalue); /*Read x[j] from left*/
        send(pipechan[i+1],xvalue); /*Send x[j] to right*/
        sum = sum + A[i][j]*xvalue;
    }
    x[i] = (B[i]-sum) / A[i][i]; /*Compute x[i]*/
    send(pipechan[i+1],x[i]); /*Send x[i] to right*/
}

main( ) { ... /*Initialize arrays A and B*/
    forall i = 1 to n do /*Create pipeline processes*/
    PipeProcess(i);
}
