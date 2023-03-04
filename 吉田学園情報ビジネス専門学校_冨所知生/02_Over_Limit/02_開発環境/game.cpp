//========================================================
// 
//	ゲーム画面の処理
//	Author : 冨所知生
//
//========================================================
#include "main.h"
#include "camera.h"
#include "polygon.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "file.h"
#include "meshfield.h"
#include "cylinder.h"
#include "sphere.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "line.h"
#include "item.h"
#include "objectline.h"
#include "Kitchen.h"
#include "contain.h"
#include "kitchentimer.h"
#include "cuttingtimer.h"
#include "ordertimer.h"
#include "order.h"
#include "gametimer.h"
#include "score.h"
#include "ready.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;
//========================================================
//ゲームの初期化処理
//========================================================
void InitGame(void)
{
	//準備画面の初期化処理
	InitReady();

	//カメラの初期化処理
	InitCamera(D3DXVECTOR3(0.0f, 120.0f, -70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//壁の初期化処理
	InitWall();

	//円柱の初期化
	InitSphere();

	////メッシュフィールドの初期化
	InitMesh();

	//ライトの初期化処理
	InitLight();

	//影の初期化処理
	InitShadow();

	//プレイヤーの初期化設定
	InitPlayer();

	//線の初期化設定
	InitLine();

	//強調表示ラインの初期化処理
	InitObjectLine();

	//容器の初期化設定
	InitContain();

	//キッチンの初期化設定
	InitKitchen();

	//モデルの初期化処理
	InitModel();

	//ファイルの初期化設定
	InitFile();

	//アニメーションの初期化設定
	MotionFile();

	//ビルボードの初期化設定
	InitBillboard();

	//エフェクトの初期化設定
	InitEffect();

	//パーティクルの初期化設定
	InitParticle();

	//アイテムの初期化設定
	InitItem();

	//キッチンタイマーの初期化
	InitKTimer();

	//カットタイマーの初期化
	InitCTimer();

	//オーダータイマーの初期化
	InitOTimer();

	//注文の初期化
	InitOrder();

	//ゲームタイマーの初期化
	InitGameTimer();

	//スコアの初期化
	InitScore();

	//壁の設置
	SetWall(D3DXVECTOR3(+MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//SetWall(D3DXVECTOR3(+MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	//SetWall(D3DXVECTOR3(-MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetWall(D3DXVECTOR3(-MESH_SIZE / 2 * MESH_X_BLOCK, +WALL_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, +MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, +MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, -MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	SetWall(D3DXVECTOR3(0.0f, +WALL_SIZE, -MESH_SIZE / 2 * MESH_Z_BLOCK), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, -D3DX_PI * 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//ビルボードの設置									   
	SetBillboard(D3DXVECTOR3(MESH_SIZE / 2 + 10.0f, 15.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ビルボードの設置
	SetBillboard(D3DXVECTOR3(MESH_SIZE / 2 - 10.0f, 15.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ゲームタイマーの設置
	SetGameTimer(120);
	//スコアの設置
	SetScore(0);

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//========================================================
//ゲームの終了処理
//========================================================
void UninitGame(void)
{
	//サウンドの終了
	StopSound();

	//準備画面の終了処理
	UninitReady();

	//メッシュの終了処理
	UninitMesh();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//影の終了処理
	UninitShadow();

	//モデルの終了処理
	UninitModel();

	//プレイヤーの終了処理
	UninitPlayer();

	//壁の終了処理
	UninitWall();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//ビルボードの終了処理
	UninitBillboard();

	//線の終了処理
	UninitLine();

	//強調表示ラインの終了処理
	UninitObjectLine();

	//アイテムの終了処理
	UninitItem();

	//キッチンの終了処理
	UninitKitchen();

	//容器の初期化設定
	UninitContain();

	//キッチンタイマーの終了処理
	UninitKTimer();

	//カットタイマーの終了処理
	UninitCTimer();

	//オーダータイマーの終了処理
	UninitOTimer();

	//注文の終了処理
	UninitOrder();

	//ゲームタイマーの終了処理
	UninitGameTimer();

	//スコアの終了処理
	UninitScore();
}

//========================================================
//ゲームの更新処理
//========================================================
void UpdateGame(void)
{
	//準備の情報の取得
	bool bReady = GetReady();
	//ゲームタイマーの使用状況の取得
	bool bGTimer = GetGTimer();

	//準備画面の更新処理
	UpdateReady();

	//準備が完了したとき
	if (bReady)
	{
		if (!bGTimer)
		{
			//円柱の更新処理
			UpdateSphere();

			//メッシュの更新処理
			UpdateMesh();

			//カメラの更新処理
			UpdateCamera();

			//ライトの更新処理
			UpdateLight();

			//影の更新処理
			UpdateShadow();

			//プレイヤーの更新処理
			UpdatePlayer();

			//強調表示ラインの更新処理
			UpdateObjectLine();

			//モデルの更新処理
			UpdateModel();

			//壁の更新処理
			UpdateWall();

			//エフェクトの更新処理
			UpdateEffect();

			//パーティクルの更新処理
			UpdateParticle();

			//ビルボードの更新処理
			UpdateBillboard();

			//容器の更新設定
			UpdateContain();

			//キッチンの更新処理
			UpdateKitchen();

			//アイテムの更新処理
			UpdateItem();

			//プレイヤーの近くのラインを光らせる処理
			PlayerDistanceModel();

			//キッチンタイマーの更新処理
			UpdateKTimer();

			//カットタイマーの更新処理
			UpdateCTimer();

			//オーダータイマーの更新処理
			UpdateOTimer();

			//注文の更新処理
			UpdateOrder();

			//注文をランダムで一定時間毎に生成する処理
			RandamOrder();

			//スコアの更新処理
			UpdateScore();
		}
		//ゲームタイマーの更新処理
		UpdateGameTimer();
	}

	//if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A, 0))
	//{
	//	SetMode(MODE_RESULT);
	//}
}

//========================================================
//ゲームの描画処理
//========================================================
void DrawGame(void)
{	
	//カメラの設定処理
	SetCamera();

	////壁の描画処理
	DrawWall();

	//////ポリゴンの描画処理
	//DrawPolygon();

	////メッシュの描画処理
	DrawMesh();

	//影の描画処理
	DrawShadow();

	//プレイヤーの描画処理
	DrawPlayer();

	//モデルの描画処理
	DrawModel();

	////円柱の描画処理
	//DrawSphere();

	////ビルボードの描画処理
	//DrawBillboard();

	//エフェクトの描画処理
	DrawEffect();

	//パーティクルのの描画処理
	DrawParticle();

	//ラインの描画処理
	DrawLine();

	//強調表示ラインの描画処理
	DrawObjectLine();

	//容器の描画設定
	DrawContain();

	//アイテムの描画処理
	DrawItem();

	//キッチンの描画処理
	DrawKitchen();

	//キッチンタイマーの描画処理
	DrawKTimer();

	//カットタイマーの描画処理
	DrawCTimer();

	//オーダータイマーの描画処理
	DrawOTimer();

	//注文の描画処理
	DrawOrder();

	//ゲームタイマーの描画処理
	DrawGameTimer();

	//スコアの描画処理
	DrawScore();

	//準備画面の描画処理
	DrawReady();
}