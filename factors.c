#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    long long prime1;
    long long prime2;
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

void factorize(long long n, Factor* factors) {
    long long factor1 = -1, factor2 = -1;

    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            if (factor1 == -1) {
                factor1 = i;
            } else if (factor2 == -1) {
                factor2 = i;
            } else {
                factor1 *= factor2;
                factor2 = i;
            }
            n /= i;
        }
    }

    if (factor1 == -1 || factor2 == -1) {
        factors->prime1 = n;
        factors->prime2 = 1;
    } else {
        factors->prime1 = factor1;
        factors->prime2 = factor2;
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
        Factor factors;

        factorize(number, &factors);

        if (is_prime(factors.prime1) && is_prime(factors.prime2)) {
            printf("%lld=%lld*%lld\n", number, factors.prime1, factors.prime2);
        } else {
            printf("%lld=%lld*1\n", number, factors.prime1);
            printf("%lld=%lld*1\n", number, factors.prime2);
        }
    }

    fclose(file);
    return 0;
}
