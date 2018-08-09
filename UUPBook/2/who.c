#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void show_info(struct utmp* up)
{
	printf("%-8.8s ",up->ut_name);
	printf("%-8.8s ",up->ut_line);
	printf("%10ld ",up->ut_time);
	printf("(%s)\n",up->ut_host);
}

int main()
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);

	if((utmpfd = open(UTMP_FILE, O_RDONLY))==-1)
	{
		printf("%s\n","open utmp file failed");
		exit(1);
	}

	while(read(utmpfd, &current_record, reclen) == reclen)
	{
		show_info(&current_record);
	}

	close(utmpfd);
	return 0;
}
