#include <ftmalloc.h>
#include <stdio.h>

void main(void)
{
	void 	*ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	printf("Allocate : %p\n", ptr);
	munmap(ptr, 1024);
	ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	printf("Allocate : %p\n", ptr);
	munmap(ptr, 1024);
}
