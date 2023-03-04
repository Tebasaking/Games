//=========================================
//
//	line.h
//	Author : 冨所知生
//
//=========================================
#ifndef _LINE_H_								
#define _LINE_H_							

#define MAX_LINE (1000)

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXCOLOR   col;					//色	
	D3DXMATRIX  mtxWorld;				//ワールドマトリックス
	LPD3DXMESH  pMeshLine;				//メッシュ情報へのポインタ
	bool  bUse;							//使用しているかしていないか
}LINE;

//=========================================
//プロトタイプ宣言
//=========================================
void InitLine(void);
void UninitLine(void);
void DrawLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 start, D3DXVECTOR3 end);

#endif