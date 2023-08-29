// The simplest MPI program

// mpic++ -o test1 test1.cpp
// mpirun -np 4 ./test1

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    cout << "SIZE = " << size << ", RANK = " << rank << ", TIME = " << MPI_Wtime() << endl;
    MPI_Finalize();
    return 0;
}
