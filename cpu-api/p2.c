// calling fork() and wait()
#include <stdio.h>  // printf, fprintf, stderr
#include <stdlib.h>  // exit
#include <unistd.h>  // fork, getpid
#include <sys/wait.h>  // wait

int main(int argc, char *argv[]) {
	printf("(pid:%d) hello world\n", (int) getpid());
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("(pid:%d) hello, I am child\n", (int) getpid());
	} else {
		int rc_wait = wait(NULL);
		printf("(pid:%d) (rc_wait:%d) hello, I am parent of %d\n",
				(int) getpid(), rc_wait, rc);
	}
	return 0;
}
