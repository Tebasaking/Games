//=========================================
//
//	item.h
//	Author : 冨所知生
//
//=========================================
#ifndef _ITEM_H_								
#define _ITEM_H_							

#define MAX_ITEM (1000)

#include "contain.h"

typedef enum
{
	ITEM_NORMAL = 0,						//アイテムの通常状態
	ITEM_HAVE = 1							//アイテムを持っているか持っていないか
}ITEM_STATE;

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rotDestItem;			//目的の座標
	D3DXVECTOR3 vtxMinItem;				//モデルの最小値
	D3DXVECTOR3 vtxMaxItem;				//モデルの最大値
	D3DXMATRIX  mtxWorldItem;			//ワールドマトリックス
	LPD3DXMESH pMeshItem;				//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatItem;			//マテリアル情報へのポインタ
	DWORD nNumMatItem;					//マテリアル情報の数
	ITEM_STATE state;					//アイテムのステート
	ITEMTYPE type;						//アイテムのタイプ
	bool  bUse;							//使用しているかしていないか
	bool  bCook;						//調理中かどうか
	bool  bCut;							//カットされているかしないか
	float ShadowSize;					//モデルと影の距離を求める
	int  Shadow;						//モデルの下にある影
	int  CuttingTime;					//アイテムの調理時間(包丁のみ)
	char ITEM_NAME[128];				//ファイルの名前
}ITEM;
//=========================================
//プロトタイプ宣言
//=========================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
ITEM* GetItem(void);
void SetItem(D3DXVECTOR3 pos, char ITEM_NAME[128], ITEM_STATE state, ITEMTYPE type, bool cut);
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
void SetMoveItem(D3DXVECTOR3 pos);
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
void PlayerDistanceItem(void);
void KitchenInput(void);
int GetSelectItem();

#endif