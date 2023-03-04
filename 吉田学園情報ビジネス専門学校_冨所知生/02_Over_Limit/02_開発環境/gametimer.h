//=========================================
//
//	ゲームタイマーの入出力処理
//	Author : 冨所知生
//
//=========================================
#ifndef _GAMETIMER_H_								
#define _GAMETIMER_H_							

#include "main.h"

#define MAX_GAMETIMER (36)

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXCOLOR   col;					//色	
	D3DXMATRIX  mtxWorld;				//ワールドマトリックス
	LPD3DXMESH  pMeshGameTimer;				//メッシュ情報へのポインタ
	bool  bUse;							//使用しているかしていないか
}GAMETIMER;

//=========================================
//プロトタイプ宣言
//=========================================
void InitGameTimer(void);
void UninitGameTimer(void);
void UpdateGameTimer(void);
void DrawGameTimer(void);
void SetGameTimer(int nGameTimer);
void SubGameTimer(int nValue);
bool GetGTimer(void);
int GetGameTimer(void);

#endif