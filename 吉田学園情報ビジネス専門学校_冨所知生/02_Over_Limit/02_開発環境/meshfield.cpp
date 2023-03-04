//=========================================
//
//	メッシュの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "meshfield.h"
#include "wall.h"
#include "model.h"
#include "wall.h"

//================================================================
//グローバル変数宣言
//================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;				//メッシュフィールドのテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;			//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffMeshField = NULL;			//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshField;									//位置
D3DXVECTOR3 g_rotMeshField;									//向き
D3DXMATRIX g_mtxWorldMesh;									//ワールドマトリックス

#define MESH_VERTEX_NUM ((MESH_X_BLOCK + 1) * (MESH_Z_BLOCK + 1))
#define MESH_INDEX_NUM  (((MESH_X_BLOCK + 1) * 2) * ( MESH_Z_BLOCK  *(MESH_Z_BLOCK - 1)) * MESH_Z_BLOCK * 2)
#define MESH_PRIMITIVE_NUM (MESH_X_BLOCK * MESH_Z_BLOCK * 2 + 4 * (MESH_Z_BLOCK  - 1))

int nLineVtx = (MESH_X_BLOCK + 1);
//================================================================
//メッシュの初期化
//================================================================
void InitMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX_NUM,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,													//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM,			//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,													//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/float.jpg",
		&g_pTextureMeshField);

	VERTEX_3D* pVtx = NULL;			//頂点情報の取得

	//頂点バッファをロック
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= MESH_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESH_X_BLOCK; nCntX++)
		{
			//頂点座標の設定（ワールド座標ではなくローカル座標を指定する）
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3(-(MESH_SIZE * MESH_X_BLOCK) / 2 + nCntX * MESH_SIZE, 0.0f,(MESH_SIZE * MESH_Z_BLOCK) / 2 - nCntZ * MESH_SIZE);

			//各頂点の法線の設定
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャの設定
			pVtx[nCntX + (MESH_X_BLOCK + 1) * nCntZ].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshField->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);
	
	//縦の頂点の数
	for (int nCntZ = 0; nCntZ < MESH_Z_BLOCK; nCntZ++)
	{
		//インデックス
		int nLineTop = nCntZ * (nLineVtx * 2 + 2);

		//横の頂点の数
		for (int nCntX = 0; nCntX < nLineVtx; nCntX++)
		{//上の段の処理
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + nLineVtx * nCntZ);

		//下の段の処理
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + nLineVtx);
		}

		//縮退ポリゴンを前後と同一にする処理
		if (nCntZ < MESH_Z_BLOCK)
		{
			pIdx[(nLineVtx * 2) + nLineTop] = (WORD)(MESH_X_BLOCK + (nLineVtx) * nCntZ);
			pIdx[(nLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (nLineVtx) + (nLineVtx) * nCntZ);
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshField->Unlock();
}
//================================================================
//メッシュの破棄
//================================================================
void UninitMesh(void)
{
	//メッシュフィールドのテクスチャ
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	//インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
	//頂点バッファの解放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
}
//================================================================
//メッシュの更新
//================================================================
void UpdateMesh(void)
{
}

//================================================================
//メッシュの描画
//================================================================
void DrawMesh(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMesh);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMesh, &g_mtxWorldMesh, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMesh, &g_mtxWorldMesh, &mtxTrans);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMesh);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファのデータストリームに設定
	pDevice -> SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// メッシュの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, MESH_VERTEX_NUM ,0, MESH_PRIMITIVE_NUM);
}