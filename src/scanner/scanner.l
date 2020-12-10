%option noyywrap
 /* c语言声明和定义 */
%{
#include "scanner.h"
#include "parser.h"
#include <math.h>
int lineNu = 1;
FuncPtr curFunc;
double curVal;
FuncT funcList[N_FUNC] = {{sin,   "SIN"},
                          {cos,   "COS"},
                          {tan,   "TAN"},
                          {exp,   "EXP"},
                          {log,   "LOG"},
                          {log10, "LOG10"},
                          {sqrt,  "SQRT"}};
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
    curFunc = funcList[0].fp;
    return FUNC;
}
"COS" {
    curFunc = funcList[1].fp;
    return FUNC;
}
"TAN" {
    curFunc = funcList[2].fp;
    return FUNC;
}
"EXP" {
    curFunc = funcList[3].fp;
    return FUNC;
}
"LOG" {
    curFunc = funcList[4].fp;
    return FUNC;
}
"LOG10" {
    curFunc = funcList[5].fp;
    return FUNC;
}
"SQRT" {
    curFunc = funcList[6].fp;
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
