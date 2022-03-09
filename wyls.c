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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

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
int main(int argc, char **argv)
{
    if(argc == 1){
        struct dirent *de;  // Pointer for directory entry
  
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir(".");
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
            if(%s, de->d_name != "." || %s, de->d_name != ".."){
            printf("%s\n", de->d_name);
            }
  
    closedir(dr);    
    return 0;
    }
}