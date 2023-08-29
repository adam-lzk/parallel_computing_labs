//

// mpic++ -o lab3_task1 lab3_task1.cpp
// mpirun -np 4 ./lab3_task1

#include <iostream>
#include <iomanip>
#include <mpi.h>

using namespace std;


int** CreateMatrix(int n)
{
    int** matrix = new int* [n];

    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int [n];
    }

    return matrix;
}


void FillMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = i + j;
        }
    }
}


void PrintMatrix(int** matrix, int n)
{
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl << endl;
    }
}


void DeleteMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];

    delete[] matrix;
}


int main(int argc, char **argv)
{
    int size, rank, *sendbuf, *recvbuf, rootProcessNumber = 0, n = 4;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Status status;

    sendbuf = new int [n];  // !!!
    recvbuf = new int [n];  // !!!

    if (rank == rootProcessNumber)
    {
        int** matrix = CreateMatrix(n);
        int* vector = new int [n];

        FillMatrix(matrix, n);

        PrintMatrix(matrix, n);

        DeleteMatrix(matrix, n);
    }

    delete[] sendbuf;
    delete[] recvbuf;

    MPI_Finalize();
    return 0;
}
