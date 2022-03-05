// using fork(), wait() and exec() for redirection
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		close(STDOUT_FILENO);
		printf("printf from child\n");
	} else {
		wait(NULL);
		printf("printf from parent\n");
	}
	return 0;
}
/*
 * Observation:
 * The child process doesn't print as it's stdout stream
 * was closed, whereas the parent does.
 */
