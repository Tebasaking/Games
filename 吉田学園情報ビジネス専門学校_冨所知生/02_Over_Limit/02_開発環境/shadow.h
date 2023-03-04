//=========================================
//
//	shadow.h
//	Author : 冨所知生
//
//=========================================
#ifndef _SHADOW_H_								
#define _SHADOW_H_							

#define MAX_SHADOW (100)				//影の最大数
#define SHADOW_SIZE (1.5f)

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rot;					//回転
	D3DXMATRIX  mtxShadow;				//ワールドマトリックス
	bool bUse;							//使用しているかしていないか
	float size;							//影のサイズ
}Shadow;

//=========================================
//プロトタイプ宣言
//=========================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
Shadow* GetShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						//影の設置
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, float nSize);				//モデルに応じて影の位置を変える処理

#endif