// sending data from process i to process j (i >= 0, j < size)

// mpic++ -o lab1_task1 lab1_task1.cpp
// mpirun -np 6 ./lab1_task1

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
    int size, rank;
    string message = "hello";

    int i = 3, j = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (i < j && size > i && size > j)  // if i < j
    {
        if (rank == i)  // send only
        {
            MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                cout << "Process " << rank << " SEND message '" << message << "' to process " << rank + 1 << endl;
        }
        if (rank == j)  // receive only
        {
            MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                cout << "Process " << rank << " RECEIVE message '" << message << "' from process " << rank - 1 << endl;
        }
        if (rank > i && rank < j)  // receive then send
        {
            MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                cout << "Process " << rank << " RECEIVE message '" << message << "' from process " << rank - 1;

            MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                cout << ".  Then SEND message '" << message << "' to process " << rank + 1 << endl;
        }
    }
    else if (i > j && size > i && size > j)  // if i > j
    {
        if (rank == i)
        {
            MPI_Send(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                cout << "Process " << rank << " SEND message '" << message << "' to process " << rank - 1 << endl;
        }
        if (rank == j)
        {
            MPI_Recv(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                cout << "Process " << rank << " RECEIVE message '" << message << "' from process " << rank + 1 << endl;
        }
        if (rank < i && rank > j)
        {
            MPI_Recv(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                cout << "Process " << rank << " RECEIVE message '" << message << "' from process " << rank + 1;

            MPI_Send(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                cout << ".  Then SEND message '" << message << "' to process " << rank - 1 << endl;
        }
    }
    else
    {
        cout << "Incorrect input. Size must be more than i and j. Must be i != j\n";
    }

    MPI_Finalize();
    return 0;
}

/*  example output (size = 8, i = 2, j = 7):
Process 2 SEND message 'hello' to process 3
Process 3 RECEIVE message 'hello' from process 2.  Then SEND message 'hello' to process 4
Process 4 RECEIVE message 'hello' from process 3.  Then SEND message 'hello' to process 5
Process 5 RECEIVE message 'hello' from process 4.  Then SEND message 'hello' to process 6
Process 6 RECEIVE message 'hello' from process 5.  Then SEND message 'hello' to process 7
Process 7 RECEIVE message 'hello' from process 6

    (size = 5, i = 3, j = 0):
Process 3 SEND message 'hello' to process 2
Process 2 RECEIVE message 'hello' from process 3.  Then SEND message 'hello' to process 1
Process 1 RECEIVE message 'hello' from process 2.  Then SEND message 'hello' to process 0
Process 0 RECEIVE message 'hello' from process 1
*/
