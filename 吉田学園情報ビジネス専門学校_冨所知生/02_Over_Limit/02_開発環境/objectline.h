//=========================================
//
//	objectline.h
//	Author : 冨所知生
//
//=========================================
#ifndef _OBJECTLINE_H_								
#define _OBJECTLINE_H_							

#define MAX_OBJECTLINE (36)

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXCOLOR   col;					//色	
	D3DXMATRIX  mtxWorld;				//ワールドマトリックス
	LPD3DXMESH  pMeshObjectLine;				//メッシュ情報へのポインタ
	bool  bUse;							//使用しているかしていないか
}OBJECTLINE;

//=========================================
//プロトタイプ宣言
//=========================================
void InitObjectLine(void);
void UninitObjectLine(void);
void UpdateObjectLine(void);
void DrawObjectLine(void);
void SetObjectLine(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 start, D3DXVECTOR3 end);

#endif