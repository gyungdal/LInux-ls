#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX 1024
 
int indent = 0, fileCount, dirCount;
char* cdir;

 
void Scan(char *wd,  int depth){
	struct dirent **items;
	int nitems, i;
	if (chdir(wd) < 0){
		fprintf(stderr, "\n\n\nDIR : %s\n", wd);
		perror("chdir ");
		exit(1);
	}
	fprintf(stdout, "\n\n\nfolder : %s\n", getcwd(cdir, sizeof(char) * MAX));

	nitems = scandir(".", &items, NULL, alphasort);

	for (i = 0; i < nitems; i++){
		struct stat fstat;

		fprintf(stdout, "%s\n",items[i]->d_name);
		if ((!strcmp(items[i]->d_name, ".")) || (!strcmp(items[i]->d_name, "..")))
			continue;


		lstat(items[i]->d_name, &fstat);
		if ((fstat.st_mode & S_IFDIR) == S_IFDIR){
			dirCount++;
			if (indent < (depth-1) || (depth == 0)){
				indent ++;
				Scan(items[i]->d_name, depth);
			}
		} else
		fileCount++;
	}
	indent--;
	chdir("..");
}

int main (int argc, char *argv[]){
	cdir = calloc(sizeof(char), MAX);
	char* now = calloc(sizeof(char), MAX);
	switch(argc){
		case 1 : 
			getcwd(now, MAX);
			Scan(now, 0);
			break;	
		case 2 :
			Scan(argv[1], 0);
			break;	
		default : 
			fprintf(stderr, "<USE> : <Program> <DIR PATH> or <Program>\n");
			break;
	}

	return 0;
}

