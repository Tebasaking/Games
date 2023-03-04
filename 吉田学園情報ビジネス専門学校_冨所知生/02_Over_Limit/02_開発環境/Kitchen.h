//=========================================
//
//	model.h
//	Author : 冨所知生
//
//=========================================
#ifndef _KITCHEN_H_								
#define _KITCHEN_H_							

#define MAX_KITCHEN (3)
#define MAX_KITCHEN_PARTS (3)

#include "contain.h"

typedef enum
{
	KITCHEN_NONE,							//調理道具に何も入っていない状態
	KITCHEN_MATERIAL,						//調理する前、素材が乗っているだけ
	KITCHEN_COOK,							//調理中
	KITCHEN_COMPLETE,						//完成した状態
	KITCHEN_OVER,							//加熱しすぎている状態
	KITCHEN_BURN							//焦げて使えなくなった状態
}KITCHEN_COOKING;

//プレイヤーのパーツの構造体
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;			//角度
	D3DXVECTOR3 posOrigin;		//元の位置
	D3DXVECTOR3 rotOrigin;		//元の角度
	D3DXVECTOR3 posDest;		//目的の位置
	D3DXVECTOR3 rotDest;		//目的の向き
	D3DXVECTOR3 vtxMin;			//プレイヤーの最小値
	D3DXVECTOR3 vtxMax;			//プレイヤーの最大値
	D3DXVECTOR3 MovePos;		//モーションのときのPos
	D3DXVECTOR3 fFrame;			//フレーム数でアニメーションを割った数値を格納する
	bool bUse;					//使っているかいないか
	int nIdxModelParent;		//親モデルのインデックス
	int nType;					//パーツのタイプ
}KITCHENPARTS;

typedef enum
{
	KITCHEN_NORMAL = 0,						//アイテムの通常状態
	KITCHEN_HAVE = 1						//アイテムを持っているか持っていないか
}KITCHEN_STATE;

typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXVECTOR3 rotOld;							//プレイヤーが置いた時の位置を保存する
	D3DXVECTOR3 move;							//移動
	D3DXVECTOR3 rotDestKitchen;					//目的の座標
	D3DXVECTOR3 vtxMinKitchen;					//モデルの最小値
	D3DXVECTOR3 vtxMaxKitchen;					//モデルの最大値
	D3DXMATRIX  mtxWorldKitchen;				//ワールドマトリックス
	LPD3DXMESH pMeshKitchen;					//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatKitchen;				//マテリアル情報へのポインタ
	DWORD nNumMatKitchen;						//マテリアル情報の数
	KITCHEN_STATE state;						//キッチンのステート
	KITCHEN_COOKING cook;						//キッチンの変化する状態
	KITCHENPARTS aParts[MAX_KITCHEN_PARTS];		//キッチンのパーツ
	ITEMTYPE type;								//アイテムのタイプ
	bool  bUse;									//使用しているかしていないか
	bool  bTimer;								//キッチンタイマーを使用しているかいないか
	float ShadowSize;							//モデルと影の距離を求める
	int  Shadow;								//モデルの下にある影
	char KITCHEN_NAME[128];						//ファイルの名前
	int CookCount;								//調理時間
}KITCHEN;

//=========================================
//プロトタイプ宣言
//=========================================
void InitKitchen(void);
void UninitKitchen(void);
void UpdateKitchen(void);
void DrawKitchen(void);
KITCHEN* GetKitchen(void);
void SetKitchen(D3DXVECTOR3 pos, KITCHEN_STATE state);
void TSKitchen(D3DXVECTOR3 pos, char KITCHEN_NAME[128], int nCnt);
int GetSelectKitchen();
int GetKitchenDistance();
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
void PlayerDistanceKitchen(void);
void SetKitchenParts(D3DXVECTOR3 pos, char PLAYER_NAME[128], int nCount);
void LetsCooking(void);

#endif