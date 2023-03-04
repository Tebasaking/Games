//========================================================
//
//	画面フェードの状態管理
//	Author : 冨所知生
//
//========================================================
#include "input.h"
#include "fade.h"

//========================================================
//グローバル変数
//========================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//頂点バッファのポイント
FADE					g_fade;						//現在のフェード
MODE					g_modeNext;					//次のフェード
D3DXCOLOR				g_colorFade;				//ポリゴン(フェード)の色

//========================================================
//フェードの初期化処理
//========================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;				//デバイスへのポインタ

											//デバイスの取得
	pDevice = GetDevice();

	g_fade = FADE_IN;						//フェードイン状態に

	g_modeNext = modeNext;					//次の画面(モード)を設定

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒いポリゴン(不透明)にしておく

														//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

								//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	//モードの設定
	SetMode(g_modeNext);
}

//====================================================
//フェードの終了処理
//====================================================
void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//====================================================
//フェードの更新処理
//====================================================
void UpdateFade(void)
{
	MODE pMode = GetMode();

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン情報
			g_colorFade.a -= 0.01f;		//ポリゴンの透明化

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		//何もしていない状態に
			}

			if (GetKeyboardTrigger(DIK_RETURN) && (pMode == MODE_TITLE || pMode == MODE_GAMEOVER))
			{
				g_colorFade.a -= 1.0f;
				g_fade = FADE_NONE;
			}
		}

		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.01f;		//ポリゴンの不透明化

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;		//フェードイン状態に

				//モードの設定(次の画面に移行)
				SetMode(g_modeNext);
			}
		}

		VERTEX_2D *pVtx;		//頂点情報へのポインタ

								//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//頂点バッファをアンロックする
		g_pVtxBuffFade->Unlock();
	}
}

//====================================================
//フェードの描画処理
//====================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,							//描画する最初の頂点インデックス
		2);
}

//====================================================
//フェードの設定処理
//====================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;										//フェードアウト状態に

	g_modeNext = modeNext;									//次の画面(モード)を設定

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//黒いポリゴン(透明)にしておく
}

//====================================================
//フェードの取得処理
//====================================================
FADE GetFade(void)
{
	return g_fade;
}