%{
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "scanner.h"
#include "semantics.h"
#define N_FUNC 7
int yyerror(char *s);
Node* createNode(int type,...);
void printTree(Node *node, int indent);
typedef struct Reflect {
    FuncPtr fp;
    char *s;
} Reflect;
Reflect reflect[N_FUNC] = {{sin,   "SIN"},
                           {cos,   "COS"},
                           {tan,   "TAN"},
                           {exp,   "EXP"},
                           {log,   "LOG"},
                           {log10, "LOG10"},
                           {sqrt,  "SQRT"}};
%}

%token ORIGIN IS L_BRACKET COMMA R_BRACKET SEMICOLON ROT SCALE FOR T FROM TO STEP DRAW COLOR NUMBER FUNC ERR;
%left PLUS MINUS;
%left MULTIPLE DIVISION;
%right POW;
%right TEMP;

%%
Program :  {
} | Program Statement {
}
;
Statement : OriginStatement {
} | 
RotStatement {
} |
ScaleStatement {
} |
ForStatement {
} |
ColorStatement {
}
;

OriginStatement :
ORIGIN IS L_BRACKET Expression COMMA Expression R_BRACKET SEMICOLON {
    printf("enter ORIGIN statement\n");
    printTree($4, 4);
    printTree($6, 4);
    origin($4, $6);
    printf("exit ORIGIN statement\n");
}
;

RotStatement :
ROT IS Expression SEMICOLON {
    printf("enter ROT statement\n");
    printTree($3, 4);
    rot($3);
    printf("exit ROT statement\n");
}
;

ScaleStatement :
SCALE IS L_BRACKET Expression COMMA Expression R_BRACKET SEMICOLON {
    printf("enter SCALE statement\n");
    printTree($4, 4);
    printTree($6, 4);
    scale($4, $6);
    printf("exit SCALE statement\n");
}
;

ForStatement :
FOR T FROM Expression TO Expression STEP Expression DRAW L_BRACKET Expression COMMA Expression R_BRACKET SEMICOLON {
    printf("enter FOR statement\n");
    printTree($4, 4);
    printTree($6, 4);
    printTree($8, 4);
    printTree($11, 4);
    printTree($13, 4);
    draw($4, $6, $8, $11, $13);
    printf("exit FOR statement\n");
}
;

ColorStatement :
COLOR IS L_BRACKET Expression COMMA Expression COMMA Expression R_BRACKET SEMICOLON {
    printf("enter COLOR statement\n");
    printTree($4, 4);
    printTree($6, 4);
    printTree($8, 4);
    color($4, $6, $8);
    printf("exit COLOR statement\n");
}
;

Expression :
T {
    $$ = createNode(T);
} | NUMBER {
    $$ = createNode(NUMBER, curVal);
} |
Expression PLUS Expression {
    $$ = createNode(PLUS, $1, $3);
} |
Expression MINUS Expression {
    $$ = createNode(MINUS, $1, $3);
} |
Expression MULTIPLE Expression {
    $$ = createNode(MULTIPLE, $1, $3);
} |
Expression DIVISION Expression {
    $$ = createNode(DIVISION, $1, $3);
} | PLUS Expression %prec TEMP {
    $$ = $2;
} | MINUS Expression %prec TEMP {
    $$ = createNode(MINUS, createNode(NUMBER, 0.0), $2);
} |
Expression POW Expression {
    $$ = createNode(POW, $1, $3);
} |
L_BRACKET Expression R_BRACKET {
    $$ = $2;
} |
FUNC L_BRACKET Expression R_BRACKET {
    $$ = createNode(FUNC, curFunc, $3);
} | ERR {
    yyerror("err\n");
}
;

%%
int yyerror(char *s) {
    fprintf(stderr, "第%d行出现了语法错误。", lineNu);
    fprintf(stderr, "%s", s);
    return 0;
}

Node* createNode(int type,...) {
    Node* node = (Node *)malloc(sizeof(Node));
    va_list args;
    node->type = type;
	va_start(args, type);
	switch(type) {
		case NUMBER:
			node->data.num=(double)va_arg(args, double);
			break;
		case T:
			break;
		case FUNC:
			node->data.f.func = (FuncPtr)va_arg(args, FuncPtr);
			node->data.f.child=(Node *)va_arg(args, Node *);
			break;
		default:
			node->data.bin.left=(Node *)va_arg(args,Node *);
			node->data.bin.right=(Node *)va_arg(args,Node *);
			break;
  }
  va_end(args);
  return node;
}

static void printBlank(int n) {
    while (n--) {
        putchar(' ');
    }
}

char *findFunc(FuncPtr fp) {
    for (int i = 0; i < N_FUNC; i++) {
        if (reflect[i].fp == fp) {
            return reflect[i].s;
        }
    }
    assert(0);
}

void printTree(Node *node, int indent) {
    printBlank(indent);
    if (node->type == NUMBER) {
        printf("%lf\n", node->data.num);
    } else if (node->type == T) {
        printf("T\n");
    } else if (node->type == FUNC) {
        printf("%s\n", findFunc(node->data.f.func));
        printTree(node->data.f.child, indent + 4);
    } else {
        switch (node->type) {
            case PLUS:
                printf("+\n");
                break;
            case MINUS:
                printf("-\n");
                break;
            case MULTIPLE:
                printf("*\n");
                break;
            case DIVISION:
                printf("/\n");
                break;
            case POW:
                printf("**\n");
                break;
        }
        printTree(node->data.bin.left, indent + 4);
        printTree(node->data.bin.right, indent + 4);
    }
}