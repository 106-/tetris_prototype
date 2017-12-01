#include "common.h"
#include "view.h"

// scoreはglobal変数
int score=0;

typedef struct{
    int x;
    int y;
} point;

typedef struct{
    int rotate;
    point p[3];
} block;

block blocks[8] = {
    {1, {{0,  0},{0, 0}, {0 ,0}}},  // null
    {2, {{0, -1},{0, 1}, {0 ,2}}},  // tetris
    {4, {{0, -1},{0, 1}, {1 ,1}}},  // L1
    {4, {{0, -1},{0, 1}, {-1,1}}},  // L2
    {2, {{0, -1},{1, 0}, {1 ,1}}},  // key1
    {2, {{0, -1},{-1,0}, {-1,1}}},  // key2
    {1, {{0,  1},{1, 0}, {1 ,1}}},  // square
    {4, {{0, -1},{1, 0}, {-1 ,0}}},  // T
};


board_element board[BOARD_WIDTH][BOARD_HEIGHT];

// テトリスの状態を初期化する.
void init_tetris()
{
    score = 0;
    int i,n;
    for(i=0; i<BOARD_WIDTH; i++)
    {
        for(n=0; n<BOARD_HEIGHT; n++)
        {
            board[i][n].flg = 0;
            board[i][n].color = COLOR_BLACK;
        }
    }
}

// テトリスを動かす. 毎フレーム呼ばれる.
void tetris_update()
{
    assign_block(board);
}