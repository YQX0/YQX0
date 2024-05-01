#include <stdio.h>
#include <omp.h>

void comput(float* A, float* B, float* C) {
    int x, y;
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            C[4 * y + x] = A[4 * y + 0] * B[4 * 0 + x] + A[4 * y + 1] * B[4 * 1 + x] +
                A[4 * y + 2] * B[4 * 2 + x] + A[4 * y + 3] * B[4 * 3 + x];
        }
    }
}

int main1() {
    double duration;
    int x, y, n;
    float A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    float B[] = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f,
                 0.9f, 0.10f, 0.11f, 0.12f, 0.13f, 0.14f, 0.15f, 0.16f };
    float C[16];

    duration = omp_get_wtime();
    for (n = 0; n < 1000000; n++)
        comput(A, B, C);
    duration = omp_get_wtime() - duration;
    printf("Result(Serial):\n");
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++)
            printf("%f,", C[y * 4 + x]);
        printf("\n");
    }
    printf("Serial     : %f\n", duration);

    int num_threads[] = { 2, 4, 8, 16 };
    for (int i = 0; i < 4; i++) {
        duration = omp_get_wtime();
#pragma omp parallel for num_threads(num_threads[i])
        for (n = 0; n < 1000000; n++)
            comput(A, B, C);
        duration = omp_get_wtime() - duration;
        printf("Parallel %d : %f\n", num_threads[i], duration);
    }

    printf("Result(Parallel 16):\n");
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++)
            printf("%f,", C[y * 4 + x]);
        printf("\n");
    }

    return 0;
}
