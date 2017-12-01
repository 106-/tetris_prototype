#ifndef TETRIS_H
#define TETRIS_H

void init_tetris();
void tetris_update();

// 当たり判定用のボードの広さ
#define BOARD_WIDTH 12
#define BOARD_HEIGHT 25

// 初期のブロックが落ちる頻度
#define INIT_FREQ 20

// ブロックの数
#define BLOCK_NUM 4

// ボード一つ一つの要素
typedef struct{
    int flg;
    int color;
} board_element;

typedef struct
{
    int x;
    int y;
} point;

typedef struct
{
    point child[4];
    int color;
} block;

#endif