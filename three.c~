#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 1024

void find(char* pos,int depth);

int main(int argc,char* argv[]){
char *temp;    
switch(argc){
	case 1 :
		temp = malloc(sizeof(char) * MAX_BUFFER_SIZE);
		getcwd(temp, MAX_BUFFER_SIZE - 1);
		*(temp + MAX_BUFFER_SIZE) = '\0';
		fprintf(stdout, "Start DIR PATH = %s", temp);
		find(".", 0);
		break;
	case 2 : 
		fprintf(stdout, "\n\nStart DIR PATH = %s\n\n", argv[1]);
		find(argv[1], 0);
		break;
	default :
		fprintf(stderr, "\n\nUSE : <Program> <Path> OR <Program>\n");
        	exit(EXIT_FAILURE);
	}       
    return 0;
}

void find(char* pos,int depth){ 

    DIR *dp;              
    struct dirent *dir;   
    struct stat stat;       
    if( (dp=opendir(pos)) == NULL){
        fprintf(stderr, "\n<ERROR> CAN'T ACCESS DIR\n");
        exit(EXIT_FAILURE);
    }
    chdir(pos);   
    while(dir = readdir(dp)){
        memset(&stat,0,sizeof(struct stat));
        lstat(dir->d_name,&stat);  
        if(S_ISDIR(stat.st_mode)){ 
            printf("%*s%s/ \n",depth,"",dir->d_name); 
            if(strcmp(".",dir->d_name) == 0 ||
                    strcmp("..",dir->d_name) == 0) 
                continue;
            find(dir->d_name,depth+4); 
        }else printf("%*s%s \n",depth,"",dir->d_name);
    }
    closedir(dp);
}
