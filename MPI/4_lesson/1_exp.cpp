#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#define mymessage 99

using namespace std;

int main (int argc, char **argv)
{



    int number_of_threads, current_rank , prev_rank;

    MPI_Init(&argc , &argv);

    
    MPI_Comm_size(MPI_COMM_WORLD , &number_of_threads);
    MPI_Comm_rank(MPI_COMM_WORLD , &current_rank);

    cout<<"CR: "<<current_rank<<" NOT: "<<(current_rank+1)%number_of_threads <<" CRNO: "<< (current_rank+number_of_threads-1)%number_of_threads  <<"\n";

    MPI_Sendrecv(&current_rank , 1 , MPI_INT , (current_rank+1)%number_of_threads , (current_rank+1)%number_of_threads ,
                    &prev_rank , 1 , MPI_INT , (current_rank+number_of_threads-1)%number_of_threads , current_rank,
                    MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                

    cout<< current_rank <<" Recieve message " <<prev_rank<<"\n";


    MPI_Finalize();
    return 0;
}