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


    if(current_rank == 0) i = 10;


    //Вывод первоначального i каждым процессом
    cout<<"Step 0. i= " <<i<<" on the thread = "<<current_rank<<"\n";


    //Рассылка уникального i всем процессам (i=10) , рассылается из потока 0 во все остальные
    MPI_Bcast(&i , 1, MPI_INT , 0 , MPI_COMM_WORLD);

    //Вывод нового i каждым процессом
    cout<<"Step 1. i = "<<i<<" on the thread = "<<current_rank<<"\n";

    i*= current_rank; //Теперь каждый процесс обладает разным i
    int *m1 = new int [size];

    cout<<"Step 2. i = "<<i<<" on the thread = "<<current_rank<<"\n";//Вывод нового i для каждого процесса


    //создание массива длиной равной количеству потоков (4) в потоке 0 и инициализация его нулями
    if (current_rank==0)
    {
        for(j=0; j<size; j++)
        {
            m1[j] = 0;
        }
            
        for(j=0; j<size; j++)
        {
            cout<<"Step 3. m[i] = "<<m1[j]<<" in the thread "<<0<<"\n"; 
        }
            
    }

    //Сбор всех значений i в массив m1 нулевого процесса
    MPI_Gather(&i, 1, MPI_INT, m1, 1, MPI_INT, 0, MPI_COMM_WORLD); 

    //Вывод массива м1 в потоке ноль с новыми значениями каждого элемента равными i каждого потока.
    if (current_rank==0)
    {
        for(j=0; j<size; j++)
        {
            cout<<"Step 4. m[i] = "<<m1[j]<<" in the thread "<<0<<"\n"; 
        }
            
    }

    //Подготовка каждым из процессов массивов разной длины
    int *m2 = new int [current_rank+1];

    for (j=0;j<current_rank+1;j++)
    {
        m2[j]= current_rank+1;
        cout<<"Step 5. Thread #"<<current_rank<<": m2["<<j<<"] = "<<m2[j]<<"\n"; 
    }

    //создаем массив размеров принимаемых сообщений и массив смещений 
    int *mass_count_r, *mass_disp_r, *m3;
    if (current_rank==0)
    {
        mass_count_r= new int [size];
        mass_disp_r= new int [size];
        mass_count_r[0]= 1;
        mass_disp_r[0]= 0;
        for(int i=1; i<size; i++)
        {
            mass_count_r[i]= i+1;
            mass_disp_r[i]= mass_disp_r[i-1]+mass_count_r[i-1];
        }
        m3 = new int [mass_disp_r[size-1]+mass_count_r[size-1]];
    }
    MPI_Gatherv(m2,current_rank+1,MPI_INT,m3,mass_count_r,mass_disp_r,
                MPI_INT, 0, MPI_COMM_WORLD);

    if (current_rank==0)
    {
        for (j=0;j<mass_disp_r[size-1]+mass_count_r[size-1];j++)
            cout<<"Step 6. m3["<<j<<"]= "<<m3[j]<<"\n";
    }



// Если принимающих процессов несколько, то можно несколько раз, изменяя
// лишь параметр N0, вызвать функцию MPI_Gather (или MPI_Gatherv). Но если
// все процессы данного коммуникатора нуждаются в собранных по кусочкам данных, то проще и эффективнее использовать единственный вызов готовой функции
// MPI_Allgather (или MPI_Allgatherv).

    MPI_Finalize();
    delete m1,m2;
    if (current_rank==0)
    delete m3, mass_count_r, mass_disp_r;
    return 0;

}