#ifndef TETRIS_H
#define TETRIS_H

void init_tetris();
void tetris_update();

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 25

typedef struct{
    int flg;
    int color;
} board_element;

#endif