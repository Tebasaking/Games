//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// タイトル
	SOUND_LABEL_BGM001,			// ゲーム画面
	SOUND_LABEL_BGM002,			// リザルト(勝利)
	SOUND_LABEL_BGM003,			// ゲームオーバー(敗北)
	SOUND_LABEL_BGM_BOSS,		//ボス戦のBGM
	SOUND_LABEL_PAGE,			//チュートリアルのページをめくった音
	SOUND_LABEL_BELL,			//ゲームを始めた音
	SOUND_LABEL_SELECT,			//タイトルで選択してるものをずらした時の音
	SOUND_LABEL_CUTTING,		//物を切る処理
	SOUND_LABEL_HOT,			//加熱音
	SOUND_LABEL_OPEN,			//箱を開ける音
	SOUND_LABEL_HOTOVER,		//焦げ付く音
	SOUND_LABEL_WHISTLE,		//ホイッスルの音
	SOUND_LABEL_REGI,		//ボスが倒れる音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
#pragma once
