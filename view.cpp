#include "common.h"
#include "view.h"

// ブロックを表示するときの縦横
#define TETRIS_VIEW_WIDTH  10
#define TETRIS_VIEW_HEIGHT 20

typedef struct
{
    int flg;
    int color;
}view_block_struct;

view_block_struct view_block[TETRIS_VIEW_HEIGHT][TETRIS_VIEW_WIDTH];

// 四角形を描画する 移植を容易にするための処置.
void render_box(int x1, int y1, int x2, int y2, int color)
{
	DrawBox(x1, y1, x2, y2, color, TRUE);
}

// 文字を描画する これも上に同じ
void render_char(int x, int y, const char *string)
{
	DrawString(x, y, string, COLOR_WHITE);
}

// 基本的な外観を描画する.
void draw_appearance()
{
	int x,y;
	// ブロックが入るスペース
	x=45;
	y=20;
	render_box(    x,     y,   x+4, y+205, COLOR_DARKGREY);
	render_box(x+106,     y, x+110, y+205, COLOR_DARKGREY);
	render_box(  x+5, y+201, x+105, y+205, COLOR_DARKGREY);
	// 次のブロックを表示する場所
	x=165;
	y=20;
	render_box(   x,    y, x+60,  y+5, COLOR_DARKGREY);
	render_box(   x,    y,  x+5, y+60, COLOR_DARKGREY);
	render_box(x+55,    y, x+60, y+60, COLOR_DARKGREY);
	render_box(   x, y+55, x+60, y+60, COLOR_DARKGREY);
	render_char(x, y, "NEXT");
	//スコア用のスペース
	x=165;
	y=100;
	char buf[20];
	sprintf(buf, "SCORE: %06d", score);
	render_char(x, y, buf);
}

// ダイアログの表示
void draw_dialogue(const char *string)
{
	render_box(0, SCREEN_HEIGHT/2-10, SCREEN_WIDTH, SCREEN_HEIGHT/2+10, COLOR_NAVY);
	int len = strlen(string);
	render_char((SCREEN_WIDTH/2)-(len*CHARA_WIDTH/2), SCREEN_HEIGHT/2, string);
}

// ブロックを全部リセットする.
void init_block()
{
	int x,y;
	for(y=0; y<TETRIS_VIEW_HEIGHT; y++)
	{
		for(x=0; x<TETRIS_VIEW_WIDTH; x++)
		{
			view_block[y][x].flg = 0;
			view_block[y][x].color = COLOR_BLACK;
		}
	}
}

// 適当な色のブロックを表示しておく.
void demo()
{
	int x,y;
	int colors[] = {COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW, COLOR_RED, COLOR_PURPLE, COLOR_PINK, COLOR_ORANGE, COLOR_WHITE, COLOR_GREENYELLOW};
	for(y=0; y<TETRIS_VIEW_HEIGHT; y++)
	{
		for(x=0; x<TETRIS_VIEW_WIDTH; x++)
		{
			view_block[y][x].flg = 1;
			view_block[y][x].color = colors[rand()%9];
		}
	}
}

// ブロックを描画する.
void draw_block()
{
	int x,y;
	for(y=0; y<TETRIS_VIEW_HEIGHT; y++)
	{
		for(x=0; x<TETRIS_VIEW_WIDTH; x++)
		{
			if(view_block[y][x].flg)
			{
				// 50, 20はブロックのスペースの右上の座標
				int ulx = 50+x*10;
				int uly = 20+y*10;
				render_box(ulx+1, uly+1, ulx+9, uly+9, view_block[y][x].color);
			}
		}
	}
}