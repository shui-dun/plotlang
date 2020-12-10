#include "scanner.h"
#include "parser.h"
#include "semantics.h"
#include <stdio.h>
#include <string.h>

/*
 * 测试语法分析器
 */

int main(int argc, char *argv[]) {
    char path[100] = "../../test/";
    strcat(path, argv[1]);
    freopen(path, "r", stdin);
    yyparse();
    writePng("../../test.png");
}