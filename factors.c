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
	FILE *stream;
	char *line = NULL;
	size_t length = 0;
	long long check = 1, divi, count, reste, num ;
	ssize_t lineread;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if (stream == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((lineread = getline(&line, &length, stream)) != -1) {
		check = 1, divi = 2;
		num = atoll(line);
		while (check) {
			reste = num % divi;
			if (!reste) {
				count = num / divi;
				printf("%lld=%lld*%lld\n", num, count, divi);
				check = 0;
			}
			divi++;
		}
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}