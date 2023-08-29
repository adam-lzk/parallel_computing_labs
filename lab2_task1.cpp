// MPI_Scatter function

// mpic++ -o lab2_task1 lab2_task1.cpp
// mpirun -np 4 ./lab2_task1

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
    int size, rank, **sendbuf, *recvbuf, **rootMatrix, rootProcessNumber = 0, width = 4, height = 3;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    sendbuf = CreateMatrix(size, height);
    recvbuf = new int [height];

    int** matrix = CreateMatrix(height, width);

    FillMatrix(matrix, height, width, rank);

    if (rank == rootProcessNumber)
    {
        rootMatrix = CreateMatrix(height, size);

        for (int i = 0; i < height; i++)  // filling rootMatrix
        {
            for (int j = 0; j < size; j++)
            {
                rootMatrix[i][j] = i;
            }
        }

        for (int i = 0; i < size; i++)  // transplonation
        {
            for (int j = 0; j < height; j++)
            {
                sendbuf[i][j] = rootMatrix[j][i];
            }
        }
    }

    MPI_Scatter(sendbuf, height, MPI_INT, recvbuf, height, MPI_INT, rootProcessNumber, MPI_COMM_WORLD);

    InsertColumnIntoMatrix(matrix, recvbuf, height, rank);

    cout << "\nProcess " << rank << " has:\n";
        for(int i = 0; i < height; i++) cout << recvbuf[i] << " ";
        cout << endl;
    //PrintMatrix(matrix, height, width);

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
