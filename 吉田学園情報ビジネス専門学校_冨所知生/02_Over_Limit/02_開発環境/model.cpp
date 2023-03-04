//=========================================
//
//	モデルの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "model.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "player.h"
#include "meshfield.h"
#include "particle.h"
#include "line.h"
#include "item.h"
#include "objectline.h"
#include "Kitchen.h"
#include "contain.h"
#include "sound.h"

//グローバル変数宣言
MODEL g_aModel[MAX_MODEL];
static int s_nIdxShadow;							//影の判別
static int s_nIdxModel;
static int s_ModelDistance;							//プレイヤーとモデルの距離
static float s_mathWidth;
static float s_mathHeight;
static float s_mathMIN = 1000000;
static int s_mathBox;
static int s_Submission;							//提出するとことの距離
static int s_nCount;
//=====================================================
//モデルの初期化
//=====================================================
void InitModel(void)
{	
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// モデルの情報の初期化
		memset(&g_aModel[nCntModel], 0, sizeof(g_aModel[nCntModel]));
	
		//目的の向きの初期設定
		g_aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	}
	s_nIdxModel = 0;
	s_nIdxShadow = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
	s_ModelDistance = 0;
}

//=========================================
//モデルの破棄
//=========================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (int i = 0; i < (int)g_aModel[nCntModel].nNumMatModel; i++)
		{
			if (g_aModel[nCntModel].pTexture[i] != NULL)
			{// テクスチャの解放
				g_aModel[nCntModel].pTexture[i]->Release();
				g_aModel[nCntModel].pTexture[i] = NULL;
			}
		}

		//メッシュの破棄
		if (g_aModel[nCntModel].pMeshModel != NULL)
		{
			g_aModel[nCntModel].pMeshModel->Release();
			g_aModel[nCntModel].pMeshModel = NULL;
		}
		//マテリアルの破棄
		if (g_aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_aModel[nCntModel].pBuffMatModel->Release();
			g_aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=========================================
//モデルの更新処理
//=========================================
void UpdateModel(void)
{
	//プレイヤーの情報を取得する
	PLAYER *pPlayer = GetPlayer();
	ITEM *pItem = GetItem();

	//一番近いアイテムにポインターをずらす
	pItem += GetSelectItem();

	//プレイヤーの近くのラインを光らせる処理
	PlayerDistanceModel();

	//***********
	//包丁の処理
	//***********
	if (g_aModel[s_ModelDistance].Type == 6 && GetKeyboardTrigger(DIK_LCONTROL) || GetJoypadTrigger(JOYKEY_A, 0) && g_aModel[s_ModelDistance].bIsLanding)
	{//モデルのタイプが6の時、左コントロールを押している時
		PlaySound(SOUND_LABEL_CUTTING);
		pPlayer->state = PLAYER_CUTTING;
	}
}

//=========================================
//モデルの描画処理
//=========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ

	for(int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{ 
		if (g_aModel[nCntModel].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorldModel);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorldModel, &g_aModel[nCntModel].mtxWorldModel, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorldModel, &g_aModel[nCntModel].mtxWorldModel, &mtxTrans);

			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorldModel);

			//現在のマテリアルを保持(退避)
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタを取得する
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_aModel[nCntModel].pTexture[nCntMat]);

				//モデルパーツの描画
				g_aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================
//モデルの情報の取得
//=========================================
MODEL* GetModel()
{
	return &g_aModel[0];
}

//=========================================
//モデルの設置
//=========================================
void SetModel(D3DXVECTOR3 pos, char MODEL_NAME[128], int nCnt ,int nType)
{
	if (g_aModel[nCnt].bUse == false)
	{
		g_aModel[nCnt].pos = pos;
		g_aModel[nCnt].bUse = true;
		g_aModel[nCnt].Shadow = SetShadow(g_aModel[nCnt].pos, g_aModel[nCnt].rot);		//影の設置処理
		g_aModel[nCnt].Type = nType;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCnt].pBuffMatModel,
			NULL,
			&g_aModel[nCnt].nNumMatModel,
			&g_aModel[nCnt].pMeshModel);

		// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_aModel[nCnt].pBuffMatModel->GetBufferPointer();

		// 各メッシュのマテリアル情報を取得する
		for (int i = 0; i < (int)g_aModel[nCnt].nNumMatModel; i++)
		{
			g_aModel[nCnt].pTexture[i] = NULL;

			if (pMat[i].pTextureFilename != NULL)
			{// マテリアルで設定されているテクスチャ読み込み
				D3DXCreateTextureFromFileA(pDevice,
					pMat[i].pTextureFilename,
					&g_aModel[nCnt].pTexture[i]);
			}
		}
		int nNumVtx;			//頂点数
		DWORD sizeFVF;			//頂点フォーマットのサイズ
		BYTE *pVtxBuff;			//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aModel[nCnt].pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCnt].pMeshModel->GetFVF());

		//頂点バッファのロック
		g_aModel[nCnt].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標を取得
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値/最大値を取得
			g_aModel[nCnt].vtxMaxModel.x = VertexMAXChange(vtx.x, g_aModel[nCnt].vtxMaxModel.x);
			g_aModel[nCnt].vtxMaxModel.y = VertexMAXChange(vtx.y, g_aModel[nCnt].vtxMaxModel.y);
			g_aModel[nCnt].vtxMaxModel.z = VertexMAXChange(vtx.z, g_aModel[nCnt].vtxMaxModel.z);

			g_aModel[nCnt].vtxMinModel.x = VertexMINChange(vtx.x, g_aModel[nCnt].vtxMinModel.x);
			g_aModel[nCnt].vtxMinModel.y = VertexMINChange(vtx.y, g_aModel[nCnt].vtxMinModel.y);
			g_aModel[nCnt].vtxMinModel.z = VertexMINChange(vtx.z, g_aModel[nCnt].vtxMinModel.z);

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
		//頂点バッファのアンロック
		g_aModel[nCnt].pMeshModel->UnlockVertexBuffer();

		if (g_aModel[nCnt].Type == 1)
		{//モデルのタイプが調理器具(1)だった場合
			SetKitchen(D3DXVECTOR3(g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y + KITCHEN_SIZE, g_aModel[nCnt].pos.z), KITCHEN_NORMAL);
			SetKitchenParts(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/frypan_test.x", 0);
			SetKitchenParts(D3DXVECTOR3(0.0f, 0.0f, -7.0f), "data/MODEL/frypan_hand.x", 1);
			SetKitchenParts(D3DXVECTOR3(0.0f, 5.0f, 0.0f), "data/MODEL/Object/Block/Null.x", 2);
			g_aModel[nCnt].cook = true;
			g_aModel[nCnt].bIsLanding = true;
		}
	}
}

//=========================================
//モデルの当たり判定の生成
//=========================================
void CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_MODEL; i++)
	{//横のめり込み判定
		if (pPos->z - size.z / 2.0f > g_aModel[i].pos.z + g_aModel[i].vtxMaxModel.z
			&& pPos->z + size.z / 2.0f < g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z)
		{
			//左の当たり判定の設定
			if (pPosOld->x - size.z / 2.0f <= g_aModel[i].pos.x - g_aModel[i].vtxMinModel.x
				&& pPos->x - size.z / 2.0f > g_aModel[i].pos.x - g_aModel[i].vtxMinModel.x)
			{
				pPos->x = g_aModel[i].pos.x - g_aModel[i].vtxMinModel.x + size.z / 2.0f;
			}
			//右の当たり判定の設定
			if (pPosOld->x + size.z / 2.0f >= g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x
				&& pPos->x + size.z / 2.0f < g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x)
			{
				pPos->x = g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x - size.z / 2.0f;
			}
		}

		//上下の当たり判定
		if (pPos->x - size.z / 2.0f > g_aModel[i].pos.x + g_aModel[i].vtxMaxModel.x
			&& pPos->x + size.z / 2.0f < g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x)
		{
			//下の当たり判定の設定
			if (pPosOld->z - size.z / 2.0f <= g_aModel[i].pos.z - g_aModel[i].vtxMinModel.z
				&& pPos->z - size.z / 2.0f > g_aModel[i].pos.z - g_aModel[i].vtxMinModel.z)
			{
				pPos->z = g_aModel[i].pos.z - g_aModel[i].vtxMinModel.z + size.z / 2.0f - 0.1f;
			} 

			//右の当たり判定の設定
			if (pPosOld->z + size.z / 2.0f >= g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z
				&& pPos->z + size.z / 2.0f < g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z)
			{
				pPos->z = g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z - size.z / 2.0f + 0.1f;
			}
		}	
	}
}

//=========================================
//頂点の最大値比較用
//=========================================
float VertexMAXChange(float vtx, float max)
{
	if (vtx < max)
	{
		max = vtx;
	}
	return max;
}

//=========================================
//頂点の最小値比較用
//=========================================
float VertexMINChange(float vtx, float min)
{
	if (vtx > min)
	{
		min = vtx;
	}
	return min;
}

//=========================================
//プレイヤーと最も近いオブジェクトを求める
//=========================================
void PlayerDistanceModel()
{
	PLAYER *pPlayer = GetPlayer();

	s_mathMIN = 1000000;
	s_Submission = 1000000;

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		s_mathWidth = pPlayer->pos.x - g_aModel[nCnt].pos.x;
		s_mathHeight = pPlayer->pos.z - g_aModel[nCnt].pos.z;

		s_mathBox = (int)sqrtf(s_mathWidth * s_mathWidth + s_mathHeight * s_mathHeight);

		if (s_mathBox <= s_mathMIN)
		{
			s_mathMIN = s_mathBox;
			s_ModelDistance = nCnt;

			if (g_aModel[nCnt].Type == 3)
			{//モデルのタイプがカウンター(3)だった時のモデルの距離
				s_Submission = s_mathBox;
			}
		}
	}

	if (s_mathMIN <= 10)
	{
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aModel[s_ModelDistance].vtxMaxModel, D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aModel[s_ModelDistance].vtxMaxModel, D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMinModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMinModel.z), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMinModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMinModel.z), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z));

		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aModel[s_ModelDistance].vtxMinModel, D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMinModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aModel[s_ModelDistance].vtxMinModel, D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMinModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z));

		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMinModel.z), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMinModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z), D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aModel[s_ModelDistance].vtxMaxModel, D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMaxModel.x, g_aModel[s_ModelDistance].vtxMinModel.y, g_aModel[s_ModelDistance].vtxMaxModel.z));
		SetObjectLine(g_aModel[s_ModelDistance].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aModel[s_ModelDistance].vtxMinModel, D3DXVECTOR3(g_aModel[s_ModelDistance].vtxMinModel.x, g_aModel[s_ModelDistance].vtxMaxModel.y, g_aModel[s_ModelDistance].vtxMinModel.z));
	}
}

//=========================================
//モデルの番号の取得
//=========================================
int GetSelectObject()
{
	return s_ModelDistance;
}

//=========================================
//モデルとの距離の取得
//=========================================
int GetObjectDistance()
{
	return s_mathMIN;
}