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
#include <sys/types.h>
#include <pwd.h>
#include <nss.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>

int main(int argc, char* argv[]) {
        int dirFlag = 0, nFlag = 0, hFlag = 0;
        DIR* dir;
        struct stat stats;
        struct dirent *de;
		struct passwd *pwd;
		struct group *grp;
		struct tm time;
		char *buf[1024];
		char dates[256];
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
                                if(dir) {
                                        while((de = readdir(dir)) != NULL) {
                                                char path[4096] = "";
                                                strcat(path,argv[i]);
                                                strcat(path,"/");
                                                if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0) {
                                                        strcat(path,de->d_name);
                                                        if(stat(path,&stats) == 0) {
																pwd = getpwuid(stats.st_uid);
																grp = getgrgid(stats.st_gid);
                                                                printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                                                                printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                                                                printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                                                                printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                                                                printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                                                                printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                                                                printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                                                                printf((stats.st_mode & S_IROTH) ? "r" : "-");
                                                                printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                                                                printf((stats.st_mode & S_IXOTH) ? "x" : "-");
                                                                printf(" ");
                                                                printf ("%ld",stats.st_size);
                                                                printf(" ");
                                                                printf("%s", pwd->pw_name);
																printf("%s", grp->gr_name);
																printf(" ");
                                                                printf("%s",de->d_name);
																

																printf(" ");
																localtime_r(&stats.st_mtime, &time);
																strftime(dates, sizeof(dates), "%b %A %Y", &time);
																printf("%s",dates);

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
