#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc , char **argv)
{

    int size , rank;

    MPI_Init(&argc , &argv);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);

    if(size<2){
        MPI_Abort(MPI_COMM_WORLD , 1);
    }
    else{
        cout<<"SIZE: "<<size<<"\n";
    }

    MPI_Finalize();


    return 0;
}