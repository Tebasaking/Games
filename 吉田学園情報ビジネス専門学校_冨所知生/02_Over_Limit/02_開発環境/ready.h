//========================================================
//ゲーム開始の合図のヘッダーファイル
//========================================================
#pragma once
#ifndef _READY_H_
#define _READY_H_

#define NUM_READY (7)

typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DXCOLOR	col;		//色
	bool		bUse;		//使っているかいないか
	int			nType;		//タイプ
}READY;

//プロトタイプ宣言
void InitReady(void);
void UninitReady(void);
void UpdateReady(void);
void DrawReady(void);
void SetReady(int nType);
bool GetReady(void);


#endif