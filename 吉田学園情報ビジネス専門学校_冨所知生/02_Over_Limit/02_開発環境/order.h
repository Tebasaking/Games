//========================================================
//ゲーム画面のヘッダーファイル
//========================================================
#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#define NUM_ORDER (5)
#define ORDER_SIZE (150.0f)

#include "main.h"
#include "contain.h"

typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DXCOLOR	col;		//色
	bool		bUse;		//使っているかいないか
	ITEMTYPE	nType;		//注文の種類
	int			nNumber;	//オーダーの配列の番号を入れる箱
	int			nLimit;		//期限
}ORDER;

//プロトタイプ宣言
void InitOrder(void);
void UninitOrder(void);
void UpdateOrder(void);
void DrawOrder(void);
void SetOrder(D3DXVECTOR3 pos, ITEMTYPE Type);
void RandamOrder(void);
ORDER *GetOrder(void);
void SubOrderCount();
void MoveOrder(int nNumber);


#endif