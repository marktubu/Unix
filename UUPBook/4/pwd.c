#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

ino_t get_inode(char*);
void printpathto(ino_t);
void inum_to_name(ino_t, char*, int);

int main()
{
	printpathto(get_inode("."));
	putchar('\n');
	return 0;
}

void printpathto(ino_t this_inode)
{
	ino_t my_inode;
	char its_name[BUFSIZ];
	if(get_inode("..")!=this_inode)
	{
		chdir("..");
		inum_to_name(this_inode, its_name, BUFSIZ);
		my_inode = get_inode(".");
		printpathto(my_inode);
		printf("/%s",its_name);
	}
}

void inum_to_name(ino_t inode, char* name, int buffsize)
{
	DIR* dir_ptr;
	struct dirent* direntp;
	dir_ptr = opendir(".");
	if(dir_ptr == NULL)
	{
		perror(".");
		exit(1);
	}

	while((direntp=readdir(dir_ptr)) != NULL)
	{
		if(direntp->d_ino == inode)
		{
			strncpy(name, direntp->d_name, buffsize);
			name[buffsize-1] = '\0';
			closedir(dir_ptr);
			return;
		}
	}
	fprintf(stderr, "error looking for inum %d\n", inode);
	exit(1);
}

ino_t get_inode(char* filename)
{
	struct stat curstat;
	if(stat(filename,&curstat) == -1)
	{
		fprintf(stderr, "cannot stat");
		perror(filename);
		exit(1);
	}
	return curstat.st_ino;
}

