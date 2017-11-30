#ifndef COMMON_H
#define COMMON_H

#define DDX_GCC_COMPILE
#define DDX_NON_INLINE_ASM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./DxLib/DxLib.h"

// 画面サイズの定義
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define CHARA_BUF_WIDTH   80
#define CHARA_BUF_HEIGHT  60
#define CHARA_WIDTH (SCREEN_WIDTH / CHARA_BUF_WIDTH)
#define CHARA_HEIGHT (SCREEN_HEIGHT / CHARA_BUF_HEIGHT)

// ボタンの数
#define NUM_BUTTON 4

// ボタンの役割
#define BUTTON_RIGHT  1
#define BUTTON_LEFT   2
#define BUTTON_ROTATE 3

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

// テトリス内部で使う変数
extern int score;
extern int cnt;
extern int button[4];

// 状態を入れておく変数
typedef enum {
    DEMONSTRATION,
    PLAYING,
}states;

extern states state;

#endif