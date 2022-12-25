#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;


int main(int argc , char **argv)
{
    int i;
    i = MPI_Init(&argc , &argv);

    if (i == MPI_SUCCESS){
        cout<<"Successful initialization with code" << "\n" << i <<"\n"  ;

    }else{
        cout<<"Initialization failed with code" << "\n"  << i <<"\n"  ;
    }

    i = MPI_Finalize();

        if (i == MPI_SUCCESS){
        cout<<"Successful MPI_Finalize with code" << "\n"  << i <<"\n"  ;

    }else{
        cout<<"MPI_Finalize failed with code" << "\n"  << i <<"\n"  ;
    }

    return 0;
}