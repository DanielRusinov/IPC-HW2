#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

#include "cyclicBuf.h"
#include "gen.h"
#include "gen.c"

int main(){
	int shmFd = shm_open( "virtual_memory", O_CREAT | O_RDWR, S_IRWXU );
	if(shmFd == -1){
		perror("Can't open file\n");
		return 1;
	}

	int resize = ftruncate( shmFd, sizeof(struct buffer) );
	if(resize == -1){
		perror("Can't truncate file\n");
		return resize;
	}
	
	struct buffer* memory = mmap( NULL, sizeof(struct buffer), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0 );
	if(memory == NULL){
		perror("Can't mmap the memmory\n");
		return -1;
	}
	
    	memory -> position = 0;
    	uint32_t seed = 0;

    	while(1)
	{
		generate((void*)memory->array[memory -> position %= 1000], seed);
		memory -> position++;
		seed++;
    	}

	return 0;
}
