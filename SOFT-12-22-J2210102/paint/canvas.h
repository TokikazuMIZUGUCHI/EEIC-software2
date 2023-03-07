#ifndef _CALC_H_
#define _CALC_H_
typedef struct
{
    int width;
    int height;
    char **canvas;
    char pen;
} Canvas;

Canvas *init_canvas(int width, int height, char pen);
void reset_canvas(Canvas *c);
void print_canvas(Canvas *c);
void free_canvas(Canvas *c);

#endif