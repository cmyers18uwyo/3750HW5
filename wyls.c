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
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
        int dirFlag = 0, nFlag = 0, hFlag = 0;
        DIR* dir;
        struct stat stats;
        struct dirent *de;
        if(argc > 1) {
                //printf("Hello \n");
                for(int i = 1; argv[i] != NULL; i++) {
                        if(argv[i][0] == '-' && dirFlag == 0) {
                                printf("Hello - \n");
                                if(strcmp(argv[i], "-n") == 0 && nFlag == 0) {
                                        nFlag = 1;
                                }
                                else if(strcmp(argv[i], "-h") == 0 && hFlag == 0) {
                                        hFlag = 1;
                                }
                                else if((strcmp(argv[i], "-nh") == 0 || strcmp(argv[i], "-hn") == 0) && (nFlag == 0 && hFlag == 0)) {
                                        nFlag = 1;
                                        hFlag = 1;
                                }
                                else {
                                        printf("Invalid Option");


                                }
                        }
                        else {
                                //printf("Hello name \n");
                                dirFlag = 1;
                               // char* path = realpath(argv[i],NULL);
                                //printf("%s",path);
                                //printf("\n");
                                dir = opendir(argv[i]);
								char *path[4096] = '';
                                //char pathbuf[4096];
                                if(dir) {
                                        while((de = readdir(dir)) != NULL) {
											strcpy(path, de->d_name);
                                                if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0) {
                                                        if(stat(path,&stats) == 0) {
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
                                                                printf(" ");
                                                                printf ("%ld",stats.st_size);
                                                                printf(" ");
                                                                printf("%s",getlogin());
                                                                printf("%s",de->d_name);
                                                                printf("\n");
                                                }
                                                }
                                        }
                                        closedir(dir);
                                }
                                else {
                                        printf("cant open \n");
                                }
                        }
                }

        }
        else {

        }
}