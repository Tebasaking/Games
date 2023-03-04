//=========================================
//
//	model.h
//	Author : 冨所知生
//
//=========================================
#ifndef _MODEL_H_								
#define _MODEL_H_							

#define MAX_MODEL (20)
#define KITCHEN_SIZE (10)
#define DISH_SIZE	(8)
#define MAX_TEXTURE (10)

#include "contain.h"

typedef enum
{
	MODEL_FOOD1_BOX = 0,				//食べ物の箱1
	MODEL_FOOD2_BOX = 4,				//食べ物の箱2
	MODEL_KITCHEN = 1,					//調理台
	MODEL_CONTAIN = 2,
	MODEL_COUNTER = 3					//カウンター
}TYPE;

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXCOLOR	col;					//モデルの色
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rotDestModel;			//目的の座標
	D3DXVECTOR3 vtxMinModel;			//モデルの最小値
	D3DXVECTOR3 vtxMaxModel;			//モデルの最大値
	D3DXMATRIX  mtxWorldModel;			//ワールドマトリックス
	LPD3DXMESH pMeshModel;				//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatModel;			//マテリアル情報へのポインタ
	// テクスチャへのポインタ
	LPDIRECT3DTEXTURE9	pTexture[MAX_TEXTURE];
	DWORD nNumMatModel;					//マテリアル情報の数
	int  Type;							//モデルのタイプ
	int	  Shadow;						//モデルの下にある影
	int	  CookCount;					//調理している時間
	float ShadowSize;					//モデルと影の距離を求める
	bool  bUse;							//使用しているかしていないか
	bool  bIsLanding;					//上にアイテムがないか
	bool  cook;							//調理中かどうか
	char MODEL_NAME[128];				//ファイルの名前
}MODEL;

//=========================================
//プロトタイプ宣言
//=========================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void UpdateHot(void);
void DrawModel(void);
void PlayerDistanceModel(void);
void Cutting(void);
MODEL* GetModel(void);
void SetModel(D3DXVECTOR3 pos, char MODEL_NAME[128], int nCnt ,int nType);
void CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
int GetSelectObject();
int GetObjectDistance();
void SubDContain();

#endif