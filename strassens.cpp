#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

int** allocateMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size]();
    }
    return matrix;
}

void deallocateMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void addMatrix(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    
    int** A11 = allocateMatrix(newSize);
    int** A12 = allocateMatrix(newSize);
    int** A21 = allocateMatrix(newSize);
    int** A22 = allocateMatrix(newSize);

    int** B11 = allocateMatrix(newSize);
    int** B12 = allocateMatrix(newSize);
    int** B21 = allocateMatrix(newSize);
    int** B22 = allocateMatrix(newSize);

    int** P = allocateMatrix(newSize);
    int** Q = allocateMatrix(newSize);
    int** R = allocateMatrix(newSize);
    int** S = allocateMatrix(newSize);
    int** T = allocateMatrix(newSize);
    int** U = allocateMatrix(newSize);
    int** V = allocateMatrix(newSize);

    int** temp1 = allocateMatrix(newSize);
    int** temp2 = allocateMatrix(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    addMatrix(A11, A22, temp1, newSize);
    addMatrix(B11, B22, temp2, newSize);
    strassen(temp1, temp2, P , newSize);

    addMatrix(A21, A22, temp1, newSize);
    strassen(temp1, B11, Q , newSize);

    subtractMatrix(B12, B22, temp2, newSize);
    strassen(A11, temp2, R, newSize);

    subtractMatrix(B21, B11, temp2, newSize);
    strassen(A22, temp2, S, newSize);

    addMatrix(A11, A12, temp1, newSize);
    strassen(temp1, B22, T, newSize);

    subtractMatrix(A21, A11, temp1, newSize);
    addMatrix(B11, B12, temp2, newSize);
    strassen(temp1, temp2, U, newSize);

    subtractMatrix(A12, A22, temp1, newSize);
    addMatrix(B21, B22, temp2, newSize);
    strassen(temp1, temp2, V, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = P[i][j] + S[i][j] - T[i][j] + V[i][j];
            C[i][j + newSize] = R[i][j] + T[i][j];
            C[i + newSize][j] = Q[i][j] + S[i][j];
            C[i + newSize][j + newSize] = P[i][j] - Q[i][j] + R[i][j] + U[i][j];
        }
    }

    deallocateMatrix(A11, newSize);
    deallocateMatrix(A12, newSize);
    deallocateMatrix(A21, newSize);
    deallocateMatrix(A22, newSize);
    deallocateMatrix(B11, newSize);
    deallocateMatrix(B12, newSize);
    deallocateMatrix(B21, newSize);
    deallocateMatrix(B22, newSize);

    deallocateMatrix(P, newSize);
    deallocateMatrix(Q, newSize);
    deallocateMatrix(R, newSize);
    deallocateMatrix(S, newSize);
    deallocateMatrix(T, newSize);
    deallocateMatrix(U, newSize);
    deallocateMatrix(V, newSize);

    deallocateMatrix(temp1, newSize);
    deallocateMatrix(temp2, newSize);
}

int main() {
    srand(time(0));
    ofstream avgTimeFile("AnalysisStrassen.txt");

    for (int size = 2; size <= 1024 ; size *= 2) {
        double totalDuration = 0.0;

        for (int n = 0; n < 100; n++) {
            int** A = allocateMatrix(size);
            int** B = allocateMatrix(size);
            int** C = allocateMatrix(size);

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    A[i][j] = rand() % size;
                    B[i][j] = rand() % size;
                }
            }

            clock_t start = clock();
            strassen(A, B, C, size);
            clock_t end = clock();

            double duration = double(end - start) * 1e6 / CLOCKS_PER_SEC;
            totalDuration += duration;

            deallocateMatrix(A, size);
            deallocateMatrix(B, size);
            deallocateMatrix(C, size);
        }

        avgTimeFile << size << " -> " << totalDuration / 100 << " microseconds" << endl;
    }

    avgTimeFile.close();
    return 0;
}
