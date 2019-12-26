#include <stdio.h>

int main()
{
    char str1[] = "hello world";
    char str2[] = "hello world";

    char* str3 = str1;
    char* str4 = "hello world";

    if(str1 == str2)
        printf("str1 and str2 are same");
    else
        printf("str1 and str2 are not same");
    
    if(str3 == str4)
        printf("str3 == str4");
    else
        printf("str3 != str4");

    str3[0] = 's';

    printf("str4 is : %p %p", &str1, &str2);
    return 0;
}