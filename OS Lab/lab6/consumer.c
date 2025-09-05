#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd;
	int nums[4];
	
	//open FIFO for reading
	fd = open("fifo1", O_RDONLY);
	if(fd == -1) {
		perror("open");
		exit(1);
	}
	
	//read integers from FIFO
	if( read(fd, nums, sizeof(nums)) == -1) {
		perror("Write");
		exit(1);
	}
	
	printf("Consumer: Read 4 integers from FIFO\n");
	for(int i = 0; i < 4; i++) {
		printf("%d" , nums[i]);
	}
	
	close(fd);
	return 0;
}
