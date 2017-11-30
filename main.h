#include <stdio.h>
#include <stdlib.h>
#include "./DxLib/DxLib.h"

// 画面サイズの定義
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define CHARA_WIDTH   80
#define CHARA_HEIGHT  60

// ボタンの数
#define NUM_BUTTON 4

// 色の定義
// ここを参考にした: https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
#define COLOR_BLACK           GetColor(0x00, 0x00, 0x00)
#define COLOR_BLUE            GetColor(0x00, 0x00, 0xFF)
#define COLOR_GREEN           GetColor(0x00, 0x80, 0x00)
#define COLOR_RED             GetColor(0xFF, 0x00, 0x00)
#define COLOR_GREENYELLOW     GetColor(0xAD, 0xFF, 0x2F)
#define COLOR_YELLOW          GetColor(0xFF, 0xFF, 0x00)
#define COLOR_CYAN            GetColor(0x00, 0xFF, 0xFF)
#define COLOR_MAGENTA         GetColor(0xFF, 0x00, 0xFF)
#define COLOR_ORANGE          GetColor(0xFF, 0xA5, 0x00)
#define COLOR_PINK            GetColor(0xFF, 0xC0, 0xCB)
#define COLOR_NAVY            GetColor(0x00, 0x00, 0x80)
#define COLOR_DARKGREEN       GetColor(0x00, 0x64, 0x00)
#define COLOR_DARKCYAN        GetColor(0x00, 0x8B, 0x8B)
#define COLOR_MAROON          GetColor(0x80, 0x00, 0x00)
#define COLOR_PURPLE          GetColor(0x80, 0x00, 0x80)
#define COLOR_OLIVE           GetColor(0x80, 0x80, 0x00)
#define COLOR_LIGHTGREY       GetColor(0xD3, 0xD3, 0xD3)
#define COLOR_DARKGREY        GetColor(0xA9, 0xA9, 0xA9)
#define COLOR_WHITE           GetColor(0xFF, 0xFF, 0xFF)

// ブロックを表示するときの縦横
#define TETRIS_VIEW_WIDTH  10
#define TETRIS_VIEW_HEIGHT 20

// テトリス内部で使う変数
int score;
int cnt;
int button[4];

typedef struct
{
    int flg;
    int color;
}view_block_struct;

view_block_struct view_block[TETRIS_VIEW_HEIGHT][TETRIS_VIEW_WIDTH];
