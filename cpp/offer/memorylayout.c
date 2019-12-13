//32位系统
#include<stdio.h>

#pragma pack(4)

struct
{
    int i;    
    char c1;  
    char c2;  
}x1;

struct{
    char c1;  
    int i;    
    char c2;  
}x2;

struct{
    char c1;  
    char c2; 
    int i;    
}x3;

struct{
    char c1;  
    double c2;   
}x4;

int main()
{
    printf("%d\n",sizeof(x1));  // 输出8
    printf("%d\n",sizeof(x2));  // 输出12
    printf("%d\n",sizeof(x3));  // 输出8
    printf("%d\n",sizeof(x4));  // 输出8
    return 0;
}