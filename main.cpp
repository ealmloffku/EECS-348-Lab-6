#include <fstream>
#include <iostream>
using namespace std;

int readItemFromMatrix(int size, int **matrix, int x, int y)
{
    if (x >= size || y >= size) {
        return -1;
    }
    return matrix[y][x];
}

void setItemInMatrix(int size, int **matrix, int x, int y, int value)
{
    if (x >= size || y >= size) {
        return;
    }
    matrix[y][x] = value;
}

// Free a matrix of a given size
void freeMatrix(int size, int **matrix)
{
    for (int y = 0; y < size; y++)
    {
        free(matrix[y]);
    }
    free(matrix);
}

// Allocate a matrix of a given size
int **allocateMatrix(int size)
{
    // allocate memory for the matrix
    int **matrix = (int **)malloc(size*sizeof(int*));

    // read the matrix
    for (int y = 0; y < size; y++)
    {
        // Allocate memory for this row
        matrix[y] = (int *)malloc(size*sizeof(int));
    }

    return matrix;
}

// Takes two matrices, adds them, and returns the result
int **addMatrices(int size, int **firstMatrix, int **secondMatrix)
{
    int **output = allocateMatrix(size);

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            int first = readItemFromMatrix(size, firstMatrix, x, y);
            int second = readItemFromMatrix(size, secondMatrix, x, y);
            setItemInMatrix(size, output, x, y, first + second);
        }
    }

    return output;
}

// Takes two matrices, subtracts the second matrix from the first matrix, and returns the result
int **subtractMatrix(int size, int **firstMatrix, int **secondMatrix)
{
    int **output = allocateMatrix(size);

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            int first = readItemFromMatrix(size, firstMatrix, x, y);
            int second = readItemFromMatrix(size, secondMatrix, x, y);
            setItemInMatrix(size, output, x, y, first - second);
        }
    }

    return output;
}

// Takes two matrices, multiplies them, and returns the result
int **multiplyMatrices(int size, int **firstMatrix, int **secondMatrix)
{
    int **output = allocateMatrix(size);

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            int sum = 0;
            for (int index = 0; index < size; index++) {
                int firstMatrixRow = readItemFromMatrix(size, firstMatrix, index, y);
                int secondMatrixColumn = readItemFromMatrix(size, firstMatrix, x, index);
                sum += firstMatrixRow*secondMatrixColumn;
            }
            setItemInMatrix(size, output, x, y, sum);
        }
    }

    return output;
}

// Transpose a matrix in place
void transposeMatrix(int size, int **matrix)
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < y; x++)
        {
            int xy = readItemFromMatrix(size, matrix, x, y);
            int yx = readItemFromMatrix(size, matrix, y, x);
            setItemInMatrix(size, matrix, x, y, yx);
            setItemInMatrix(size, matrix, y, x, xy);
        }
    }
}

// Find the max value of the matrix
int maxItemInMatrix(int size, int **matrix)
{
    int max = readItemFromMatrix(size, matrix, 0, 0);
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            int newItem = readItemFromMatrix(size, matrix, x, y);
            if (newItem > max) {
                max = newItem;
            }
        }
    }

    return max;
}

void printMatrix(int size, int **matrix)
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            printf("%-5i ", readItemFromMatrix(size, matrix, x, y));
        }
        printf("\n");
    }
}

// Reads a square matrix into a file. Returns the size of the matrix
int readMatrix(int ***matrix, string fileName)
{
    // open a file in write mode.
    std::fstream matrixFile(fileName, std::ios_base::in);

    // Read the matrix size
    int matrixSize;
    matrixFile >> matrixSize;
    // allocate memory for the matrix
    *matrix = allocateMatrix(matrixSize);

    // read the matrix
    for (int y = 0; y < matrixSize; y++)
    {
        for (int x = 0; x < matrixSize; x++)
        {
            int newItem;
            matrixFile >> newItem;
            setItemInMatrix(matrixSize, *matrix, x, y, newItem);
        }
    }

    // close the opened file.
    matrixFile.close();

    // return the size
    return matrixSize;
}

int main()
{
    // 1. Read values from a file into a matrix:
    int **matrix;
    int matrixSize = readMatrix(&matrix, "matrix.txt");

    // 2. Print a matrix:
    printf("\nMatrix:\n");
    printMatrix(matrixSize, matrix);

    // 3. Add two matrices and place the result in a third matrix; print the result:
    printf("\nMatrix + Matrix:\n");
    int **sum = addMatrices(matrixSize, matrix, matrix);
    printMatrix(matrixSize, sum);
    freeMatrix(matrixSize, sum);

    // 4. Multiply two matrices and place the result in a third matrix; print the result:
    printf("\nMatrix * Matrix:\n");
    int **product = multiplyMatrices(matrixSize, matrix, matrix);
    printMatrix(matrixSize, product);
    freeMatrix(matrixSize, product);

    // 5. Subtract the second matrix from the first matrix and place the result in a third matrix; print the result:
    printf("\nMatrix - Matrix:\n");
    int **result = subtractMatrix(matrixSize, matrix, matrix);
    printMatrix(matrixSize, result);
    freeMatrix(matrixSize, result);

    // 6. Update an element of the first matrix; print the result:
    printf("\nMatrix after updating the center element to 100:\n");
    setItemInMatrix(matrixSize, matrix, 1, 1, 100);
    printMatrix(matrixSize, matrix);

    // 7. Get the max value of the first matrix:
    printf("\nMax item in matrix: ");
    int max = maxItemInMatrix(matrixSize, matrix);
    printf("%d\n", max);

    // 8. Transpose the first matrix; print the result:
    printf("\nTransposed Matrix:\n");
    transposeMatrix(matrixSize, matrix);
    printMatrix(matrixSize, matrix);

    // Free the memory for the matrix
    freeMatrix(matrixSize, matrix);

    return 0;
}
