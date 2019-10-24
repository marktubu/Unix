#include <stdio.h>
#include <string>
#include <utility>
#include <iostream>
 
class MyString : public std::string
{
public:
	MyString() : std::string() {
		printf("MyString:1\n");
	}
	
	MyString(const char* data) : std::string(data) {
		printf("MyString:2\n");
	}
	
	MyString(MyString&& str) : std::string( std::move(str) ) {
		printf("MyString:3\n");
	}
	
	MyString operator = (MyString&& str){
		this->swap(str);        // 试试把它注释掉你就知道了
		printf("operator:1\n");
	}
};
 
int main(int argc, char* argv[])
{
	MyString str1 = "123";
	std::cout << "str1=" << str1 << std::endl;
	std::cout << "----------" << std::endl;
#if 1
	// 下面三句同等效果，呵呵
	MyString str2 = "456";
	str2 = (MyString &&)(str1);
	//MyString str2 = static_cast<MyString&&>(str1);
	//MyString str2 = std::move(str1);
#else
	// 下面三句同等效果，呵呵
	MyString str2 = (MyString &&)(str1);
	//MyString str2 = static_cast<MyString&&>(str1);
	//MyString str2 = std::move(str1);
#endif
	std::cout << "str1=" << str1 << std::endl;
	std::cout << "str2=" << str2 << std::endl;
	return 0;
}