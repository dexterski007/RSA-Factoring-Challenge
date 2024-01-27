#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    long long prime;
    int power;
} Factor;

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

void factorize(long long n, Factor factors[], int* num_factors) {
    *num_factors = 0;
    if (n <= 1) return;

    // Factorization using trial division
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            if (*num_factors < 2) {
                factors[*num_factors].prime = i;
                factors[*num_factors].power = 1;
                (*num_factors)++;
            } else {
                factors[0].power *= factors[1].prime;
                factors[1] = factors[*num_factors - 1];
                (*num_factors)--;
            }
            n /= i;
        }
    }
    if (n > 1) {
        if (*num_factors < 2) {
            factors[*num_factors].prime = n;
            factors[*num_factors].power = 1;
            (*num_factors)++;
        } else {
            factors[0].power *= factors[1].prime;
            factors[1].prime = n;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    long long number;
    while (fscanf(file, "%lld", &number) != EOF) {
        Factor factors[2];
        int num_factors;

        factorize(number, factors, &num_factors);

        printf("%lld=", number);
        for (int i = 0; i < num_factors; i++) {
            printf("%lld", factors[i].prime);
            if (i < num_factors - 1) {
                printf("*");
            }
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}
