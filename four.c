#include <stdio.h>
#include <sys/stat.h> 
#include <dirent.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#define MAX_SIZE 1024
 
int indent = 0; 
char cdir[MAX_SIZE];
 
void Scandir(char *wd, int depth);
 
int main(int argc, char *argv[]){
	switch(argc){
		case 1 :
			Scandir(".", 0);
			break;
		case 2 :
			Scandir(argv[1],  0);
			break;
		default :
			fprintf(stderr, "\n<ERROR> : USE <Program> <Path> OR <Program>");
			exit(EXIT_FAILURE);
		}
		return 0;
}
 
 
void Scandir(char *wd, int depth) { 
	struct dirent **items; 
	int nitems, i; 
	if (chdir(wd) < 0) { 
		fprintf(stderr, "\n<ERROR> : DIR (%s) \n", wd);
		exit(EXIT_FAILURE); 
	} 

	nitems = scandir(".", &items, NULL,alphasort); 

	for (i = 0; i < nitems; i++) { 
	struct stat fstat; 
	if ( (!strcmp(items[i]->d_name, ".")) 
		|| (!strcmp(items[i]->d_name, "..")) ) 
		continue; 
	//fprintf(stdout, "%*s%s%s/ \n",depth,"\t",getcwd(cdir, MAX_SIZE), items[i]->d_name);
	fprintf(stdout, "%s/%s\n", getcwd(cdir, MAX_SIZE), items[i]->d_name);

	lstat(items[i]->d_name, &fstat); 
	if (S_ISDIR(fstat.st_mode)) { 
		if (indent < (depth-1) || (depth == 0)) { 
			indent ++; 
			Scandir(items[i]->d_name, depth); 
			} 
		} 
	} 

	indent --; 
	chdir(".."); 
} 
