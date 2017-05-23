#include <stdio.h>
#include <sys/mman.h>
#include <time.h>

#define PAGE 16384
#define SIZE 4096*PAGE
#define LOOP 1024*1024


int main(){
	clock_t begin = clock();
	void *ptr;	
	for (int i = 0; i < LOOP; i++){
		ptr = mmap(NULL, SIZE, PROT_EXEC | PROT_READ | PROT_EXEC, MAP_ANONYMOUS | MAP_POPULATE, -1, 0);
		munmap(ptr, SIZE);
	}
		

	clock_t end = clock();

	printf("Prealloced mmaped: %Lf\n", (long double) (end - begin)/(1000*1000));

	begin = clock();
	
	for (int i = 0; i < LOOP; i++){
		mmap(NULL, SIZE, PROT_EXEC | PROT_READ | PROT_EXEC, MAP_ANONYMOUS, -1, 0);
		munmap(ptr, SIZE);
	}

	end = clock();

	printf("Not allocated mmapped: %Lf\n", (long double) (end - begin)/(1000*1000));
	return 0;
}


