#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int sum = 0;

    // Paralel for döngüsü. Her thread 'i' değerlerini paylaşır,
    // 'sum' değişkeni reduction ile toplanır.
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < 10; i++) {
        sum += i;
        printf("Thread %d is adding %d | sum = %d\n",
               omp_get_thread_num(), i, sum);
    }

    printf("Final sum = %d\n", sum);
    return 0;
}
