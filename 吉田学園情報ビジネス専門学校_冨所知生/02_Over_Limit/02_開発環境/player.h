//=========================================
//
//	player.h
//	Author : 冨所知生
//
//=========================================
#ifndef _PLAYER_H_								
#define _PLAYER_H_							

#define MAX_PLAYER (1)
#define MAX_PARTS (2)
#define PLAYER_MOVE (1.0f)
#define MAX_KEY	(2)
#define MAX_KEY_SET (3)
#define MAX_ANIMATION (3)

//プレイヤーの状態
typedef enum
{
	PLAYER_NORMAL,
	PLAYER_HAVE,
	PLAYER_CUTTING,
	PLAYER_MAX
}PLAYERSTATE;

//プレイヤーのパーツの構造体
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;			//プレイヤーの移動量
	D3DXVECTOR3 rot;
	D3DXVECTOR3 posOrigin;		//元の位置
	D3DXVECTOR3 rotOrigin;		//元の角度
	D3DXVECTOR3 posDest;		//目的の位置
	D3DXVECTOR3 rotDest;		//目的の向き
	D3DXVECTOR3 vtxMin;			//プレイヤーの最小値
	D3DXVECTOR3 vtxMax;			//プレイヤーの最大値
	D3DXVECTOR3 MovePos;		//モーションのときのPos
	D3DXVECTOR3 fFrame;			//フレーム数でアニメーションを割った数値を格納する
	int nIdxModelParent;		//親モデルのインデックス
	int nType;					//パーツのタイプ
}ModelParts;

//プレイヤーの構造体
typedef struct
{
	ModelParts aModel[MAX_PARTS];		//モデルのパーツの数
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 posOld;					//元々いた位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 move;					//移動
	D3DXVECTOR3 rotDestPlayer;			//目的の座標
	D3DXVECTOR3 vtxMinPlayer;			//プレイヤーの最小値
	D3DXVECTOR3 vtxMaxPlayer;			//プレイヤーの最大値
	D3DXVECTOR3 size;					//プレイヤーのサイズ
	D3DXMATRIX  mtxWorldPlayer;			//ワールドマトリックス
	LPD3DXMESH pMeshPlayer;				//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatPlayer;		//マテリアル情報へのポインタ
	DWORD nNumMatPlayer;				//マテリアル情報の数
	PLAYERSTATE state;					//プレイヤーのステート
	bool  bUse;							//使用しているかしていないか
	float ShadowSize;					//モデルと影の距離を求める
	int  Shadow;						//モデルの下にある影
	int  Number;						//どのパーツを動かすか
	char PLAYER_NAME[128];				//ファイルの名前
}PLAYER;

//キーごとの構造体
typedef struct
{
	D3DXVECTOR3 pos;					//座標
	D3DXVECTOR3 rot;					//回転
}Key;

//キーの一連の流れを管理する構造体
typedef struct
{
	float nFRAME;						//現在のフレーム数
	Key aKey[MAX_KEY];					//キーの構造体の配列
}KeySet;

//アニメーションの一連の流れを管理する構造体
typedef struct
{
	bool bLOOP;							//ループをするかしないか
	int	 nNUM_KEY;						//キーの個数
	KeySet aKeySet[MAX_KEY_SET];		//キーの一連の構造体の配列
}MotionSet;

//=========================================
//プロトタイプ宣言
//=========================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);
void SetPlayer(D3DXVECTOR3 pos);
void SetParts(D3DXVECTOR3 pos, char PLAYER_NAME[128],int nCnt);
void LoadAnimation(int AnimNumber, int KeyNumber, int Number, bool bLoop, int NUM_KEY, int FRAME, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void MotionPlayer(int nCntMotionSet);
void Cutting(void);
MotionSet *GetMotionSet(void);

#endif