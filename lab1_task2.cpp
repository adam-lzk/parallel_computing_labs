// sending data from process i to all other processes, where 0 <= i < size

// mpic++ -o lab1_task2 lab1_task2.cpp
// mpirun -np 5 ./lab1_task2

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
    int size, rank;
    string message = "hello";

    int i = 3;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (i > size)
    {
        cout << "Incorrect input. Size must be more than i\n";
        MPI_Finalize();
        return 0;
    }

    for (int j = 0; j < size; j++)
    {
        if (i < j)
        {
            if (rank == i)  // send only
            {
                MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    cout << "Process " << rank << " SEND message '" << message << j << "' to process " << rank + 1 << endl;
            }
            if (rank == j)  // receive only
            {
                MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                    cout << "Process " << rank << " RECEIVE message '" << message << j << "' from process " << rank - 1 << endl;
            }
            if (rank > i && rank < j)  // receive then send
            {
                MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                    cout << "Process " << rank << " RECEIVE message '" << message << j << "' from process " << rank - 1;

                MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                    cout << ".  Then SEND message '" << message << j << "' to process " << rank + 1 << endl;
            }
        }
        else if (i > j)
        {
            if (rank == i)
            {
                MPI_Send(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    cout << "Process " << rank << " SEND message '" << message << j << "' to process " << rank - 1 << endl;
            }
            if (rank == j)
            {
                MPI_Recv(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                    cout << "Process " << rank << " RECEIVE message '" << message << j << "' from process " << rank + 1 << endl;
            }
            if (rank < i && rank > j)
            {
                MPI_Recv(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
                    cout << "Process " << rank << " RECEIVE message '" << message << j << "' from process " << rank + 1;

                MPI_Send(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    cout << ".  Then SEND message '" << message << j << "' to process " << rank - 1 << endl;
            }
        }
    }

    MPI_Finalize();
    return 0;
}

/*  example output (size = 5, i = 3)
Process 3 SEND message 'hello0' to process 2
Process 2 RECEIVE message 'hello0' from process 3.  Then SEND message 'hello0' to process 1
Process 1 RECEIVE message 'hello0' from process 2.  Then SEND message 'hello0' to process 0
Process 0 RECEIVE message 'hello0' from process 1
Process 3 SEND message 'hello1' to process 2
Process 2 RECEIVE message 'hello1' from process 3.  Then SEND message 'hello1' to process 1
Process 1 RECEIVE message 'hello1' from process 2
Process 3 SEND message 'hello2' to process 2
Process 2 RECEIVE message 'hello2' from process 3
Process 3 SEND message 'hello4' to process 4
Process 4 RECEIVE message 'hello4' from process 3
*/
