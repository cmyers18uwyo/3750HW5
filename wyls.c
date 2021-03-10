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
                                dirFlag = 1;
                                dir = opendir(argv[i]);
                                if(dir) {
                                        while((de = readdir(dir)) != NULL) {
                                                char path[4096] = "";
                                                strcat(path,argv[i]);
                                                strcat(path,"/");
                                                //if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0) {
												if(de->d_name[0] != '.') {
                                                        strcat(path,de->d_name);
                                                        if(stat(path,&stats) == 0) {
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
															if(nFlag == 1) {
																printf("%d", stats.st_uid);
																printf("%d", stats.st_gid);
															}
															else {
																pwd = getpwuid(stats.st_uid);
																grp = getgrgid(stats.st_gid);
																printf("%s", pwd->pw_name);
																printf(" ");
																printf("%s", grp->gr_name);
															}
                                                            printf(" ");
															
															if(hFlag == 1) {
																float byteSize;
																long statsSize = stats.st_size;
																if(statsSize >= 1024) {
																	byteSize = stats.st_size / 1024;
																	printf ("%.1f",byteSize);
																}
																else if(statsSize >= 1048576) {
																	byteSize = stats.st_size / 1048576;
																	printf ("%.1f",byteSize);
																}
																else if(statsSize >= 1073741824) {
																	byteSize = stats.st_size / 1073741824;
																	printf ("%.1f",byteSize);
																}
																else {
																	printf ("%ld",stats.st_size);
																}
																
															}
															else {
																printf ("%ld",stats.st_size);
															}
                                                            printf(" ");
                                                           
															localtime_r(&stats.st_mtime, &time);
															strftime(dates, sizeof(dates), "%b %A %Y", &time);
															printf("%s",dates);
														   											   
															printf(" ");
															
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

