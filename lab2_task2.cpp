// MPI_Scatter function

// mpic++ -o lab2_task2 lab2_task2.cpp
// mpirun -np 4 ./lab2_task2

#include <iostream>
#include <iomanip>
#include <mpi.h>

using namespace std;


int** CreateMatrix(int height, int width)
{
    int** matrix = new int* [height];

    for (int i = 0; i < height; i++)
    {
        matrix[i] = new int [width];
    }

    return matrix;
}


void FillMatrix(int** matrix, int height, int width, int rank)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = rank;
        }
    }
}


int* GetSendbuf(int** rootMatrix, int height, int rank)
{
    int* sendbuf = new int [height];

    for (int i = 0; i < height; i++)
    {
        sendbuf[i] = rootMatrix[i][rank];
    }

    return sendbuf;
}


void InsertColumnIntoMatrix(int** matrix, int* recvbuf, int height, int rank)
{
    for (int i = 0; i < height; i++)
    {
        matrix[i][rank] = recvbuf[i];
    }
}


void PrintMatrix(int** matrix, int height, int width)
{
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl << endl;
    }
}


void DeleteMatrix(int** matrix, int height, int width)
{
    for (int i = 0; i < height; i++)
        delete[] matrix[i];

    delete[] matrix;
}


int main(int argc, char **argv)
{
    int size, rank, *sendbuf, *recvbuf, **rootMatrix, rootProcessNumber = 0, width = 4, height = 3;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Status status;

    sendbuf = new int [height];
    recvbuf = new int [height];

    int** matrix = CreateMatrix(height, width);

    FillMatrix(matrix, height, width, rank);

    if (rank == rootProcessNumber)
    {
        rootMatrix = CreateMatrix(height, size);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < size; j++)
            {
                rootMatrix[i][j] = i;
            }
        }

        for (int i = 0; i < height; i++)
        {
            sendbuf[i] = rootMatrix[i][rank];
        }

        for (int i = 0; i < size; i++)
        {
            MPI_Send(sendbuf, height, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Recv(recvbuf, height, MPI_INT, rootProcessNumber, 0, MPI_COMM_WORLD, &status);

    InsertColumnIntoMatrix(matrix, recvbuf, height, rank);

    cout << "\nProcess " << rank << " has:\n";
    PrintMatrix(matrix, height, width);

    DeleteMatrix(matrix, height, width);

    if (rank == rootProcessNumber)
    {
        DeleteMatrix(rootMatrix, height, size);
        delete[] sendbuf;
    }

    delete[] sendbuf;
    delete[] recvbuf;

    MPI_Finalize();
    return 0;
}


/*  example output (size = 4, width = 4, height = 3):

Process 0 has:

  0   0   0   0

  1   0   0   0

  2   0   0   0


Process 1 has:

  1   0   1   1

  1   1   1   1

  1   2   1   1


Process 2 has:

  2   2   0   2

  2   2   1   2

  2   2   2   2


Process 3 has:

  3   3   3   0

  3   3   3   1

  3   3   3   2


===================================================================================
=   BAD TERMINATION OF ONE OF YOUR APPLICATION PROCESSES
=   PID 54589 RUNNING AT macadam.local
=   EXIT CODE: 6
=   CLEANING UP REMAINING PROCESSES
=   YOU CAN IGNORE THE BELOW CLEANUP MESSAGES
===================================================================================
YOUR APPLICATION TERMINATED WITH THE EXIT STRING: Abort trap: 6 (signal 6)
This typically refers to a problem with your application.
Please see the FAQ page for debugging suggestions

*/
