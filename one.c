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
	
	if(chdir(path) < 0){
		fprintf(stderr, "<ERROR> : Not Found Folder\n");
		exit(1);
	}
	
	if((dir = opendir(".")) == NULL){
		fprintf(stderr, "<ERROR> : Can't Open Folder\n");
		exit(1);
	}

	while(den=readdir(dir)){
		if(den->d_ino != DELETE_FILE){
			if(strcmp(den->d_name, ".") || strcmp(den->d_name,".."))
				continue;

			stat(den->d_name, &fstat);		
			for(i = 0;i<level;i++)
				fprintf(stdout, "\t");
		
			if(S_ISDIR(fstat.st_mode)){
				fprintf(stdout, "%s\n", den->d_name);
				level++;
				find(den->d_name);
			}else fprintf(stdout, "%s\n", den->d_name);	
		}
	}
	closedir(dir);
	level--;
	chdir("..");
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
