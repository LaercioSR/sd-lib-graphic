#ifndef GRAPHIC_PROCESSOR_H
#define GRAPHIC_PROCESSOR_H

#define LEFT         0
#define RIGHT        4
#define UP           2
#define DOWN         6
#define UPPER_RIGHT  1
#define UPPER_LEFT   3
#define BOTTOM_LEFT  5
#define BOTTOM_RIGHT 7

typedef struct {
    int coord_x, coord_y;
    int direction, offset, data_register;
    int step_x, step_y;
    int ativo, collision;
} Sprite;

typedef struct {
    int coord_x, coord_y, offset;
    int data_register, ativo;
} Sprite_Fixed;

int set_sprite(int registrador, int x, int y, int offset, int activation_bit);
int set_background_block(int column, int line, int R, int G, int B);
int set_background_color(int R, int G, int B);
void increase_coordinate(Sprite* sp, int mirror);
int collision(Sprite* sp1, Sprite* sp2);

#endif // GRAPHIC_PROCESSOR_H