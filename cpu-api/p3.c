// calling fork(), wait() and exec()
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
		char *myargs[] = {"wc", "p3.c", NULL};
		execvp(myargs[0], myargs);
		printf("this line won't print");
	} else {
		int rc_wait = wait(NULL);
		printf("(pid:%d) (rc_wait:%d) hello, I am parent of %d\n",
				(int) getpid(), rc_wait, rc);
	}
	return 0;
}
