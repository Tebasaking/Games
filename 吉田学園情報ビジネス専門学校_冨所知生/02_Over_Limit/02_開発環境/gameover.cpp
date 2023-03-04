//========================================================
//ゲームオーバー画面の処理
//========================================================
#include "main.h"
#include "GameOver.h"
#include "input.h"
#include "fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGameOver = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameOver = NULL;
//========================================================
//ゲームオーバーの初期化処理
//========================================================
void InitGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();
	//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"Data\\TEXTURE\\gameover001.jpg",
		&g_pTextureGameOver);

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameOver,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameOver->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標の指定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffGameOver->Unlock();

}

//========================================================
//ゲームオーバーの終了処理
//========================================================
void UninitGameOver(void)
{
	//テクスチャの破棄
	if (g_pTextureGameOver != NULL)
	{
		g_pTextureGameOver->Release();
		g_pTextureGameOver = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGameOver != NULL)
	{
		g_pVtxBuffGameOver->Release();
		g_pVtxBuffGameOver = NULL;
	}
}

//========================================================
//ゲームオーバーの更新処理
//========================================================
void UpdateGameOver(void)
{
	FADE pFade = GetFade();

	//決定(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN)|| GetJoypadTrigger(JOYKEY_X, 0) || GetJoypadTrigger(JOYKEY_B, 0))
	{
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}
}

//========================================================
//ゲームオーバーの描画処理
//========================================================
void DrawGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポイント

										//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameOver, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGameOver);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,									//描画する最初の頂点インデックス
		2);									//プリミティブ(ポリゴン)数
}