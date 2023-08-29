// MPI_Scatter function (sending arrays)

// mpic++ -o test5 test5.cpp
// mpirun -np 5 ./test5

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank, rootProcessNumber = 0, *sendbuf, *recvbuf;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    recvbuf = new int [size];

    if (rank == rootProcessNumber)  // create and fill
    {
        sendbuf = new int[size*size];

        for (int i = 0; i < size*size; i++)
        {
            sendbuf[i] = i;
        }
    }

  //MPI_Scatter(*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, root, comm)
    MPI_Scatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, rootProcessNumber, MPI_COMM_WORLD);

    cout << "\nProcess " << rank << " received the vector:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << recvbuf[i] << " ";
    }
    cout << endl;


    if (rank == rootProcessNumber)  // delete
    {
        delete[] sendbuf;
    }

    delete[] recvbuf;

    MPI_Finalize();
    return 0;
}
