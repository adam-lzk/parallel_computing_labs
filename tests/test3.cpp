// MPI_Barrier function - the program will not continue until all the processes of the communicator make MPI_Barrier call

// mpic++ -o test3 test3.cpp
// mpirun -np 4 ./test3

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    if (rank != -1)  // try rank != 1 (or anything that is not always true) and the program will not work
    {
        MPI_Barrier(MPI_COMM_WORLD);
    }
    else cout << "Oops\nStop the programm (control-C)\n";

    cout << "Process " << rank << endl;

    MPI_Finalize();
    return 0;
}
