#include "scanner.h"
#include <stdio.h>
#include <string.h>

/*
 * 测试词法分析器
 */
int main(int argc, char *argv[]) {
    char path[100] = "../../test/";
    strcat(path, argv[1]);
    freopen(path, "r", stdin);
    while (1) {
        int type = yylex();
        if (type == 0) {
            break;
        }
        printf("%d\t%s\n", type, yytext);
    }
}