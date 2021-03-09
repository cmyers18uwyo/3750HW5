#################################
#Makefile
#Charles Myers
#COSC 3750 Spring 2021
#Homework 5
#March 9, 2021
#
#This file will compile the wyls file for HW5
##################################
CC=gcc
CFLAGS=-ggdb -Wall
RM=/bin/rm -f
#tidy and clean are not files
.PHONY : tidy clean
#wyls will use the wyls.c file and create an executable called wyls
wyls : wyls.c
	$(CC) $(CFLAGS) -o wyls wyls.c
#tidy will remove any object files in the directory
tidy :
	$(RM) *.o
#clean will run tidy and remove the executable wyls
clean : tidy
	$(RM) wyls