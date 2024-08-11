#include <math.h>
#include<stdlib.h>
#define n 36
#define tolerance 0.009

float A[n+2][n+2], B[n+2][n+2];
int i,j;
int stream higher[n+1], stream lower[n+1];
float change, maxchange;
int count;

spinlock Arrival, Departure;
boolean globaldone;

void Barrier(int i){

    int dummy;
    
    if (i > 1){
        send(higher[i-1],1);
        recv(lower[i],dummy);
       }
           
    if (i < n){
        recv(higher[i],dummy);
        send(lower[i+1],1);
    }
    
}

boolean Aggregate(boolean mydone){
    
    boolean result;
    Lock(Arrival);
    count = count + 1;
    globaldone = globaldone && mydone;
    
    if (count < n)
        Unlock(Arrival);
    
    else
        Unlock(Departure);
    
    Lock(Departure);
    count = count - 1;
    result = globaldone;
    
    if (count > 0)
        Unlock(Departure);
    
    else{
        Unlock(Arrival);
        globaldone = true;
    }
    
    return(result);
    
}

main( ){

    for (i = 0; i <= n+1; i++){
        for (j = 0; j <= n+1; j++)
            A[i][j]= (rand() % 200) / 200.0;
    }

    count = 0;
    Unlock(Arrival);
    Lock(Departure);
    globaldone = true;
    B = A;

    forall i = 1 to n do{

        int j;
        float change, maxchange;
        boolean done;

        do{

            maxchange = 0;

            for (j = 1; j <= n; j++){
                B[i][j] = (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]) / 4;
                change = fabs( B[i][j] - A[i][j] );

                if (change > maxchange)
                    maxchange=change;

            }

            Barrier(i);
            A[i] = B[i];
            done = Aggregate(maxchange<tolerance);

        }

        while (!done);

    }

    cout.precision(3);

    cout << "Amrutha Ginkala- "<< endl ;

    for(i = 0; i <= n + 1; i++){
            cout << "Row:  " << i << "   Result" <<endl;
        for(j = 0; j <= n+1; j++){
            if((j > 0) && (j % 10) == 0){
                cout << endl;
            }
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }
}

