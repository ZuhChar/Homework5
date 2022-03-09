/*
 * wyls.c
 * Author: Zachary Crimmel
 * Date: Mar 7, 2022
 *
 * COSC 3750, Homework 5
 *
 * This is a simple version of the ls utility.
 * It is designed to print the contents of a directory and modify this output based on the options recieved.
 *
 * Collaborated with Ian Moon to work on this
 */

//Used for basic input/output stream
#include <stdio.h>
//Used for handling directory files
#include <dirent.h>
//For EXIT codes and error handling
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void _ls(const char *dir,int op_a,int op_l,int op_n, int op_h)
{
    char access;
    char * userName;
    int userID;
    char date;
    int group;
    int size;
    int readSize;

	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh)
	{
		if (errno = ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL)
	{
		//If hidden files are found we continue
		if (!op_a && d->d_name[0] == '.')
			continue;
		if(op_l){
            userID = geteuid();
            userName = getlogin();
            group = getgid();
        }
        printf("%s %d %s %s", d->d_name, userID, group, userName);
	}
	if(!op_l)
	printf("\n");
}

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		_ls(".",0,0,0,0);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0, op_n = 0, op_h = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
                else if(*p == 'n') op_n = 1;
                else if(*p == 'h') op_h = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l,op_n,op_h);
		}
	}
	return 0;
}