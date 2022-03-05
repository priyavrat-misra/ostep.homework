#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int x = 100;
	printf("(%d) x = %d, a = %d\n", (int) getpid(), x, &x);
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		++x;
		printf("(%d) x = %d, a = %d\n", (int) getpid(), x, &x);
	} else {
		wait(NULL);
		printf("(%d) x = %d, a = %d\n", (int) getpid(), x, &x);
	}
	return 0;
}
/*
 * Observation:
 * Even though both process' (parent & child) 'x' has the same address,
 * making changes in one doesn't lead to any changes in the other,
 * the reason being, they have the same virtual address but not physical.
 */
