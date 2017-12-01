#include "common.h"
#include "view.h"

// scoreはglobal変数
int score = 0;

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

typedef struct
{
    int x;
    int y;
    block b;
} active_block;

int freq=100;

void move_block();
void rotate_block(active_block, int);
void block_down();
void generateblock();
int check_collision(active_block);
void switch_block(active_block, int, int);

active_block active;
block next_block;
board_element board[BOARD_HEIGHT][BOARD_WIDTH];

block blocks[8] = {
    {{{0, 0}, {0,  0}, {0, 0}, {0 ,0}}, COLOR_WHITE},  // null
    {{{0, 0}, {0, -1}, {0, 1}, {0 ,2}}, COLOR_GREEN},  // tetris
    {{{0, 0}, {0, -1}, {0, 1}, {1 ,1}}, COLOR_GREENYELLOW},  // L1
    {{{0, 0}, {0, -1}, {0, 1}, {-1,1}}, COLOR_NAVY},  // L2
    {{{0, 0}, {0, -1}, {1, 0}, {1 ,1}}, COLOR_ORANGE},  // key1
    {{{0, 0}, {0, -1}, {-1,0}, {-1,1}}, COLOR_YELLOW},  // key2
    {{{0, 0}, {0,  1}, {1, 0}, {1 ,1}}, COLOR_RED},  // square
    {{{0, 0}, {0, -1}, {1, 0}, {-1 ,0}}, COLOR_BLUE}  // T
};

// テトリスの状態を初期化する.
void init_tetris()
{
    score = 0;
    freq = INIT_FREQ;
    int i, n;
    // 全部消す
    for (i = 0; i < BOARD_HEIGHT; i++)
    {
        for (n = 0; n < BOARD_WIDTH; n++)
        {
            board[i][n].flg = 0;
            board[i][n].color = COLOR_BLACK;
        }
    }
    // 左の壁を作る
    for(i=0; i<BOARD_HEIGHT; i++)
    {
        board[i][0].flg = 1;
    }
    // 右の壁を作る
    for(i=0; i<BOARD_HEIGHT; i++)
    {
        board[i][BOARD_WIDTH-1].flg = 1;
    }
    // 下の壁を作る
    for(i=0; i<BOARD_WIDTH; i++)
    {
        board[BOARD_HEIGHT-1][i].flg = 1;
    }
    next_block = blocks[1];
    generateblock();
}

// テトリスを動かす. 毎フレーム呼ばれる.
void tetris_update()
{
    move_block();
    if(cnt % freq == 0)
        block_down();
    assign_block(board);
}

// ブロックを下へ移動させる
void block_down()
{
    int i;

    // 今のブロックを消しておく(衝突判定に含まれないように)
    int x,y;
    switch_block(active, 0, COLOR_BLACK);

    // 一旦下に落とす
    active.y++;
    // ぶつかってないかの判定
    if(!check_collision(active))
    {
        // 新しいブロックを置く
        switch_block(active, 1, active.b.color);
    }
    else
    {
        // 元に戻す
        active.y--;
        switch_block(active, 1, active.b.color);
        generateblock();
    }

}

// キーボードの入力に合わせてブロックを移動させる
void move_block()
{
    if(button[BUTTON_ROTATE]==1)
    {
        switch_block(active, 0, COLOR_BLACK);
        rotate_block(active, 1);
        if(check_collision(active))
            rotate_block(active, 0);
        switch_block(active, 1, active.b.color);
    }
    if(button[BUTTON_LEFT]==1)
    {
        switch_block(active, 0, COLOR_BLACK);
        active.x--;
        if(check_collision(active))
            active.x++;
        switch_block(active, 1, active.b.color);
    }
    if(button[BUTTON_RIGHT]==1)
    {
        switch_block(active, 0, COLOR_BLACK);
        active.x++;
        if(check_collision(active))
            active.x--;
        switch_block(active, 1, active.b.color);
    }
}

// ブロックを回転させる clockwise=1で時計回り,0で反時計回り
void rotate_block(active_block b, int clockwise)
{
    int i,x,y;
    for(i=0; i<BLOCK_NUM; i++)
    {
        if(clockwise==1)
        {
            x = active.b.child[i].x;
            y = active.b.child[i].y;
            active.b.child[i].x = -y;
            active.b.child[i].y = x;
        }
        else if(clockwise==0)
        {
            x = active.b.child[i].x;
            y = active.b.child[i].y;
            active.b.child[i].x = y;
            active.b.child[i].y = -x;
        }
    }
}

// ブロックのフラグと色を一括して変更する
void switch_block(active_block a,int flg, int color)
{
    int i, x, y;
    for(i=0; i<BLOCK_NUM; i++)
    {
        x = active.x+active.b.child[i].x;
        y = active.y+active.b.child[i].y;
        board[y][x].flg = flg;
        board[y][x].color = color;
    }
}

// 何かにぶつかってるかの判定 ぶつかってたら1を返す
int check_collision(active_block a)
{
    int i, x, y;
    for(i=0; i<BLOCK_NUM; i++)
    {
        x = active.x+active.b.child[i].x;
        y = active.y+active.b.child[i].y;
        // なにかがあるとき
        if(board[y][x].flg)
        {
            return 1;
        }
    }
    return 0;
}

// 新しくブロックを作る
void generateblock()
{
    active.x = 5;
    active.y = 3;
    active.b = next_block;
    next_block = blocks[1];
}
