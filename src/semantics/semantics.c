#include <math.h>
#include <stdio.h>
#include <libpng16/png.h>
#include <malloc.h>
#include <assert.h>
#include "semantics.h"
#include "scanner.h"
#include "parser.h"
#include "list.h"

double valT;
double originX, originY;
double rotDegree;
double scaleX = 1, scaleY = 1;
int colorR, colorG, colorB;
List lst;
int height, width;

void origin(Node *x, Node *y) {
    originX = solve(x);
    originY = solve(y);
}

void rot(Node *degree) {
    rotDegree = solve(degree);
}

void scale(Node *x, Node *y) {
    scaleX = solve(x);
    scaleY = solve(y);
}

void color(Node *r, Node *g, Node *b) {
    int red = (int) solve(r);
    int green = (int) solve(g);
    int blue = (int) solve(b);
    if (red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0) {
        fprintf(stderr, "颜色设定无效，rgb值必须介于0-255间\n");
        return;
    }
    colorR = red;
    colorG = green;
    colorB = blue;
}

double solve(Node *node) {
    if (node->type == NUMBER) {
        return node->data.num;
    } else if (node->type == T) {
        return valT;
    } else if (node->type == FUNC) {
        return node->data.f.func(solve(node->data.f.child));
    } else {
        switch (node->type) {
            case PLUS:
                return solve(node->data.bin.left) + solve(node->data.bin.right);
            case MINUS:
                return solve(node->data.bin.left) - solve(node->data.bin.right);
            case MULTIPLE:
                return solve(node->data.bin.left) * solve(node->data.bin.right);
            case DIVISION:
                return solve(node->data.bin.left) / solve(node->data.bin.right);
            case POW:
                return pow(solve(node->data.bin.left), solve(node->data.bin.right));
        }
    }
    fprintf(stderr, "无法解读的表达式\n");
    assert(0);
}

static void transform(double *xPtr, double *yPtr) {
    double x = *xPtr;
    double y = *yPtr;
    x *= scaleX;
    y *= scaleY;
    double x1 = x, y1 = y;
    x = x1 * cos(rotDegree) + y1 * sin(rotDegree);
    y = y1 * cos(rotDegree) - x1 * sin(rotDegree);
    x += originX;
    y += originY;
    *xPtr = x;
    *yPtr = y;
}

void draw(Node *fromNode, Node *toNode, Node *stepNode, Node *x, Node *y) {
    if (!lst) {
        lst = createList();
    }
    double from = solve(fromNode);
    double to = solve(toNode);
    double step = solve(stepNode);
    for (valT = from; valT <= to; valT += step) {
        double curX = solve(x);
        double curY = solve(y);
        transform(&curX, &curY);
        int intX = (int) curX, intY = (int) curY;
        if (intX < 0 || intY < 0) {
            continue;
        }
        if (intY > height) {
            height = intY;
        }
        if (intX > width) {
            width = intX;
        }
        insertList(lst, intX, intY, colorR, colorG, colorB);
    }
}

int writePng(char *filename) {
    if (!lst || !lst->next) {
        return -2;
    }
    height += 2;
    width += 2;
    FILE *fp = NULL;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *content = NULL;
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        return -1;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        return -1;
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
        return -1;
    }
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    content = (png_bytep *) malloc(height * sizeof(png_bytep));
    for (int y = 0; y < height; y++) {
        content[y] = (png_bytep) malloc(3 * width * sizeof(png_byte));
        for (int x = 0; x < 3 * width; x++) {
            content[y][x] = 0xff;
        }
    }
    for (List cur = lst->next; cur; cur = cur->next) {
        content[cur->y][3 * cur->x] = cur->r;
        content[cur->y][3 * cur->x + 1] = cur->g;
        content[cur->y][3 * cur->x + 2] = cur->b;
    }
    for (int y = 0; y < height; y++) {
        png_write_row(png_ptr, content[y]);
    }
    png_write_end(png_ptr, NULL);
    if (fp != NULL) fclose(fp);
    if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
    if (content != NULL) free(content);
    return 0;
}