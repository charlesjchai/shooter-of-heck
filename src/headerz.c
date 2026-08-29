#include "headerz.h"
#include <math.h>

double point_dist(Point p1, Point p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
double dot_product(Point p1, Point p2) { return p1.x * p2.x + p1.y * p2.y; }

void obj_update(char **canvas, Point canvas_size, GameObj obj,
                size_t sprite_index)
{
    int line = obj.pos.y;
    int column = obj.pos.x;
    for (size_t i = 0; obj.sprites[sprite_index][i] != '\0'; i++)
    {
        char ch = obj.sprites[sprite_index][i];
        if (ch == '\n')
        {
            if (++line >= canvas_size.y)
                return;
            column = obj.pos.x;
            // Move onto the next line and return carriage if a newline is
            // detected

            continue;
        }
        if (column < canvas_size.x)
        {
            canvas[column][line] = ch;
        } // Don't print if it's out of bounds
        column++;
    }
}