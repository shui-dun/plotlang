#include "scanner.h"
#include "parser.h"
#include "semantics.h"
#include <stdio.h>

/*
 * 测试语法分析器
 */

int main() {
    freopen("../../test/in3.txt", "r", stdin);
    yyparse();
    writePng("../../test.png");
}