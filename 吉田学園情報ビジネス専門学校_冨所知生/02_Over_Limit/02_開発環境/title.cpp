//=============================================
//
//	タイトル画面の出力処理
//	Auhor : 冨所知生
//
//=============================================
#include "main.h"
#include "title.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "particle.h"
#include "titlemodel.h"
#include "file.h"
#include "camera.h"
#include "light.h"
#include "sound.h"

//グローバル関数
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = { NULL, NULL , NULL };			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
D3DXCOLOR g_TitleColor;
D3DXCOLOR g_TutorialColor;
int g_TitleColTimer;
int TutorialCnt = 0;
bool g_TitleColBlinking;
bool g_tutorial;
static int g_move;
bool MoveStart;
bool tutorial;
//タイトルの状態
TITLE_SELECT TitleSelect;
//=============================================
//タイトルの初期化処理
//=============================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	g_TitleColTimer = 0;
	g_move = 0;
	g_TitleColBlinking = false;
	g_TitleColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_TutorialColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_tutorial = false;
	MoveStart = false;
	TitleSelect = GAME;					//タイトルセレクトの初期位置の設定

	//デバイスの取得
	pDevice = GetDevice();

	//カメラの初期化
	InitCamera(D3DXVECTOR3(0.0f, 10.0f, 360.0f), D3DXVECTOR3(0.0f, 100.0f, -50.0f));

	//パーティクルの初期化
	InitParticle();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/ol_logo.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/title001.png",
		&g_pTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/GAME_START.png",
		&g_pTextureTitle[2]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/TUTORIAL.png",
		&g_pTextureTitle[3]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/tutorial000.png",
		&g_pTextureTitle[4]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/tutorial001.png",
		&g_pTextureTitle[5]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/tutorial_true.png",
		&g_pTextureTitle[6]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 , 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 4, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点座標の更新
	pVtx[4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 250.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 250.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 25, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 25, 0.0f);

	//頂点カラーの設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点座標の更新
	pVtx[8].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 200.0f, 0.0f);

	//頂点カラーの設定
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点座標の更新
	pVtx[12].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 100.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 100.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

	//頂点カラーの設定
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点座標の更新
	pVtx[16].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//頂点カラーの設定
	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//頂点座標の更新
	pVtx[20].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[21].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[22].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[23].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//チュートリアルを表示する処理
	pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//頂点座標の更新
	pVtx[24].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[25].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[26].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[27].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//チュートリアルを表示する処理
	pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);


for (int nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//タイトルのモデルの初期化
	InitTitleModel();

	//プレイヤーの初期化
	InitPlayer();

	//モデルのファイルの読み込み
	TitleFile();

	//ライトの初期化
	InitLight();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}
//=============================================
//タイトルの終了処理
//=============================================
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	//カメラの終了処理
	UninitCamera();

	int nCntTitle;

	//プレイヤーの破棄
	UninitPlayer();

	//パーティクルの破棄
	UninitParticle();

	//タイトルのモデルの終了処理
	UninitTitleModel();

	//ライトの終了処理
	UninitLight();

	//テクスチャの破棄
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffTitle != NULL)
		{
			g_pVtxBuffTitle->Release();
			g_pVtxBuffTitle = NULL;
		}
	}
}
//=============================================
//タイトルの更新処理
//=============================================
void UpdateTitle(void)
{
	//カメラの更新処理
	UpdateCamera();

	//プレイヤーの更新処理
	UpdatePlayer();

	//パーティクルの更新処理
	UpdateParticle();

	//タイトルのモデルの更新処理
	UpdateTitleModel();

	//ライトの更新処理
	UpdateLight();

	FADE pFade = GetFade();

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトルの選択の処理
	switch (TitleSelect)
	{
		case GAME:
		{
			//ゲームを開始する処理
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_X, 0) || GetJoypadTrigger(JOYKEY_B, 0))
			{
				if (pFade == FADE_NONE)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_BELL);

					SetFade(MODE_GAME);
				}
			}
			//タイトルの選択をずらす処理
			if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_S)
				|| GetJoypadTrigger(JOYKEY_UP, 0) || GetJoypadTrigger(JOYKEY_DOWN, 0))
			{
				PlaySound(SOUND_LABEL_SELECT);
				TitleSelect = TUTORIAL;
			}
			break;
		}
		case TUTORIAL:
		{
			//タイトルの選択をずらす処理
			if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_S) 
				|| GetJoypadTrigger(JOYKEY_UP, 0) || GetJoypadTrigger(JOYKEY_DOWN, 0) && tutorial == false)
			{
				PlaySound(SOUND_LABEL_SELECT);
				TitleSelect = GAME;
			}
			else if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_B,0 ))
			{
				//チュートリアルが使用されている状態にする
				tutorial = true;
				PlaySound(SOUND_LABEL_PAGE);

				switch(TutorialCnt)
				{
					case 0:
					{
						//チュートリアルを表示する処理
						pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						TutorialCnt++;
						break;
					}
					case 1:
					{
						//チュートリアルを表示する処理
						pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						TutorialCnt++;
						break;
					}
					case 2:
					{
						//チュートリアルを表示する処理
						pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						TutorialCnt++;
						break;
					}
					case 3:
					{
						//チュートリアルを表示する処理
						pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[24].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[25].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[26].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
						pVtx[27].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

						tutorial = false;
						TutorialCnt = 0;
						break;
					}
				}
			}
			break;
		}
	}
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	if (MoveStart == false)
	{
		g_move++;

		if (g_move == 30)
		{
			MoveStart = true;
		}
	}
	else
	{
		g_move--;

		if (g_move == 0)
		{
			MoveStart = false;
		}
	}

	switch (TitleSelect)
	{
	case GAME:
		//頂点座標の更新
		pVtx[8].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 - pos.y * g_move / 2, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 - pos.y * g_move / 2, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 200.0f - pos.y * g_move / 2, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 200.0f - pos.y * g_move / 2, 0.0f);
		break;

	case TUTORIAL:
		//頂点座標の更新
		pVtx[12].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 100.0f - pos.y * g_move / 2, 0.0f);
		pVtx[13].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2 + 100.0f - pos.y * g_move / 2, 0.0f);
		pVtx[14].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - 100.0f - pos.y * g_move / 2, 0.0f);
		pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT - 100.0f - pos.y * g_move / 2, 0.0f);
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}
//=============================================
//タイトルの描画処理
//=============================================
void DrawTitle(void)
{
	//カメラの設定処理
	SetCamera();

	//タイトルのモデルの描画
	DrawTitleModel();

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの描画
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//ポリゴンの描画 四角
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,				//プリミティブの種類
			nCntTitle * 4,						//描画する最初の頂点インデックス
			2);									//プリミティブ(ポリゴン)数
	}

	//パーティクルの描画
	DrawParticle();
}