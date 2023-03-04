//=========================================
//
//	camera.h
//	Author : 冨所知生
//
//=========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#define MAX_SPEED (1.0f)
#define CAMERA_HEIGHT (100.0f)

typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 posVDis;		//中心からプレイヤーまでの距離を正規化するための関数
	D3DXVECTOR3 rotDest;		//目的の角度
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxProjection;	// プロジェクトマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	float fDistance;			//視点から注視点の距離
}Camera;

//=========================================
// プロトタイプ宣言
//=========================================
void InitCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR);	// ポリゴンの初期化処理
void UninitCamera(void);								// ポリゴンの終了処理
void UpdateCamera(void);								// ポリゴンの更新処理
void SetCamera(void);									// ポリゴンの描画処理
Camera* GetCamera();									//カメラの情報の取得
float NormalizePos(float fPos);							//座標の補正

#endif

