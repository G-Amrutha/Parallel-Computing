/* Project 6 - Project 6 - Parallel Numerical Integration Program on 2-D Mesh - Simple Messaage Pass Version*/
/*Students who choose to submit this code must add comments to the code that explain what is going on. */
/* Comments must be brief, but demonstrate that student understands the functionality of program statements.*/
/* Each Student comment must include student's first initial and last name, as per out usual naming convention*/
/* Student will also modify the cout statement at the end of this code to add their name */
/*For examle: */
      /* Sample comment n_turbe */

ARCHITECTURE MESH2(5); /* describes a mesh architecture that is two dimensional and has a size parameter of 5. This means that the mesh configuration is 5x5, meaning that there are 25 processors in total. - a_ginkala */
#include <stdlib.h>
#include <math.h>

#define numproc 25 /* sets the number of processors at 25, which corresponds to the 2-D mesh's dimensions. - a_ginkala */
#define numpoints 30 /* gives the number of integration points for numerical calculations that each processor can have. - a_ginkala */

float a,b,w,globalsum,answer; /* declaration of global variables where 'a' and 'b' refer to integration limits. 'w' refers to step width, 'globalsum' refers to total sum and 'answer' refers to the final answer - a_ginkala */
int i;/* declaration of global iterator - a_ginkala */

float stream inchan[numproc+1]; /* declaration a range of streams for communication between processors. An additional one for the border condition - a_ginkala */

float integral[numproc];/* declares an array to hold each processor's integration results. - a_ginkala */


float f(float t) {/* defines the function to be integrated - a_ginkala */
    return( sqrt(4 - t*t) );
}

void Integrate(int myindex, float *sum){ /* puts the outcome in *sum after carrying out numerical integration on each processor. - a_ginkala */
    float localsum = 0; /* sets the local processor's sum of function values to its initial value. - a_ginkala */
    float t; /* represents the integration process's current evaluation point. - a_ginkala */
    int j; /* used to loop through numpoints - a_ginkala*/
    float start, end, space; /* declatation of local variables for integration start, end points and spacing between points - a_ginkala */

    /* used for communication, takes values from the stream, including start, end, and space, and sends them to the following processor - a_ginkala */
    recv(inchan[myindex], start);
    recv(inchan[myindex], end);
    recv(inchan[myindex], space);
    send(inchan[myindex+1], start);
    send(inchan[myindex+1], end);
    send(inchan[myindex+1], space);

    /* used as a calculation start point. establishes the beginning point of the integration segment for this processor - a_ginkala */
    t = start + myindex*(end-start)/numproc;

    for (j = 1; j <= numpoints; j++) {
        localsum = localsum + f(t);
        t = t + space;
    }

    /* the area under the curve is found by multiplying the cumulative total by the space - a_ginkala */
    localsum = space * localsum;
    *sum = localsum; /* saves the local sum that was calculated in the passed pointer sum - a_ginkala */

}

main( ){
    /* sets up initial conditions and gathers results from processors - a_ginkala */
    a = 0; /* lower bound of integration is set - a_ginkala */
    b = 2; /* upper bound of integration is set - a_ginkala */
    w = (b-a)/(numproc*numpoints); /* calculate step width by establishing the distance between integration points - a_ginkala */

    /* communicates the width, start, and end values to the chain's initial processor - a_ginkala */
    send(inchan[0], a);
    send(inchan[0], b);
    send(inchan[0], w);

    /* the Integrate function is called on each processor in parallel to perform the integration - a_ginkala */
    forall i = 0 to numproc-1 do{
        Integrate(i, &integral[i]);
    }

    /*calculates the overall integral by adding up the output from each processor - a_ginkala */
    for(i=0;i<numproc;i++){
        globalsum = globalsum + integral[i];
    }

    /* adds the correction term to the global total and stores the result in the response - a_ginkala */
    answer = globalsum + w/2*(f(b)-f(a));

    cout<< "Project 6 - Parallel Numerical Integration Program on 2-D Mesh" << ENDL
    << "Simple Message Pass: " <<"Professor's Version "<< ENDL
    <<"Submitted With Comments By <Amrutha Ginkala>"<< ENDL
    << "Answer is: ";
    /* outputs the answer - a_ginkala */
    cout<<answer<<ENDL;
}
