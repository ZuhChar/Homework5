// /*
//  * wyls.c
//  * Author: Zachary Crimmel
//  * Date: Mar 7, 2022
//  *
//  * COSC 3750, Homework 5
//  *
//  * This is a simple version of the ls utility.
//  * It is designed to print the contents of a directory and modify this output based on the options recieved.
//  *
//  * Collaborated with Ian Moon to work on this
//  */

// // Used for basic input/output stream
// #include <stdio.h>
// // Used for handling directory files
// #include <dirent.h>
// // For EXIT codes and error handling
// #include <errno.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <grp.h>

// void _ls(const char *dir, int op_a, int op_l, int op_n, int op_h)
// {
// 	char *userName;
// 	int userID;
// 	struct stat datestat;
// 	int group;
// 	struct stat st;
// 	int readSize;
// 	struct group *groupName;
// 	int size;
// 	char date;

// 	struct stat fileStat;

// 	struct dirent *d;
// 	DIR *dh = opendir(dir);
// 	if (!dh)
// 	{
// 		if (errno = ENOENT)
// 		{
// 			// If the directory is not found
// 			perror("Directory doesn't exist");
// 		}
// 		else
// 		{
// 			// If the directory is not readable then throw error and exit
// 			perror("Unable to read directory");
// 		}
// 		exit(EXIT_FAILURE);
// 	}
// 	// While the next entry is not readable we will print directory files
// 	while ((d = readdir(dh)) != NULL)
// 	{
// 		// If hidden files are found we continue
// 		if (!op_a && d->d_name[0] == '.')
// 			continue;
// 		if (op_l)
// 		{

// 			printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
// 			printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
// 			printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
// 			printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
// 			printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
// 			printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
// 			printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
// 			printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
// 			printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
// 			printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
// 			userID = geteuid();
// 			userName = getlogin();
// 			group = getgid();
// 			groupName = getgrgid(group);
// 			stat(dh, &st);
// 			size = dh->st_size;
// 			stat(dh, &datestat);
// 			date = dh->st_mtime;
// 			//groupName->gr_name = getgrnam(userName);
// 			printf(" %s %s %d %d %s\n", userName, groupName->gr_name, size, date, d->d_name);
// 		}
// 	}
// 	if (!op_l)
// 		printf("\n");
// }

// int main(int argc, const char *argv[])
// {
// 	if (argc == 1)
// 	{
// 		_ls(".", 0, 0, 0, 0);
// 	}
// 	else if (argc == 2)
// 	{
// 		if (argv[1][0] == '-')
// 		{
// 			// Checking if option is passed
// 			// Options supporting: a, l
// 			int op_a = 0, op_l = 0, op_n = 0, op_h = 0;
// 			char *p = (char *)(argv[1] + 1);
// 			while (*p)
// 			{
// 				if (*p == 'a')
// 					op_a = 1;
// 				else if (*p == 'l')
// 					op_l = 1;
// 				else if (*p == 'n')
// 					op_n = 1;
// 				else if (*p == 'h')
// 					op_h = 1;
// 				else
// 				{
// 					perror("Option not available");
// 					exit(EXIT_FAILURE);
// 				}
// 				p++;
// 			}
// 			_ls(".", op_a, op_l, op_n, op_h);
// 		}
// 	}
// 	return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


void detail(char *filename);

void myls(int size, char **argv) {
	struct dirent *dent;
	DIR *dp;

	if((dp = opendir("./")) == NULL) {
		exit(1);
	}

	if(size == 1) {
		while((dent = readdir(dp)) != NULL) {
			if(strcmp(dent->d_name, "..") == 0) {
				continue;
			} else if(strcmp(dent->d_name, ".") == 0) {
				continue;
			}

			printf("%s\t", dent->d_name);
		}
		printf("\n");

	} else if(size == 2) {
		if(strcmp(argv[1], "--help") == 0) {
			printf("myls command list directory comtents\n");
			printf("usage : myls [-l] [filename]\n");
			printf("[option] --help : print myls command usage\n\t-l : print detail contents of list directory contents\n");

			return;
			
		} else if(strcmp(argv[1], "-l") == 0) {
			while((dent = readdir(dp)) != NULL) {
				if(strcmp(dent->d_name, "..") == 0) {
					continue;
				} else if(strcmp(dent->d_name, ".") == 0) {
					continue;
				}

				detail(dent->d_name);
			}
			
		} else {
			int i;
			for(i = 0; i < size; i++) {
				printf("%s\n", argv[i]);
			}
			printf(": Invalid option\n");
		}

	} else if(size == 3) {
		if(strcmp(argv[1], "-l") == 0) {
			printf("50\n");
			detail(argv[2]);
			
		} else {
			int i;
			for(i = 0; i < size; i++) {
				printf("%s\n", argv[i]);
			}
			printf(": Invalid option\n");
		}
	}
}

void detail(char *filename) {
	struct stat statbuf;

	stat(filename, &statbuf);
	struct group *grp;
	struct passwd *pwd;
	grp = getgrgid((int)statbuf.st_gid);
	pwd = getpwuid((int)statbuf.st_uid);

	char permission[11];
	if(S_ISDIR(statbuf.st_mode)) {
		permission[0] = 'd';

	} else if(S_ISBLK(statbuf.st_mode)){
		permission[0] = 'b';

	} else if(S_ISCHR(statbuf.st_mode)) {
		permission[0] = 'c';

	} else if(S_ISFIFO(statbuf.st_mode)) {
		permission[0] = 'f';

	} else if(S_ISSOCK(statbuf.st_mode)) {
		permission[0] = 's';

	} else if(S_ISLNK(statbuf.st_mode)) {
		permission[0] = 'l';
		
	}else {
		permission[0] = '-';
	}

	if(statbuf.st_mode & S_IRUSR) {
		permission[1] = 'r';
	} else {
		permission[1] = '-';
	}

	if(statbuf.st_mode & S_IWUSR) {
		permission[2] = 'w';
	} else {
		permission[2] = '-';
	}

	if(statbuf.st_mode & S_IXUSR) {
		permission[3] = 'x';
	} else {
		permission[3] = '-';
	}

	if(statbuf.st_mode & S_IRGRP) {
		permission[4] = 'r';
	} else {
		permission[4] = '-';
	}
	
	if(statbuf.st_mode & S_IWGRP) {
		permission[5] = 'w';
	} else {
		permission[5] = '-';
	}

	if(statbuf.st_mode & S_IXGRP) {
		permission[6] = 'x';
	} else {
		permission[6] = '-';
	}

	if(statbuf.st_mode & S_IROTH) {
		permission[7] = 'r';
	} else {
		permission[7] = '-';
	}

	if(statbuf.st_mode & S_IWOTH) {
		permission[8] = 'w';
	} else {
		permission[8] = '-';
	}

	if(statbuf.st_mode & S_IXOTH) {
		permission[9] = 'x';
	} else {
		permission[9] = '-';
	}

	permission[10] = '\0';

	struct tm *tm;
	time_t t = statbuf.st_atime;
	tm = localtime(&t);
	char timebuf[80];
	strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M",tm);

	printf("%s %d %s %s %d %s %s\n", permission, (unsigned int)statbuf.st_nlink, pwd->pw_name, grp->gr_name, (int)statbuf.st_size, timebuf, filename);
}