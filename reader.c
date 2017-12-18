#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "cyclicBuf.h"
#include "gen.h"
#include "gen.c"


int main(){
	int shmFd = shm_open( "virtual_memory", O_RDONLY, 0 );
	if(shmFd == -1){
		perror("Can't open file");
		return 1;
	}

	struct buffer* memory = mmap( NULL, sizeof(struct buffer), PROT_READ, MAP_SHARED, shmFd, 0 );
	if( memory == NULL )
	{
		perror("Can't mmap");
		return 1;
	}
    
	uint64_t position = memory -> position;
	uint64_t seed, prevSeed;

	int i = 0;

	while(1){
		while(memory -> position != position){
			seed = verify((void *)memory->array[position %= 1000]);
			if(seed < 0){
				printf("Error in verifying\n");
			}
			if(memory -> position >= position + 1000){
				printf("Overloaded\n");
				return 1;
			}
			if(i == 0){
				prevSeed = seed;
				i = 1;
			} else if(prevSeed + 1 != seed) {
				printf("Error in seed");
			} else {
				prevSeed++;
			}
		}

		printf("Veryfy array[%ld] - seed:%d\n", position %= 1000,seed);
		position ++;
	}  
	return 0;
}
