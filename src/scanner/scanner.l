%option noyywrap
 /* c语言声明和定义 */
%{
#include "scanner.h"
#include "parser.h"
#include <math.h>
int lineNu = 1;
FuncPtr curFunc;
double curVal;
%}

digit [0-9]+
blank [\r\t ]+
comment1 "//".*
comment2 "--".*
str [a-zA-Z_][a-zA-Z0-9_]*

%%

 /* 翻译规则 */
"ORIGIN" return ORIGIN;
"IS" return IS;
"(" return L_BRACKET;
"," return COMMA;
")" return R_BRACKET;
";" return SEMICOLON;
"ROT" return ROT;
"SCALE" return SCALE;
"FOR" return FOR;
"T" return T;
"FROM" return FROM;
"TO" return TO;
"STEP" return STEP;
"DRAW" return DRAW;
"COLOR" return COLOR;
{digit}(\.{digit})? {
    curVal = atof(yytext);
    return NUMBER;
}
"PI" {
    curVal = 3.141592653589793;
    return NUMBER;
}
"E" {
    curVal = 2.718281828459045;
    return NUMBER;
}
"SIN" {
    curFunc = sin;
    return FUNC;
}
"COS" {
    curFunc = cos;
    return FUNC;
}
"TAN" {
    curFunc = tan;
    return FUNC;
}
"EXP" {
    curFunc = exp;
    return FUNC;
}
"LOG" {
    curFunc = log;
    return FUNC;
}
"LOG10" {
    curFunc = log10;
    return FUNC;
}
"SQRT" {
    curFunc = sqrt;
    return FUNC;
}
"+" return PLUS;
"-" return MINUS;
"*" return MULTIPLE;
"/" return DIVISION;
"**" return POW;
{blank}|{comment1}|{comment2} ;
"\n" lineNu++;
{str} {
    fprintf(stderr, "第%d行：未识别的记号%s\n", lineNu, yytext);
    return ERR;
}
. {
    fprintf(stderr, "第%d行：未识别的记号%s\n", lineNu, yytext);
    return ERR;
}
