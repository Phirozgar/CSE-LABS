#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd;
	int nums[4] = {10, 20, 30, 40};
	
	//open FIFO for writing
	fd = open("fifo1", O_WRONLY);
	if(fd == -1) {
		perror("open");
		exit(1);
	}
	
	//write integers into FIFO
	if( write(fd, nums, sizeof(nums)) == -1) {
		perror("Write");
		exit(1);
	}
	
	printf("Producer: Wrote 4 integers into FIFO\n");
	
	close(fd);
	return 0;
}
