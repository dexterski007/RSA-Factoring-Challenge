#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *file_stream;
    char *current_line = NULL;
    size_t line_length = 0;
    long long is_factor_found = 1, divisor, remainder, current_number, factor;
    ssize_t chars_read;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file_stream = fopen(argv[1], "r");
    if (file_stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((chars_read = getline(&current_line, &line_length, file_stream)) != -1) {
        is_factor_found = 1;
        divisor = 2;
        current_number = atoll(current_line);

        while (is_factor_found) {
            remainder = current_number % divisor;
            if (!remainder) {
                factor = current_number / divisor;
                printf("%lld=%lld*%lld\n", current_number, factor, divisor);
                is_factor_found = 0;
            }
            divisor++;
        }
    }

    free(current_line);
    fclose(file_stream);
    exit(EXIT_SUCCESS);
}
