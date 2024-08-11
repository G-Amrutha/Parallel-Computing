/* PROGRAM BackSubstitution */

#define n 10
float A[n+1][n+1];
float B[n+1], x[n+1];
float stream pipechan[n+2];
int i;
int j;

void PipeProcess(int i){
    
    int j;
    int y=0;
    /*change y for task 1 */
    float sum, xvalue;
    sum = 0;
    /*set flag true for breaking down into stream */
    for (j = 1; j <= i-1; j++) {
        recv(pipechan[i],xvalue); /*Read x[j] from left*/
        /*step into a process and change y after lines you wish */
        if(y>0){
            cout<<"break the stream in process" <<i<<"\n";
            cout<<"x:"<<j<<" "<<xvalue<<" ";
        }
        send(pipechan[i+1],xvalue); /*Send x[j] to right*/
        sum = sum + A[i][j]*xvalue;
    }
    x[i] = (B[i]-sum) / A[i][i]; /*Compute x[i]*/
    send(pipechan[i+1],x[i]); /*Send x[i] to right*/
}

main( )
{
    /*Initialize arrays A and B*/
    float f;
    
    for(i=1;i<=n;i++){
        for(j=1;j<=i;j++){
            if (j<=i) A[i][j] = (float)j;
            else A[i][j]=0.0;
        }
    }
    
    for (i=1;i<=n;i++){
        if (i<=n) B[i]=10.0+i;
        else B[i]= 0.0;
    }
    
    forall i = 1 to n do{
        PipeProcess(i);
    }
    /* now the x array must be solved */
    /*for (j=1;j<=n;j++){
        cout << "x[" << j << "] = " << x[j] << endl;
    }*/
}

