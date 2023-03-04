//=========================================
//
//	shadow.h
//	Author : 冨所知生
//
//=========================================
#ifndef _WALL_H_								
#define _WALL_H_							

#include "meshfield.h"

#define MAX_WALL (100)							//壁の最大数
#define WALL_SIZE (5.0f * MESH_X_BLOCK)			//壁のサイズ

typedef struct
{
	D3DXVECTOR3 pos;					//座標
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rot;					//回転
	D3DXCOLOR	col;					//色
	D3DXMATRIX  mtxWall;				//ワールドマトリックス
	bool bUse;							//使用しているかしていないか
	float size;							//壁のサイズ
}Wall;

//=========================================
//プロトタイプ宣言
//=========================================
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
Wall* GetWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot , D3DXCOLOR col);					//壁の設置

#endif
