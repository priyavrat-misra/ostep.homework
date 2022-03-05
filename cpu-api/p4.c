// using fork(), wait() and exec() for redirection
#include <stdio.h>  // printf, fprintf, stderr
#include <stdlib.h>  // exit
#include <unistd.h>  // fork, exec*
#include <fcntl.h>  // open, close, STDOUT_FILENO, O_*
#include <sys/wait.h>  // wait

int main(int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		close(STDOUT_FILENO);
		open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		char *myargs[] = {"wc", "p4.c", NULL};
		execvp(myargs[0], myargs);
		// or execlp("wc", "wc", "p4.c", NULL);
	} else {
		wait(NULL);
		execlp("ls", "ls", ".", NULL);
	}
	return 0;
}
/*
 * Note: The child changes the stream (stdout) by associating
 * a file (p4.output) to the file descriptor 1, but it can be
 * seen from the output that it doesn't affect the parent
 */
