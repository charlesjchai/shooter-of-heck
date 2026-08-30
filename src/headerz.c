#include "headerz.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

double point_dist(Point p1, Point p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
double dot_product(Point p1, Point p2) { return p1.x * p2.x + p1.y * p2.y; }

GameObj *new_gameobj(Point pos, Point size, char *sprites[])
{
    GameObj *obj = calloc(1, sizeof(GameObj));
    obj->pos = pos;
    obj->size = size;
    obj->sprites = sprites;
    return obj;
}
Canvas *new_canvas(Point size)
{
    Canvas *canvas = calloc(1, sizeof(Canvas));
    canvas->size = size;
    canvas->board = calloc(size.x, sizeof(char *));
    for (int i = 0; i < size.x; i++)
    {
        canvas->board[i] = calloc(size.y, sizeof(char));
    }

    return canvas;
}

char canvas_getch(const Canvas *canvas, Point index)
{
    if (index.x < 0 || index.x >= canvas->size.x || index.y < 0 ||
        index.y >= canvas->size.y)
    {
        return 0;
    }
    return canvas->board[index.x][index.y];
}
void canvas_setch(Canvas *canvas, char val, Point index)
{
    if (index.x < 0 || index.x >= canvas->size.x || index.y < 0 ||
        index.y >= canvas->size.y)
    {
        return;
    }
    canvas->board[index.x][index.y] = val;
}
void canvas_erase(Canvas *canvas)
{
    for (int i = 0; i < canvas->size.x; i++)
    {
        memset(canvas->board[i], 0,
               canvas->size.y * sizeof(canvas->board[i][0]));
    }
}
void obj_update(Canvas *canvas, const GameObj *obj, size_t sprite_index)
{
    int line = obj->pos.y;
    int column = obj->pos.x;
    for (size_t i = 0; obj->sprites[sprite_index][i] != '\0'; i++)
    {
        char ch = obj->sprites[sprite_index][i];
        if (ch == '\n' )
        {
            if (++line >= canvas->size.y)
                return;
            column = obj->pos.x;
            // Move onto the next line and return carriage if a newline is
            // detected

            continue;
        }
        
        // canvas[column][line] = ch;
        if (column >= 0)
            canvas_setch(canvas, ch, (Point){column, line});
        column++;
    }
}