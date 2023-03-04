//=========================================
//
//	カメラの設置と制御など
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "fade.h"

//------------------------------------
// グローバル変数
//------------------------------------
Camera g_camera;	// カメラ情報
float fLengthX;
float fLengthY;
float fLengthZ;
int   AfkCheck;		//モデルを動かしてない時間を計測
//=========================================
// 初期化処理
//=========================================
void InitCamera(D3DXVECTOR3 posV , D3DXVECTOR3 posR)
{
	// 視点・注視点・上方向を設定する
	g_camera.posV = posV;									//視点
	g_camera.posR = posR;									//注視点
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//ベクトル
	g_camera.rot = D3DXVECTOR3(0.0f , 0.0f, 0.0f);			//角度
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//距離の算出
	fLengthX = g_camera.posV.x - g_camera.posR.x;			//x^2
	fLengthY = g_camera.posV.y - g_camera.posR.y;			//z^2
	fLengthZ = g_camera.posV.z - g_camera.posR.z;			//y^2
	
	//放置してるかの検出
	AfkCheck = 0;

	//注視点の向きを設定
	g_camera.rot.x = atan2f(fLengthY, fLengthZ);

	//算出
	g_camera.fDistance = sqrtf((fLengthX * fLengthX) + (fLengthZ * fLengthZ));		//距離
	g_camera.fDistance = sqrtf((fLengthY * fLengthY) + (g_camera.fDistance * g_camera.fDistance));	//距離2
}

//=========================================
// 終了処理
//=========================================
void UninitCamera(void)
{
}

//=========================================
// 更新処理
//=========================================
void UpdateCamera(void)
{
	PLAYER *pPlayer = GetPlayer();

	//目的の角度の設定
	g_camera.rotDest.y = pPlayer->rot.y + D3DX_PI;

	////注視点の旋回
	//{
	//	if (GetKeyboardPress(DIK_Z))
	//	{
	//		g_camera.rot.y -= 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_C))
	//	{
	//		g_camera.rot.y += 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_U))
	//	{// 上に移動する
	//		g_camera.rot.x -= 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_J))
	//	{// 下に移動する
	//		g_camera.rot.x += 0.01f;
	//	}
	//}

	//{
	//	//視点の移動
	//	if (GetKeyboardPress(DIK_UP))
	//	{//前に移動する
	//		g_camera.posV.x += sinf(g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z += cosf(g_camera.rot.y) * 0.5f;
	//	}
	//	else if (GetKeyboardPress(DIK_DOWN))
	//	{//後ろに移動する
	//		g_camera.posV.x -= sinf(g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y) * 0.5f;
	//	}
	//	else if (GetKeyboardPress(DIK_LEFT))
	//	{//左に移動する
	//		g_camera.posV.x -= sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z -= cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//	}
	//	else if (GetKeyboardPress(DIK_RIGHT))
	//	{//右に移動する
	//		g_camera.posV.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//		g_camera.posV.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	//	}
	//	if (GetKeyboardPress(DIK_N))
	//	{
	//		g_camera.posV.y -= 0.1f;
	//	}
	//	else if (GetKeyboardPress(DIK_M))
	//	{
	//		g_camera.posV.y += 0.1f;
	//	}
	//}

	//{
	//	//視点の旋回
	//	if (GetKeyboardPress(DIK_Q))
	//	{
	//		g_camera.rot.y -= 0.01f;
	//	}
	//	else if (GetKeyboardPress(DIK_E))
	//	{
	//		g_camera.rot.y += 0.01f;
	//	}
	//}

	//角度の目的地の正規化
	if (g_camera.rotDest.y - g_camera.rot.y > D3DX_PI)
	{
		g_camera.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rotDest.y - g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rotDest.y += D3DX_PI * 2.0f;
	}

	////カメラの向いている方向をプレイヤーの向いている方向に寄せる
	//if(!GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_A) && !GetKeyboardPress(DIK_S) && !GetKeyboardPress(DIK_D))
	//{
	//	//AFKを検知したら加算
	//	AfkCheck++;

	//	if (AfkCheck >= 180)
	//	{
	//		g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * 0.05f;
	//	}
	//}
	//else
	//{
	//	AfkCheck = 0;
	//}

	//プレイヤーの座標を代入する
	g_camera.posVDis = pPlayer->pos;

	//座標の補正を行う
	g_camera.posVDis.x = NormalizePos(g_camera.posVDis.x);
	g_camera.posVDis.y = NormalizePos(g_camera.posVDis.y);
	g_camera.posVDis.z = NormalizePos(g_camera.posVDis.z);

	//角度の正規化
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

	//角度の正規化
	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x += D3DX_PI * 2.0f;
	}

	//目的の注視点の設定
	/*g_camera.posRDest.x = pPlayer->pos.x * 0.1f ;
	g_camera.posRDest.z = pPlayer->pos.z * 0.1f ;*/

	//目的の視点の設定
	//g_camera.posVDest.x = pPlayer->pos.x * 0.1f;
	g_camera.posVDest.y = g_camera.posVDis.x / 5.0f + g_camera.posVDis.z / 5.0f + CAMERA_HEIGHT;		//マジックナンバー
	//g_camera.posVDest.z = pPlayer->pos.z * 0.1f;

	//視点の減衰処理
	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;.
	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;

	/*g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;*/
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
}

//=========================================
// 設定処理
//=========================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);	// ビュー座標行列の設定

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),	// 視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// アスペクト比
		0.1f, 10000000.0f);	// どこから(ニア)(第５引数)どこまで(ファー)(第６引数)を表示するか設定 

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//=========================================
// カメラの情報の取得
//=========================================
Camera* GetCamera()
{
	return &g_camera;
}

//=========================================
// posの正規化
//=========================================
float NormalizePos(float fPos)
{
	if (fPos < 0)
	{
		fPos = -fPos;
	}
	return fPos;
}