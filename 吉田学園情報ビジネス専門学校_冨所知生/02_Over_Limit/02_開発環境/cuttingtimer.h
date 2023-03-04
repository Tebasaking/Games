//========================================================
//包丁の調理時間のヘッダーファイル
//========================================================
#ifndef _CUTTINGTIMER_H_
#define _CUTTINGTIMER_H_

#define MAX_CUTTINGTIMER (100)

#define CTIMER_WIDTH (8.0f)
#define CTIMER_HEIGHT (3.0f)

#include "main.h"

//=========================================
//構造体の宣言
//=========================================
typedef enum
{
	CTIMER_CONTAIN,				//タイマーの容器
	CTIMER_BAR					//タイマーのバー
}CTIMER_STATE;

typedef struct
{
	D3DXVECTOR3		pos;			//座標
	D3DXVECTOR3		rot;			//角度
	D3DCOLOR		col;			//色
	D3DXMATRIX		mtxWorld;		//ワールドマトリックス
	CTIMER_STATE	state;			//キッチンのステート
	bool			bUse;			//使っているか
	int				KitchenNumber;	//一番近かったキッチンの番号を保存する
}CTIMER;

//プロトタイプ宣言
void InitCTimer(void);
void UninitCTimer(void);
void UpdateCTimer(void);
void DrawCTimer(void);
void SetCTimer(D3DXVECTOR3 pos);
void SetCTimerBar(D3DXVECTOR3 pos);
CTIMER *GetCTimer();

#endif