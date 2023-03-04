//=========================================
//
//	shadow.h
//	Author : 冨所知生
//
//=========================================
#ifndef _BILLBOARD_H_								
#define _BILLBOARD_H_							

#define MAX_BILLBOARD (100)				//ビルボードの最大数
#define BILLBOARD_SIZE (10.0f)			//ビルボードのサイズ

typedef struct
{
	D3DXVECTOR3 pos;					//座標
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rot;					//回転
	D3DXCOLOR	col;					//色
	D3DXMATRIX  mtxWorld;				//ワールドマトリックス
	bool bUse;							//使用しているかしていないか
	float size;							//ビルボードのサイズ
}Billboard;

//=========================================
//プロトタイプ宣言
//=========================================
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
Billboard* GetBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					//ビルボードの設置

#endif
