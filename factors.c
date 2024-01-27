#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	long long flag = 1, div, rest, number, counter;
	ssize_t nread;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, file)) != -1) {
		flag = 1, div = 2;
		number = atoll(line);
		while (flag) {
			rest = number % div;
			if (!rest) {
				counter = number / div;
				printf("%lld=%lld*%lld\n", number, counter, div);
				flag = 0;
			}
			div++;
		}
	}

	free(line);
	fclose(file);
	exit(EXIT_SUCCESS);
}