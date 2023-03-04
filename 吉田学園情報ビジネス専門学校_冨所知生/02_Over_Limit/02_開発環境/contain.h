//=========================================
//
//	model.h
//	Author : 冨所知生
//
//=========================================
#ifndef _CONTAIN_H_								
#define _CONTAIN_H_							

#define MAX_CONTAIN (3)

//=========================================
//アイテムの種類の宣言
//=========================================
typedef enum
{
	ITEM_NULL = 0,
	ITEM_MEAT = 1 << 0,
	ITEM_CABBAGE = 1 << 1,
	ITEM_PANS = 1 << 2,
}ITEMTYPE;

//=========================================
//構造体の宣言
//=========================================
typedef enum
{
	CONTAIN_NONE,							//何も乗っていない状態
	CONTAIN_COMPLETE,						//完成した状態
}CONTAIN_COOKING;

typedef enum
{
	CONTAIN_NORMAL = 0,						//アイテムの通常状態
	CONTAIN_HAVE = 1						//アイテムを持っているか持っていないか
}CONTAIN_STATE;

typedef enum
{
	MEAT,								//肉
	CABBAGE,							//キャベツ
	PANS,								//パンズ
	HAMBURGER							//ハンバーガー
}COOK;

typedef struct
{
	int meat;							//肉
	int cabbage;						//キャベツ
	int vegetable;						//野菜炒め
}FOOD_COUNT;

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rotDestContain;			//目的の座標
	D3DXVECTOR3 vtxMinContain;			//モデルの最小値
	D3DXVECTOR3 vtxMaxContain;			//モデルの最大値
	D3DXMATRIX  mtxWorldContain;		//ワールドマトリックス
	LPD3DXMESH pMeshContain;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatContain;		//マテリアル情報へのポインタ
	DWORD nNumMatContain;				//マテリアル情報の数
	CONTAIN_STATE state;				//キッチンのステート
	CONTAIN_COOKING cook;				//キッチンの変化する状態
	COOK  cooking;						//できた料理の状態
	ITEMTYPE type;						//アイテムの種類
	bool  bUse;							//使用しているかしていないか
	float ShadowSize;					//モデルと影の距離を求める
	int  Shadow;						//モデルの下にある影
	int	 food;							//アイテムの最終的な種類
	char CONTAIN_NAME[128];				//ファイルの名前
	int CookCount;						//調理時間
}CONTAIN;

//=========================================
//プロトタイプ宣言
//=========================================
void InitContain(void);
void UninitContain(void);	
void UpdateContain(void);
void DrawContain(void);
CONTAIN* GetContain(void);
FOOD_COUNT* GetFoodCount(void);
void SetContain(D3DXVECTOR3 pos, char CONTAIN_NAME[128], CONTAIN_STATE state);
void TSContain(D3DXVECTOR3 pos, CONTAIN_STATE state, CONTAIN_COOKING cook, ITEMTYPE type);
void CollisionContain(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
int GetSelectContain();
int GetContainDistance();
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
void PlayerDistanceContain(void);
void LetsCooking(void);
void Calculation(ITEMTYPE);
void UninitCalculation();
bool UseFood(ITEMTYPE type, unsigned int dish);

#endif