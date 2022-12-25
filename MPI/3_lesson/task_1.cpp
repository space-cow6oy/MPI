#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#define mymessage 99

using namespace std;

int main (int argc, char **argv)
{



    int i , j ,number_of_threads, current_rank;

    MPI_Init(&argc , &argv);

    
    MPI_Comm_size(MPI_COMM_WORLD , &number_of_threads);
    MPI_Comm_rank(MPI_COMM_WORLD , &current_rank);

    int array_size = 10;
    int a[array_size][array_size] , b[array_size] , c[array_size];

    if(current_rank==0)
    {


            for(int i =0 ; i<array_size;i++)
            {
                b[i] = i +1;
                for(int j=0;j<array_size;j++)
                 {
                    a[i][j] = j * 10;
                 }
            } 

            for(int i=1 ; i<number_of_threads;i++)
            {
               int send_to_thread = i; 
               MPI_Send(a , array_size*array_size , MPI_INT , send_to_thread , mymessage , MPI_COMM_WORLD);
               MPI_Send(b , array_size , MPI_INT , send_to_thread , mymessage , MPI_COMM_WORLD); 
               MPI_Send(c , array_size , MPI_INT , send_to_thread , mymessage , MPI_COMM_WORLD); 
               MPI_Send(&array_size , 1 , MPI_INT , send_to_thread , mymessage , MPI_COMM_WORLD); 

            }

            cout<<"First process initialized and sent DATA to other processes\n";
            
    }
    else
    {
        int sending_thread = 0;
        MPI_Recv(a , array_size*array_size , MPI_INT , sending_thread , MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b , array_size , MPI_INT , sending_thread , MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        MPI_Recv(c , array_size , MPI_INT , sending_thread , MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        MPI_Recv(&array_size , 1 , MPI_INT , sending_thread ,MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        
        
        for(i=(current_rank-1)*array_size/(number_of_threads-1);i<(current_rank)*array_size/(number_of_threads-1);i++)
        {
            c[i] = 0;
            for(j=0;j<array_size;j++)
            {
                c[i] += a[i][j]*b[j];
            }
            cout<<"C["<<i+1<<"] = "<<c[i]<<" process: "<<current_rank+1<<" out of "<<number_of_threads<<" processes\n";
        }
    }


    MPI_Finalize();





    return 0;
}