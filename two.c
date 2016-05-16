#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define DELETE_FILE 0

int level = 0, i;
void find(char* path){
	struct dirent *den; 
	struct stat fstat;
	DIR *dir;
	if((dir=opendir(path)) == NULL){
		fprintf(stderr, "\n\n<ERROR> : Not Found DIR\n\n");
		exit(1);
	}
		
	while((den = readdir(dir)) != NULL){
		lstat(den->d_name, &fstat);
		if(S_ISDIR(fstat.st_mode)){
			fprintf(stdout, "%s\n", den->d_name);
			find(den->d_name);
		}else 
			fprintf(stdout, "%s\n", den->d_name);
	}
}

int main(int argc, char* argv[]){
	switch(argc){
		case 1 :
			fprintf(stdout, "\n\n");
			find(".");
			break;
		case 2 :
			fprintf(stdout, "\n\n");
			find(argv[1]);
			break;
		default :
			fprintf(stderr, "\n\nUSE : <Program> <Path>\n\n");
			break;
	}
	return 0;			
}
