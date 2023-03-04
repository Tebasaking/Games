//========================================================
//パーティクルの処理
//========================================================
#include "particle.h"
#include "effect.h"
#include "main.h"

LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//頂点バッファへのポインタ
Particle g_aParticle[MAX_PARTICLE];

//========================================================
//パーティクルの初期化処理
//========================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntParticle;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureParticle);

	//弾の情報の初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;			//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius,-g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aParticle[nCntParticle].fRadius,-g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius,+g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aParticle[nCntParticle].fRadius,+g_aParticle[nCntParticle].fRadius, 0.0f);

			//頂点colorの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める

	}
	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//========================================================
//パーティクルの終了処理
//========================================================
void UninitParticle(void)
{
	if (g_pTextureParticle != NULL)
	{//テクスチャの破棄
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	if (g_pVtxBuffParticle != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}
//========================================================
//パーティクルの更新処理
//========================================================
void UpdateParticle(void)
{
	int nCntParticle;

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			SetEffect(g_aParticle[nCntParticle].pos , g_aParticle[nCntParticle].col , g_aParticle[nCntParticle].fRadius ,g_aParticle[nCntParticle].nLife);

			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;
			g_aParticle[nCntParticle].col.a -= 0.05f;
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}

			//頂点colorの設定
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//========================================================
//エフェクトの描画処理
//========================================================
void DrawParticle(void)
{
}

//========================================================
//パーティクルの設定処理
//========================================================
void SetParticle(D3DXVECTOR3 pos, int nType)
{
	int nCntParticle;

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//パーティクルが使用されていない

			g_aParticle[nCntParticle].nType = nType;

			switch (nType)
			{
			case 0:	
				g_aParticle[nCntParticle].pos = pos;
				g_aParticle[nCntParticle].move.x = cosf((float)(rand() % 600 - 314) / 100) * ((float)(rand() % 5) / 100 + 0.25f);
				g_aParticle[nCntParticle].move.y = (rand()% 1) / 10 + 0.1f;
				g_aParticle[nCntParticle].move.z = 0.0f;
				g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f);
				g_aParticle[nCntParticle].fRadius = (float)(rand() % 1 + 1);
				g_aParticle[nCntParticle].nLife = (rand() % 10) + 10;
				g_aParticle[nCntParticle].bUse = true;

				break;

			default:
				break;
			}
			break;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffParticle->Unlock();
}
//========================================================
//パーティクルの取得処理
//========================================================
Particle* GetParticle()
{
	return g_aParticle;
}