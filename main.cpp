#define DDX_GCC_COMPILE
#define DDX_NON_INLINE_ASM

#include "./main.h"

void init_block();
void draw_appearance();
void draw_block();
void demo();
void check_buttons();
void debug_output();

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	SetMainWindowText("tetris");
	SetGraphMode(320, 240, 16);

	if( DxLib_Init() == -1 || SetDrawScreen(-2) != 0 )
		return -1;
	
	init_block();

	while(ProcessMessage() == 0)
	{
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK, TRUE);
		clsDx();

		check_buttons();

		if(cnt%10==0)
			demo();

		draw_appearance();

		draw_block();

		debug_output();
		ScreenFlip();
		cnt++;
	}

	DxLib_End();

	return 0 ;
}

// 基本的な外観を描画する.
void draw_appearance()
{
	int x,y;
	// ブロックが入るスペース
	x=45;
	y=20;
	DrawBox(    x,     y,   x+4, y+205, COLOR_DARKGREY, TRUE);
	DrawBox(x+106,     y, x+110, y+205, COLOR_DARKGREY, TRUE);
	DrawBox(  x+5, y+201, x+105, y+205, COLOR_DARKGREY, TRUE);
	// 次のブロックを表示する場所
	x=165;
	y=20;
	DrawBox(   x,    y, x+60,  y+5, COLOR_DARKGREY, TRUE);
	DrawBox(   x,    y,  x+5, y+60, COLOR_DARKGREY, TRUE);
	DrawBox(x+55,    y, x+60, y+60, COLOR_DARKGREY, TRUE);
	DrawBox(   x, y+55, x+60, y+60, COLOR_DARKGREY, TRUE);
	DrawString(x, y, "NEXT", COLOR_WHITE);
	//スコア用のスペース
	x=165;
	y=100;
	char buf[20];
	sprintf(buf, "SCORE: %06d", score);
	DrawString(x, y, buf, COLOR_WHITE);
}

// デバッグ用の出力. ボタンが押されてるかなどを表示.
void debug_output()
{
	int i;
	char buf[20];

	sprintf(buf, "CNT: %06d\n", cnt);
	printfDx(buf);
	
	for(i=0; i<NUM_BUTTON; i++)
	{
		sprintf(buf, "BUTTON[%d]: %04d\n", i, button[i]);
		printfDx(buf);
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
				DrawBox(ulx+1, uly+1, ulx+9, uly+9, view_block[y][x].color, TRUE );
			}
		}
	}
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

// ボタンが入力されているかどうかを取得する.
void check_buttons()
{
	int button_input[] = {KEY_INPUT_J, KEY_INPUT_K, KEY_INPUT_L, KEY_INPUT_SEMICOLON};
	int i;
	for(i=0; i<NUM_BUTTON; i++)
	{
		if(CheckHitKey(button_input[i]))
			button[i] += 1;
		else
			button[i] = 0;
	}
}