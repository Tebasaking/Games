//=============================================
//
//	オーダーの入出力処理
//	Auhor : 冨所知生
//
//=============================================
#include <stdio.h>
#include "main.h"
#include "title.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "order.h"
#include "ordertimer.h"

//グローバル関数
LPDIRECT3DTEXTURE9 g_pTextureOrder[NUM_ORDER] = { NULL, NULL , NULL };			//テクスチャ(3枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOrder = NULL;									//頂点バッファへのポインタ
ORDER g_aOrder[NUM_ORDER];
int g_OrderCount;																//次のオーダーが出るまでのカウント
int g_OrderCheck;																//原罪のオーダーの数
//=============================================
//タイトルの初期化処理
//=============================================
void InitOrder(void)
{
	//オーダーのカウントのリセット
	g_OrderCount = 3500;			//注文が出るまでの時間のリセット
	g_OrderCheck = 0;				//注文の個数のカウントのリセット

	for (int i = 0; i < NUM_ORDER; i++)
	{
		g_aOrder[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aOrder[i].nNumber = 0;
		g_aOrder[i].nType = ITEM_NULL;
		g_aOrder[i].bUse = false;
		g_aOrder[i].nLimit = 0;
		g_aOrder[i].nNumber = 0;
	}

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	//注文内容の画像の読み込みは完成品の数値を使っているので
	//[1]から始めている
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Order001.png",
		&g_pTextureOrder[1]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Order002.png",
		&g_pTextureOrder[2]);

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Order003.png",
		&g_pTextureOrder[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ORDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOrder,
		NULL);

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffOrder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{
		if (g_aOrder[nCnt].bUse == false)
		{
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aOrder[nCnt].nType = ITEM_NULL;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOrder->Unlock();
}
//=============================================
//タイトルの終了処理
//=============================================
void UninitOrder(void)
{
	int nCntOrder;

	//テクスチャの破棄
	for (nCntOrder = 0; nCntOrder < NUM_ORDER; nCntOrder++)
	{
		if (g_pTextureOrder[nCntOrder] != NULL)
		{
			g_pTextureOrder[nCntOrder]->Release();
			g_pTextureOrder[nCntOrder] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffOrder != NULL)
		{
			g_pVtxBuffOrder->Release();
			g_pVtxBuffOrder = NULL;
		}
	}
}
//=============================================
//タイトルの更新処理
//=============================================
void UpdateOrder(void)
{
	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{//オーダーの期限を制御する処理
		if (g_aOrder[nCnt].bUse)
		{
			g_aOrder[nCnt].nLimit--;			//オーダーの期限を減らす

			if (g_aOrder[nCnt].nLimit == 0)
			{//リミットが0になった時
				g_aOrder[nCnt].bUse = false;					//オーダーをfalseにする
				MoveOrder(g_aOrder[nCnt].nNumber);				//オーダーを移動させる
				SubOrderCount();								//オーダーの個数を一個減らす
			}
		}
	}
}
//=============================================
//タイトルの描画処理
//=============================================
void DrawOrder(void)
{
	int nCntOrder;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOrder, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの描画
	for (nCntOrder = 0; nCntOrder < NUM_ORDER; nCntOrder++)
	{
		if (g_aOrder[nCntOrder].bUse)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureOrder[g_aOrder[nCntOrder].nType]);

			//ポリゴンの描画 四角
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntOrder * 4,						//描画する最初の頂点インデックス
				2);									//プリミティブ(ポリゴン)数
		}
	}
}

//=========================================
//	注文の設置処理
//	* nTypeはcontain内のITEMTYPEの数字と共通 *
//=========================================
void SetOrder(D3DXVECTOR3 pos ,ITEMTYPE nType)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffOrder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{
		if (g_aOrder[nCnt].bUse == false)
		{
			//個数をインクリメントする
			g_OrderCheck++;
		
			g_aOrder[nCnt].pos = pos;
			g_aOrder[nCnt].bUse = true;
			g_aOrder[nCnt].nType = nType;
			g_aOrder[nCnt].nNumber = g_OrderCheck;
			g_aOrder[nCnt].nLimit = 3600;

			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + ORDER_SIZE, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + ORDER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + ORDER_SIZE, pos.y + ORDER_SIZE, 0.0f);

			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点colorの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//オーダータイマーの設置
			SetOTimer(pos, nCnt);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffOrder->Unlock();
}
//=========================================
//注文の情報の取得
//=========================================
ORDER *GetOrder()
{
	return g_aOrder;
}

//=========================================
//注文内容のランダム生成
//=========================================
void RandamOrder()
{
	g_OrderCount++;

	if (g_OrderCheck <= NUM_ORDER)
	{
		if (g_OrderCount >= 360)
		{
			//1から3までの乱数を生成
			SetOrder(D3DXVECTOR3(0.0f + (ORDER_SIZE * g_OrderCheck), 0.0f, 0.0f), (ITEMTYPE)(rand() % 3 + 1));
			g_OrderCount = 0;
		}
	}
}
//=========================================
//オーダーを横にずらす処理
//=========================================
void MoveOrder(int nNumber)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffOrder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_ORDER; nCnt++)
	{
		if (g_aOrder[nCnt].nNumber >= nNumber)
		{//取得したnNumberよりもオーダーの番号がそれ以上の時
			g_aOrder[nCnt].nNumber--;
		}

		if (g_aOrder[nCnt].bUse == true)
		{
			g_aOrder[nCnt].pos = D3DXVECTOR3((g_aOrder[nCnt].nNumber - 1) * ORDER_SIZE, 0.0f, 0.0f);

			pVtx[0].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x, g_aOrder[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x + ORDER_SIZE, g_aOrder[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x, g_aOrder[nCnt].pos.y + ORDER_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aOrder[nCnt].pos.x + ORDER_SIZE, g_aOrder[nCnt].pos.y + ORDER_SIZE, 0.0f);
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffOrder->Unlock();
}
//=========================================
//現在ある注文の個数をデクリメントする処理
//=========================================
void SubOrderCount()
{
	g_OrderCheck--;
}