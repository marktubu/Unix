#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdio.h>

int main(){
    regex_t re;
    regmatch_t subs[1024];
    char matched[1024];
    char src[1024]="beginworldendtestbeginworkendtest";
    char pattern[1024] = "begin(.*?)end";

    int err = regcomp(&re, pattern, REG_EXTENDED);
    if (err) {
        printf("regex error");
        return 1;
    }

    const char *ptr = src;
    while (strlen(ptr) > 0) {
        memset(subs, 0, sizeof(subs));
        err = regexec(&re, ptr, (size_t)1024, subs, REG_NOTBOL);
        if (err == REG_NOMATCH) {
            break;
        } else if (err) {
            char errbuf[1024];
            regerror(err, &re, errbuf, sizeof(errbuf));
            printf("errbuf:%s\n", errbuf);
            break;
        }
        int len = subs[0].rm_eo - subs[0].rm_so;
        memcpy(matched, ptr + subs[0].rm_so, len);
        matched[len] = '\0';
        printf("match:%s\n", matched);
        ptr = ptr + subs[0].rm_so + len;
    }

    regfree(&re);

    return 0;
}
