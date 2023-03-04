//========================================================
//包丁の調理時間のヘッダーファイル
//========================================================
#ifndef _ORDERTIMER_H_
#define _ORDERTIMER_H_

#define MAX_ORDERTIMER (12)

#define OTIMER_WIDTH (8.0f)
#define OTIMER_HEIGHT (3.0f)

#include "main.h"

//=========================================
//構造体の宣言
//=========================================
typedef enum
{
	OTIMER_CONTAIN,				//タイマーの容器
	OTIMER_BAR					//タイマーのバー
}OTIMER_STATE;

typedef struct
{
	D3DXVECTOR3		pos;			//座標
	D3DXVECTOR3		rot;			//角度
	D3DCOLOR		col;			//色
	D3DXMATRIX		mtxWorld;		//ワールドマトリックス
	OTIMER_STATE	state;			//キッチンのステート
	int				nNumber;		//オーダーの番号、タイマーを消すときに使う
	bool			bUse;			//使っているか
	int				KitchenNumber;	//一番近かったキッチンの番号を保存する
}OTIMER;

//プロトタイプ宣言
void InitOTimer(void);
void UninitOTimer(void);
void UpdateOTimer(void);
void DrawOTimer(void);
void SetOTimer(D3DXVECTOR3 pos, int nNumber);
void SetOTimerBar(D3DXVECTOR3 pos, int nNumber);
void MoveOTimer(int nNumber);
OTIMER *GetOTimer();

#endif