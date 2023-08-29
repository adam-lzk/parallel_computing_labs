// MPI_Scatter function

// P0  A B C        P0  A - -
// P1  - - -   ->   P1  B - -
// P2  - - -        P2  C - -

// mpic++ -o test4 test4.cpp
// mpirun -np 5 ./test4

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank, rootProcessNumber = 0, *sendbuf, recvbuf;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    if (rank == rootProcessNumber)
    {
        sendbuf = new int [size];

        for (int i = 0; i < size; i++)
        {
           sendbuf[i] = i*i;
        }
    }

  //MPI_Scatter(*sendbuf, sendcount, sendtype, *recvbuf, recvcount, recvtype, root, comm)
    MPI_Scatter(sendbuf, 1, MPI_INT, &recvbuf, 1, MPI_INT, rootProcessNumber, MPI_COMM_WORLD);

    cout << "Process " << rank << " received the value " << recvbuf << endl;

    if (rank == rootProcessNumber)
    {
        delete[] sendbuf;
    }

    MPI_Finalize();
    return 0;
}
