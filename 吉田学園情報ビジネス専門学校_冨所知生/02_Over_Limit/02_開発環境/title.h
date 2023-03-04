//========================================================
//タイトル画面のヘッダーファイル
//========================================================
#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#define NUM_TITLE (7)

#include "main.h"

//=========================================
//構造体の宣言
//=========================================
typedef enum
{
	GAME = 0,			//ゲームを始める
	TUTORIAL = 1,		//チュートリアルを始める
	SHUTDOWN = 2		//ゲームをやめる
}TITLE_SELECT;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif