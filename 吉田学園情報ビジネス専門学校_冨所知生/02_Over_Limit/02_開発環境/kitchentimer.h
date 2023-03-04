//========================================================
//キッチンタイマーのヘッダーファイル
//========================================================
#ifndef _KITCHENTIMER_H_
#define _KITCHENTIMER_H_

#define MAX_KITCHENTIMER (100)

#define KTIMER_WIDTH (8.0f)
#define KTIMER_HEIGHT (3.0f)

#include "main.h"

//=========================================
//構造体の宣言
//=========================================
typedef enum
{
	KTIMER_CONTAIN,				//タイマーの容器
	KTIMER_BAR					//タイマーのバー
}KTIMER_STATE;

typedef struct
{
	D3DXVECTOR3		pos;			//座標
	D3DXVECTOR3		rot;			//角度
	D3DCOLOR		col;			//色
	D3DXMATRIX		mtxWorld;		//ワールドマトリックス
	KTIMER_STATE	state;			//キッチンのステート
	bool			bUse;			//使っているか
	int				KitchenNumber;	//一番近かったキッチンの番号を保存する
}KTIMER;

//プロトタイプ宣言
void InitKTimer(void);
void UninitKTimer(void);
void UpdateKTimer(void);
void DrawKTimer(void);
void SetKTimer(D3DXVECTOR3 pos);
void SetKTimerBar(D3DXVECTOR3 pos);
KTIMER *GetKTimer();

#endif