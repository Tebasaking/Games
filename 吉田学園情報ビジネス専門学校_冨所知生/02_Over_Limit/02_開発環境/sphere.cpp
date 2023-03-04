//=========================================
//
//	メッシュの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "sphere.h"
#include "wall.h"
#include "model.h"
#include "wall.h"

//================================================================
//グローバル変数宣言
//================================================================
LPDIRECT3DTEXTURE9 g_pTextureSphereField = NULL;				//メッシュフィールドのテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphereField = NULL;			//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffSphereField = NULL;			//インデックスバッファへのポインタ
D3DXVECTOR3 g_posSphereField;									//位置
D3DXVECTOR3 g_rotSphereField;									//向き
D3DXMATRIX g_mtxWorldSphere;									//ワールドマトリックス

#define SPHERE_VERTEX_NUM ((SPHERE_X_BLOCK + 1) * (SPHERE_Z_BLOCK + 1))
#define SPHERE_INDEX_NUM  (((SPHERE_X_BLOCK + 1) * 2) * ( SPHERE_Z_BLOCK  * (SPHERE_Z_BLOCK - 1)) * SPHERE_Z_BLOCK * 2)
#define SPHERE_PRIMITIVE_NUM (SPHERE_X_BLOCK * SPHERE_Z_BLOCK * 2 + (4 * (SPHERE_Z_BLOCK  - 1)))

int sLineVtx = (SPHERE_X_BLOCK + 1);
static float sRadius = 10.0f;
//================================================================
//メッシュの初期化
//================================================================
void InitSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_VERTEX_NUM,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,													//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphereField,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * SPHERE_INDEX_NUM,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,													//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphereField,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/aiueo.jpg",
		&g_pTextureSphereField);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffSphereField->Lock(0, 0, (void**)&pVtx, 0);

	//float fSphere = 0.0f;
	float RotZ = 0.0f;
	float Radius = 0.0f;
	//float Rot = ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK);

	for (int nCntZ = 0; nCntZ <= SPHERE_Z_BLOCK; nCntZ++)
	{
		RotZ = (D3DX_PI / SPHERE_Z_BLOCK) * nCntZ;
		Radius = sinf(RotZ) * 10.0f;

		for (int nCntX = 0; nCntX <= SPHERE_X_BLOCK; nCntX++)
		{
			//頂点座標の設定（ワールド座標ではなくローカル座標を指定する）
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
			(sinf(nCntX * ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK)) * Radius,				//x
			10.0f + cosf(RotZ) * 10.0f,													//y
			-cosf(nCntX  * ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK)) * Radius);				//z

			//各頂点の法線の設定
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor = pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].pos;

			//法線の正規化
			D3DXVec3Normalize(&pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor, &pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor);

			//頂点カラーの設定
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャの設定
			pVtx[(nCntX + (SPHERE_X_BLOCK + 1) * nCntZ)].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffSphereField->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffSphereField->Lock(0, 0, (void**)&pIdx, 0);

	//縦の頂点の数
	for (int nCntZ = 0; nCntZ < SPHERE_Z_BLOCK; nCntZ++)
	{
		//インデックス
		int nLineTop = nCntZ * (sLineVtx * 2 + 2);

		//横の頂点の数
		for (int nCntX = 0; nCntX < sLineVtx; nCntX++)
		{//上の段の処理
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + sLineVtx * nCntZ);

			//下の段の処理
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + sLineVtx);
		}

		//縮退ポリゴンを前後と同一にする処理
		if (nCntZ < SPHERE_Z_BLOCK)
		{
			pIdx[(sLineVtx * 2) + nLineTop] = (WORD)(SPHERE_X_BLOCK + (sLineVtx)* nCntZ);
			pIdx[(sLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (sLineVtx)+(sLineVtx)* nCntZ);
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffSphereField->Unlock();
}
//================================================================
//メッシュの破棄
//================================================================
void UninitSphere(void)
{
	//メッシュフィールドのテクスチャ
	if (g_pTextureSphereField != NULL)
	{
		g_pTextureSphereField->Release();
		g_pTextureSphereField = NULL;
	}
	//インデックスバッファの解放
	if (g_pIdxBuffSphereField != NULL)
	{
		g_pIdxBuffSphereField->Release();
		g_pIdxBuffSphereField = NULL;
	}
	//頂点バッファの解放
	if (g_pVtxBuffSphereField != NULL)
	{
		g_pVtxBuffSphereField->Release();
		g_pVtxBuffSphereField = NULL;
	}
}
//================================================================
//メッシュの更新
//================================================================
void UpdateSphere(void)
{
}

//================================================================
//メッシュの描画
//================================================================
void DrawSphere(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ライトを無効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldSphere);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotSphereField.y, g_rotSphereField.x, g_rotSphereField.z);

	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posSphereField.x, g_posSphereField.y, g_posSphereField.z);
	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxTrans);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSphereField);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSphere);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSphereField, 0, sizeof(VERTEX_3D));

	//インデックスバッファのデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffSphereField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// メッシュの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SPHERE_VERTEX_NUM, 0, SPHERE_PRIMITIVE_NUM);

	//ライトを有効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}