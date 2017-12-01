#include "common.h"
#include "view.h"
#include "tetris.h"
#include "main.h"

void debug_output();
void check_buttons();
void reset_buttons();

int cnt=0;
int button[4];
states state;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	SetMainWindowText("tetris");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);

	if( DxLib_Init() == -1 || SetDrawScreen(-2) != 0 )
		return -1;
	
	switch_state(DEMONSTRATION);

	while(ProcessMessage() == 0)
	{
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK, TRUE);
		clsDx();

		check_buttons();

		switch(state)
		{
			case DEMONSTRATION:	
				draw_appearance();
				if(cnt%10==0)
					demo();
				draw_block();
				draw_dialogue("DEMONSTRATION");
				if(button[BUTTON_ROTATE]==1)
					switch_state(PLAYING);
				break;
			case PLAYING:
				tetris_update();
				draw_appearance();
				draw_block();
				draw_next_block();
				break;
			case GAMEOVER:
				draw_appearance();
				draw_block();
				draw_dialogue("GAMEOVER");
				if(button[BUTTON_ROTATE]==1)
					switch_state(DEMONSTRATION);
				break;
		}

		debug_output();
		ScreenFlip();
		cnt++;
	}

	DxLib_End();

	return 0 ;
}

// デバッグ用の出力. ボタンが押されてるかなどを表示.
void debug_output()
{
	int i;
	char buf[20];

	sprintf(buf, "CNT: %06d\n", cnt);
	printfDx(buf);
}

// 状態を変える関数. 状態遷移を起こす前の初期化などに使う.
void switch_state(states next_state)
{

    switch(next_state)
    {
        case DEMONSTRATION:
			reset_buttons();
			init_block();
            state = DEMONSTRATION;
            break;
        case PLAYING:
			reset_buttons();
			init_block();
			init_tetris();
            state = PLAYING;
            break;
		case GAMEOVER:
			reset_buttons();
			state = GAMEOVER;
			break;
    }
}

// ボタンの状態をリセットする.
void reset_buttons()
{
	int i;
	for(i=0; i<NUM_BUTTON; i++)
	{
		button[i] = 0;
	}
}

// ボタンが入力されているかどうかを取得する.
void check_buttons()
{
	int button_input[] = {KEY_INPUT_SEMICOLON, KEY_INPUT_L, KEY_INPUT_K, KEY_INPUT_J};
	int i;
	for(i=0; i<NUM_BUTTON; i++)
	{
		if(CheckHitKey(button_input[i]))
			button[i] += 1;
		else
			button[i] = 0;
	}
}