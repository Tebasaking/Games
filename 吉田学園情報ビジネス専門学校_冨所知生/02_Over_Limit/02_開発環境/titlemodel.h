//=========================================
//
//	model.h
//	Author : 冨所知生
//
//=========================================
#ifndef _TITLEMODEL_H_								
#define _TITLEMODEL_H_							

#define MAX_TITLEMODEL (12)
#define KITCHEN_SIZE (10)
#define DISH_SIZE	(8)
#define MAX_TITLE_TEXTURE (30)

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXCOLOR	col;					//モデルの色
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rotDestTitleModel;		//目的の座標
	D3DXVECTOR3 vtxMinTitleModel;		//モデルの最小値
	D3DXVECTOR3 vtxMaxTitleModel;		//モデルの最大値
	D3DXMATRIX  mtxWorldTitleModel;		//ワールドマトリックス
	LPD3DXMESH pMeshTitleModel;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatTitleModel;	//マテリアル情報へのポインタ
	LPDIRECT3DTEXTURE9	pTexture[MAX_TITLE_TEXTURE];	// テクスチャへのポインタ
	DWORD nNumMatTitleModel;			//マテリアル情報の数
	int   Type;							//モデルのタイプ
	int	  Shadow;						//モデルの下にある影
	int	  CookCount;					//調理している時間
	float ShadowSize;					//モデルと影の距離を求める
	bool  bUse;							//使用しているかしていないか
	bool  bIsLanding;					//上にアイテムがないか
	bool  cook;							//調理中かどうか
	char MODEL_NAME[128];				//ファイルの名前
}TITLEMODEL;

//=========================================
//プロトタイプ宣言
//=========================================
void InitTitleModel(void);
void UninitTitleModel(void);
void UpdateTitleModel(void);
void DrawTitleModel(void);
void Cutting(void);
TITLEMODEL* GetTitleModel(void);
void SetTitleModel(D3DXVECTOR3 pos, char MODEL_NAME[128], int nCnt, int nType);
float VertexMAXChange(float vtx, float max);
float VertexMINChange(float vtx, float min);
int GetSelectObject();
int GetObjectDistance();

#endif