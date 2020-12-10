#ifndef PLOTLANG_SEMANTICS_H
#define PLOTLANG_SEMANTICS_H

#include "scanner.h"
#include "list.h"

extern double valT; // 当前T的值
extern double originX, originY; // 原点x，y坐标值
extern double rotDegree; // 旋转角度
extern double scaleX, scaleY; // 伸展比例
extern int colorR, colorG, colorB; // 当前画笔的RGB值

// origin的语义函数
void origin(Node *x, Node *y);

// rot的语义函数
void rot(Node *degree);

// scale的语义函数
void scale(Node *x, Node *y);

// color的语义函数
void color(Node *r, Node *g, Node *b);

// 解出表达式树的数值
double solve(Node *node);

// draw的语义函数
void draw(Node *fromNode, Node *toNode, Node *stepNode, Node *x, Node *y);

// 写入png文件
int writePng(char *filename);
#endif //PLOTLANG_SEMANTICS_H
