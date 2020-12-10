#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "parser.h"
#include "semantics.h"

/*
 * 函数绘图语言解释器 主函数
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("请指定源代码文件路径\n");
        return 1;
    }
    freopen(argv[1], "r", stdin);
    yyparse();
    char pngName[50];
    strcpy(pngName, argv[1]);
    strcat(pngName, ".png");
    if (writePng(pngName) == 0) {
        printf("图片已写入%s\n", pngName);
    }
}