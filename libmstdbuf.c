#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

static void apply(FILE *stream, char *value){
	int mode;
	long int size = 0;
	char *buffer = NULL;
	char *endPtr = NULL;
	size = strtol(value, &endPtr, 10);

	if(size == 0){
		mode = _IONBF;
	} else if(size == -1){
		mode = _IOLBF;
	} else {
		if(value != endPtr){
			buffer = malloc(size);
		}
	}
	setvbuf(stream, buffer, mode, size);
}

static void __attribute((constructor)) mstdbuf(void){
	
	char *i_mode = getenv("_STDBUF_IN");
	char *o_mode = getenv("_STDBUF_OUT");
	char *e_mode = getenv("_STDBUF_ERR");
	
	if(e_mode){
		apply(stderr, e_mode);
	}
	if(i_mode){
		apply(stdin, i_mode);
	}
	if(o_mode){
		apply(stdout, o_mode);
	}	
}
