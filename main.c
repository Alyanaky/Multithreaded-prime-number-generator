#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4
#define RANGE_START 1
#define RANGE_END 1000000

typedef struct {
    int start;
    int end;
} Range;

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

void* generate_primes(void* arg) {
    Range* range = (Range*)arg;
    for (int i = range->start; i <= range->end; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    Range ranges[NUM_THREADS];
    int range_size = (RANGE_END - RANGE_START + 1) / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        ranges[i].start = RANGE_START + i * range_size;
        ranges[i].end = (i == NUM_THREADS - 1) ? RANGE_END : ranges[i].start + range_size - 1;
        pthread_create(&threads[i], NULL, generate_primes, (void*)&ranges[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n");
    return 0;
}
