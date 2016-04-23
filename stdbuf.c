#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <malloc.h>

#define LIB "/libmstdbuf.so" //DONT HARDCODE

#define HELP "STDBUF util\n\
 * it accepts:\n\
  * -iMODE adjust STDIN\n\
  * -oMODE adjust STDOUT\n\
  * -eMODE adjust STDERR\n\
 * MODE could be:\n\
  * 'L' - line buffering\n\
  * '0' - unbuffered\n\
  * n - n bytes\n\
  * -h display this help and exit\n\
* USAGE:\n\
  * tail -f some.log | stdbuf -oL cut -d ' ' -f1\n"


void show_help(){
    printf(HELP);
}
//opt - option 
//T -default value of bufferisation
int get_buf_type(char *opt, int T){
	int ret = T, tmp = 0;
	if(opt[0] == '0'){
		ret = 0;
	} else if (opt[0] == 'L'){
		ret = -1;
	} else if ((tmp = atoi(opt)) > 0){
		ret = tmp;
	}
	return ret;
}

char *get_ld_path(){
	int llen = strlen(LIB);
	char *dir = malloc(PATH_MAX+llen);
	getcwd(dir, PATH_MAX);
	strcat(dir, LIB);
	return dir;
}

int main(int argc, char *argv[]){
	int res = 0;

	int inputT = -1, outputT = -1, errorT = 0;
	while ((res = getopt(argc,argv,"i:o:e:h")) != -1){
		switch(res){
			case 'i': {
				inputT = get_buf_type(optarg, inputT);
				break;
			}
	 		case 'o': {
				outputT = get_buf_type(optarg, outputT);
				break;
			}
			case 'e': {
				errorT = get_buf_type(optarg, errorT);
				break;
			}
			case 'h': {
				show_help();
				return 1;
			break; 
			} 
		}
	}

	argv += optind;
	argc -= optind;
	if(argc < 1){
		fprintf(stderr, "Need at least 1 command to execute\n");
		return 1;
	}

	char *dir = get_ld_path();

	setenv("LD_PRELOAD", dir, 1);

	char *mode = malloc(20);

	sprintf(mode, "%d", inputT);
	setenv("_STDBUF_IN", mode, 1);

	sprintf(mode, "%d", outputT);
	setenv("_STDBUF_OUT", mode, 1);

	sprintf(mode, "%d", errorT);
	setenv("_STDBUF_ERR", mode, 1);

	execvp(argv[0], argv);
	return 0;
}
