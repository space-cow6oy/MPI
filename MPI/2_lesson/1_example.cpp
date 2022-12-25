#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc , char **argv)
{

    int i , size , rank;
    MPI_Init(&argc , &argv);

    MPI_Comm_size(MPI_COMM_WORLD , &size);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);

    cout<< "Hello , I'm process " << rank << " of " << size << " processes\n";
    MPI_Finalize();
    

    return 0;
}