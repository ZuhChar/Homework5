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

// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <dirent.h>

// int main(int argc, char **argv){
//     //What to do if no arguments are provided.
//     if(argc == 1){
//         for(int i = 0; i < )
//     }
//     //Run through all of the arguments if there are >= 1 arguments.
//     for(int i = 1; i < argc; i++){
//         //Check to see if any options are passed.
//         if(argv[i] == "-" + [a-z][A-Z]){

//         }
//         //No options passed so move on to arguments of pathnames
//         else{

//         }
//     }
//     return 0;
// }
// int main(int argc, char **argv)
// {
//     if (argc == 1)
//     {
//         struct dirent *de; // Pointer for directory entry

//         // opendir() returns a pointer of DIR type.
//         DIR *dr = opendir(".");

//         if (dr == NULL) // opendir returns NULL if couldn't open directory
//         {
//             printf("Could not open current directory");
//             return 0;
//         }

//         // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
//         // for readdir()
//         while ((de = readdir(dr)) != NULL)
//             if (de->d_name != "." || de->d_name != "..")
//             {
//                 printf("%s\n", de->d_name);
//             }

//         closedir(dr);
//         return 0;
//     }
// }
//Used for basic input/output stream
#include <stdio.h>
//Used for handling directory files
#include <dirent.h>
//For EXIT codes and error handling
#include <errno.h>
#include <stdlib.h>

void _ls(const char *dir,int op_a,int op_l)
{
	//Here we will list the directory
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
		printf("%s  ", d->d_name);
		if(op_l) printf("\n");
	}
	if(!op_l)
	printf("\n");
}

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		_ls(".",0,0);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l);
		}
	}
	return 0;
}