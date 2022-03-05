// calling fork() and wait()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("(pid:%d) hello world\n", (int) getpid());
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("(pid:%d) hello, I am child\n", (int) getpid());
		int c_wait = waitpid(-1, NULL, 0); 
		printf("c_wait = %d\n", c_wait);
	} else {
		int p_wait = waitpid(rc, NULL, 0);
		printf("(pid:%d) hello, I am parent of %d\n", (int) getpid(), rc);
		printf("p_wait = %d\n", p_wait);
	}
	return 0;
}
/*
 * Observation:
 * waitpid() is useful when there are multiple children processes
 * and the parent need to wait for a particular child to terminate
 */
