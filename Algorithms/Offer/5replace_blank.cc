#include <iostream>
#include <stack>

using namespace std;

void replace_blank(char str[], int length)
{
    int original_length = 0;
    int blank_count = 0;
    for(int i=0;i<length;++i)
    {
        char c = str[i];
        if(c == '\0')
        {
            break;
        }
        else if(c == ' ')
        {
            blank_count++;
        }
        original_length++;
    }

    if(blank_count == 0)
    {
        cout << str << endl;
        return;
    }

    int new_length = original_length + blank_count * 2 + 1;
    if(new_length > length)
        return;

    int origin_index = original_length - 1;
    int new_index = new_length - 1;

    str[new_length - 1] = '\0';
    new_index --;
    while (new_index >=0 && origin_index >=0)
    {
        char c = str[origin_index];
        if(c == ' ')
        {
            str[new_index--] = '0';
            str[new_index--] = '2';
            str[new_index--] = '%';

            origin_index--;
        }
        else
        {
            str[new_index--] = str[origin_index--];
        }
        
    }

    cout << str << endl;
} 

int main()
{
    const int length = 100;
    //char str[length] = "this is me";
    //char str[length] = "   ";
    char str[length] = "thisisme";
    replace_blank(str, length);
    return 0;
}