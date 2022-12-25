#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc , char **argv)
{

    const int v_size = 10;
    int size , rank , i , j , l , a[v_size][v_size] , b[v_size] , c[v_size];

    for(i=0;i<v_size;i++)
    {
        b[i] = i+1;
        for(j=0;j<v_size;j++)
        {
            a[i][j] = (i+1)*(j+1);
        }
    }

    MPI_Init(&argc , &argv);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);


    for(i=rank*10/size;i<(rank+1)*10/size;i++)
    {
        c[i] = 0;
        for(j=0;j<v_size;j++)
        {
            c[i] += a[i][j]*b[j];
        }
        cout<<"C["<<i+1<<"] = "<<c[i]<<" process: "<<rank+1<<" out of "<<size<<" processes\n";
    }
    MPI_Finalize();


    return 0;
}