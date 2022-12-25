#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#define mymessage 99

using namespace std;

int main (int argc, char **argv)
{
int number_of_threads, current_thread;
MPI_Status status;
MPI_Init(&argc, &argv);



MPI_Comm_size(MPI_COMM_WORLD, &number_of_threads);
MPI_Comm_rank(MPI_COMM_WORLD, &current_thread);




if (number_of_threads<2) //Досрочный выход, если процесс всего один
{
cout<<"Error: too few processes";
MPI_Finalize();
exit(1);
}

int i= (current_thread+1)*10;

cout<<"Before sending: i= "<<i<<" on current_thread: " <<current_thread+1<<"\n";
if (current_thread==0)
{

MPI_Send(&i, 1, MPI_INT, 1, mymessage, MPI_COMM_WORLD);
}




if (current_thread==1)
{
MPI_Recv(&i, 1, MPI_INT, MPI_ANY_SOURCE,
MPI_ANY_TAG, MPI_COMM_WORLD, &status);
}
cout<<"After sending: i= "<<i<<" on current_thread: " <<current_thread+1<<"\n";

// if (rank==1)
// printf
// ("status.MPI_SOURCE=%d\nstatus.MPI_TAG=%d\nstatus.MPI_ERROR=%s",
// status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
MPI_Finalize();
return 0;
}