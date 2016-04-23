#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	if(argc < 4) {
		printf("Invalid: %s llen amount_of_symbols msec\n", argv[0]);
		return 1;
	}

	size_t llen = strtoul(argv[1], NULL, 10);
	size_t a = strtoul(argv[2], NULL, 10);
	useconds_t ms = strtoul(argv[3], NULL, 10);
	size_t i = 0;

	while(i < a) {
		printf("+");
		usleep(ms);
		(++i)%llen?0:printf("\n");
	}
}
