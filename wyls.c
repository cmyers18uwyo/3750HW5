/*
* wyls.c
* Charles Myers
* COSC 3750 Spring 2021
* Homework 5
* March 9, 2021
*
* This file is our version of ls
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
int main(int argc, char* argv[]) {
	int dirFlag = 0, nFlag = 0, hFlag = 0;
	DIR* dir;
	struct stat stats;
	struct dirent *de;
	
	struct passwd pwd;
    struct passwd *result;
	char *buf;
    size_t bufsize = 16384;
    int s;
	
	
	if(argc > 1) {
		
		for(int i = 1; argv[i] != NULL; i++) {
			if(argv[i][0] == '-' && dirFlag == 0) {
				if(strcmp(argv[i], "-n") == 0 && nFlag == 0) {
					nFlag = 1;
				}
				else if(strcmp(argv[i], "-h") == 0 && hFlag == 0) {
					hFlag = 1;
				}
				else if(strcmp(argv[i], "-nh") == 0 || strcmp(argv[i], "-hn") == 0 && (nFlag == 0 && hFlag == 0)) {
					nFlag = 1;
					hFlag = 1;
				}
				else {
					printf("Invalid Option");
					exit(1);
					
				}
			}
			else {
				dirFlag = 1;
				buf = malloc(bufsize);
				dir = opendir(argv[i]);
				if(dir) {
					while((de = readdir(dir)) != NULL) {
						if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0) {
							if(lstat(argv[i], &stats) ==0) {
								s = getpwnam_r(getlogin(),&pwd, buf, bufsize, &result);
								printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
								printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
								printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
								printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
								printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
								printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
								printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
								printf( (stats.st_mode & S_IROTH) ? "r" : "-");
								printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
								printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
								printf ("%ld",stats.st_size);
								printf("%s", result);
								printf("%s",de->d_name);
								printf("\n");
						}
						}
					}
					closedir(dir);
				}
			}
		}
		
	}
	else {
		
	}
}