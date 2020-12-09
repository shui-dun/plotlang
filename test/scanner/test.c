#include "scanner.h"
#include <stdio.h>


/*
 * 测试词法分析器
 */
int main() {
    freopen("../../test/in2.txt", "r", stdin);
    while (1) {
        int type = yylex();
        if (type == 0) {
            break;
        }
        printf("%d\t%s\n", type, yytext);
    }
}