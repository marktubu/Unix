#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "test"

int main()
{
	int fd0,fd1,fd2;
	//fd0 = open(FILENAME, O_RDWR);  //将flag改成 O_RDWR 先读取20字节，
									 //再写入 s 时， 从文件20字节处开始写入
	fd0 = open(FILENAME, O_RDONLY);
	fd1 = open(FILENAME, O_WRONLY);
	fd2 = open(FILENAME, O_RDONLY);
	
	char buf[20];
	read(fd0, buf,20);
	printf("%s\n",buf);
	
	char* s = "testing 123...";
	//write(fd0, s, strlen(s));
	write(fd1, s, strlen(s));   //先读取20字节，再写入时，从文件开头写入。
								//同一文件的不同的描述符的文件指针不一样

	read(fd2, buf, 20);
	printf("%s\n", buf);

	close(fd0);
	close(fd1);
	close(fd2);
}
