// Sending messages between processes along the pipeline(i-1 -> i -> i+1). MPI_Send and MPI_Recv function

// mpic++ -o test2 test2.cpp
// mpirun -np 5 ./test2

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int size, rank;
    string message = "hello";

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0)  // send a message to the next process
    {
      //MPI_Send(*buf, count, datatype, dest, tag, comm)
        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        cout << "Process " << rank << " SEND message '" << message << "' to process " << rank + 1 << endl;
    }
    else if (rank == size - 1)  // receive a message from the previous processs
    {
      //MPI_Recv(*buf, count, datatype, source, tag, comm, *status)
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        cout << "Process " << rank << " RECEIVE message '" << message << "' from process " << rank - 1 << endl;
    }
    else  // receive a message from the previous processs and then send a message to the next process
    {
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        cout << "Process " << rank << " RECEIVE message '" << message << "' from process " << rank - 1;

        MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        cout << ".  Then SEND message '" << message << "' to process " << rank + 1 << endl;
    }

    MPI_Finalize();
    return 0;
}
