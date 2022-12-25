#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc , char **argv)
{

    const int array_size = 10;
    int i , j ,number_of_threads, rank , a[array_size][array_size] , b[array_size] , c[array_size];

    for(i =0 ; i<array_size;i++)
    {
        b[i] = i +1;
        for(j=0;j<array_size;j++)
        {
            a[i][j] = j * j;
        }
    } 

    MPI_Init(&argc , &argv);

    MPI_Comm_size(MPI_COMM_WORLD , &number_of_threads);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);

    for(i=rank*array_size/number_of_threads;i<(rank+1)*array_size/number_of_threads;i++)
    {
        c[i] = 0;
        for(j=0;j<array_size;j++)
        {
            c[i] += a[i][j]*b[j];
        }
        cout<<"C["<<i+1<<"] = "<<c[i]<<" process: "<<rank+1<<" out of "<<number_of_threads<<" processes\n";
    }
    MPI_Finalize();


    return 0;
}