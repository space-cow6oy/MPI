#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#define mymessage 99

using namespace std;

int main (int argc, char **argv)
{


    int i, j , number_of_threads , current_rank;
    int size = 4;
    MPI_Init(&argc , &argv);

    
    MPI_Comm_size(MPI_COMM_WORLD , &number_of_threads);
    MPI_Comm_rank(MPI_COMM_WORLD , &current_rank);

    int *mass;

    if(current_rank==0)
    {
        mass = new int [size];
        for(j=0;j<size;j++)
            mass[j] = j*j;

    }

    MPI_Scatter(mass , 1 , MPI_INT , &i , 1 , MPI_INT , 0 , MPI_COMM_WORLD);

    printf("Process #%d received %d\n", current_rank, i);

    MPI_Finalize();
    if (current_rank==0)
        delete mass;

}