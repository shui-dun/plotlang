#ifndef PLOTLANG_SCANNER_H
#define PLOTLANG_SCANNER_H

// 函数指针
typedef double (* FuncPtr)(double);

/*
 * 语法树中的节点
 */
typedef struct Node {
    int type; // 类型
    union {
        struct {
            struct Node *left; // 左运算符
            struct Node *right; // 又运算符
        } bin; // 二元运算节点
        struct {
            struct Node *child; // 函数参数
            FuncPtr func; // 函数指针
        } f; // 函数节点
        double num; // 数值
    } data; // 内容
} Node;

#define YYSTYPE Node*
int yylex(void); // 词法分析器

extern int yyleng; // 当前记号的长度
extern char *yytext; // 当前记号的字符串值
extern YYSTYPE yylval;
extern int lineNu; // 当前行号
extern FuncPtr curFunc; // 当前记号的函数指针（如果是函数类型）
extern double curVal; // 当前记号的数值（如果是数值类型）

#endif //PLOTLANG_SCANNER_H
