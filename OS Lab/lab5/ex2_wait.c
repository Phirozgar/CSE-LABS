#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main() {
	int status;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		printf("\nERROR: child not created");
	else if(pid == 0) {
		printf("\npretty little babyyy");
		exit(0);
	}
	else {
		wait(&status); //causes parent to sleep till child finishes execution
		printf("\n I'm THE Parent");
		printf("\n Child returned %d status", status);
	}
}
