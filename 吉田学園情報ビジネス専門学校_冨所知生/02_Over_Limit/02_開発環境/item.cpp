//=========================================
//
//	アイテムの入出力処理
//	Author : 冨所知生
//
//=========================================
#include <stdio.h>
#include "main.h"
#include "item.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "player.h"
#include "meshfield.h"
#include "particle.h"
#include "line.h"
#include "model.h"
#include "objectline.h"
#include "Kitchen.h"
#include "contain.h"
#include "kitchentimer.h"
#include "cuttingtimer.h"
#include "sound.h"

//グローバル変数宣言
ITEM g_aItem[MAX_ITEM];
static int s_nIdxShadow;							//影の判別
static int SelectItem;								//何番目のアイテムを持っているか

//一番近くのアイテムを判定するのに必要な数値一式
static float s_mathWidth;
static float s_mathHeight;
static int s_mathMIN;
static int s_mathBox;
//=====================================================
//アイテムの初期化
//=====================================================
void InitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// アイテムの情報の初期化
		memset(&g_aItem[nCntItem], 0, sizeof(g_aItem[nCntItem]));

		g_aItem[nCntItem].vtxMaxItem = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aItem[nCntItem].vtxMaxItem = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		g_aItem[nCntItem].state = ITEM_NORMAL;										//アイテムの状態の初期化
	}
	SelectItem = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
}

//=========================================
//アイテムの破棄
//=========================================
void UninitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//メッシュの破棄
		if (g_aItem[nCntItem].pMeshItem != NULL)
		{
			g_aItem[nCntItem].pMeshItem->Release();
			g_aItem[nCntItem].pMeshItem = NULL;
		}

		//マテリアルの破棄
		if (g_aItem[nCntItem].pBuffMatItem != NULL)
		{
			g_aItem[nCntItem].pBuffMatItem->Release();
			g_aItem[nCntItem].pBuffMatItem = NULL;
		}
	}
}

//=========================================
//アイテムの更新処理
//=========================================
void UpdateItem(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	KITCHEN *pKitchen = GetKitchen();
	CONTAIN *pContain = GetContain();

	//モデルとの距離
	int ModelDistance = GetObjectDistance();
	int KitchenDistance = GetKitchenDistance();
	int ContainDistance = GetContainDistance();

	//一番近くにあるキッチン/モデル/容器を判定する
	int SelectKitchen = GetSelectKitchen();
	int SelectContain = GetSelectContain();
	int SelectModel = GetSelectObject();

	//ポインターを取得した数分進める
	pKitchen += SelectKitchen;				//キッチンのポインター
	pModel += SelectModel;					//モデルのポインター
	pContain += SelectContain;				//容器のポインター

	//プレイヤーとアイテムとの距離を測り、ラインを設置する処理
	PlayerDistanceItem();

	if (ModelDistance <= 10)
	{//モデルとの距離が近いとき
		//プレイヤーがアイテムを取得する処理
		if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) && pPlayer->state == PLAYER_NORMAL && pModel->bIsLanding == false)
		{//スペースを押したときかつ、プレイヤーの状態が何も持っていないとき
			//かつ、モデルのタイプが調理台(1)かカウンター(3)ではないとき
			//モデルがプレイヤーの近くにある時
			if (pModel->Type == 0)
			{
				PlaySound(SOUND_LABEL_OPEN);
				SetItem(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z), "data/MODEL/Object/Material/Material_1.x", ITEM_HAVE, ITEM_MEAT, false);
				pPlayer->state = PLAYER_HAVE;		//プレイヤーが物体を所持している状態にする
			}
			else if (pModel->Type == 4)
			{
				PlaySound(SOUND_LABEL_OPEN);
				SetItem(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z), "data/MODEL/Object/Material/Material_2.x", ITEM_HAVE, ITEM_CABBAGE, false);
				pPlayer->state = PLAYER_HAVE;		//プレイヤーが物体を所持している状態にする
			}
		}
		else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) && pPlayer->state == PLAYER_NORMAL && g_aItem[SelectItem].state == ITEM_NORMAL && pModel->bIsLanding == true)
		{//ブロックの上からアイテムを回収する処理
			if (s_mathMIN <= 10)
			{
				if (g_aItem[SelectItem].bUse)
				{
					PlaySound(SOUND_LABEL_OPEN);
					pPlayer->state = PLAYER_HAVE;
					g_aItem[SelectItem].state = ITEM_HAVE;
					pModel->bIsLanding = false;
					g_aItem[SelectItem].bCook = false;
				}
			}
		}
		//アイテムを持っているときスペースを押したらアイテムをそこのブロックの上に置く処理
		else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0))&& g_aItem[SelectItem].state == ITEM_HAVE && pPlayer->state == PLAYER_HAVE)
		{
			if (s_mathMIN <= 10)
			{//一番近くにあるオブジェクトが調理器具だった場合
				if (pModel->bIsLanding)
				{//すでに物が設置されているとき
					if (KitchenDistance <= 10)
					{//アイテムを調理器具の中に入れる
						if ((pKitchen->cook == KITCHEN_NORMAL || pKitchen->cook == KITCHEN_NONE) && g_aItem[SelectItem].bCut)
						{//キッチンの状態が何も入ってない || 通常状態 || アイテムを切った状態
							//調理中の処理
							KitchenInput();
						}
						else
						{
							//何もしない
						}
					}
				}
				else if (ContainDistance <= 10)
				{//容器が最も近いものだった場合
				 //何もしない
				}
				else
				{//モデルの上に何も乗っていないとき
					if (pModel->bIsLanding == false)
					{
						if (ModelDistance <= 10)
						{//モデルとの距離が10以下の時
							pPlayer->state = PLAYER_NORMAL;				//プレイヤーを何も持っていない状態にする
							g_aItem[SelectItem].state = ITEM_NORMAL;	//アイテムを初期状態にする
							pModel->bIsLanding = true;					//モデルの上に物体があるかないか
							PlaySound(SOUND_LABEL_SELECT);

							//アイテムをモデルの上に設置する
							g_aItem[SelectItem].pos = (D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 11.0f, pModel->pos.z));
						}
					}
				}
			}
		}
		else if (pPlayer->state == PLAYER_CUTTING)
		{//プレイヤーを切っている状態にする
			Cutting();
		}
	}

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_aItem[nCnt].state == ITEM_HAVE)
		{//アイテムが持たれているとき
			if (pPlayer->state == PLAYER_HAVE)
			{
				g_aItem[nCnt].pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 5.0f, pPlayer->pos.z);
			}
		}
	}
}

//=========================================
//アイテムの描画処理
//=========================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ
	//プレイヤーの情報を取得
	PLAYER *pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			if(g_aItem[nCntItem].state == ITEM_NORMAL)
			{ 
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorldItem);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aItem[nCntItem].rot.y, g_aItem[nCntItem].rot.x, g_aItem[nCntItem].rot.z);

			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldItem, &g_aItem[nCntItem].mtxWorldItem, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldItem, &g_aItem[nCntItem].mtxWorldItem, &mtxTrans);
			}
			else if (g_aItem[nCntItem].state == ITEM_HAVE)
			{//アイテムが持たれているとき
				if (pPlayer->state == PLAYER_HAVE)
				{//向きの反映
					D3DXMATRIX Kichen_have;

					D3DXMatrixIdentity(&Kichen_have);

					D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DX_PI, 0.0f, 0.0f);

					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxRot);

					//位置を反映
					D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, -5.0f);
					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxTrans);

					D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldItem, &Kichen_have, &pPlayer->mtxWorldPlayer);
				}
			}
			//ワールドマトリックスを更新
			pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorldItem);

			//現在のマテリアルを保持(退避)
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタを取得する
			pMat = (D3DXMATERIAL*)g_aItem[nCntItem].pBuffMatItem->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aItem[nCntItem].nNumMatItem; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//アイテムパーツの描画
				g_aItem[nCntItem].pMeshItem->DrawSubset(nCntMat);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================
//アイテムの情報の取得
//=========================================
ITEM* GetItem()
{
	return g_aItem;
}

//=========================================
//アイテムの設置
//=========================================
void SetItem(D3DXVECTOR3 pos , char ITEM_NAME[128] ,ITEM_STATE state ,ITEMTYPE type ,bool cut)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].bUse = true;
			g_aItem[nCntItem].bCut = cut;
			g_aItem[nCntItem].Shadow = SetShadow(g_aItem[nCntItem].pos, g_aItem[nCntItem].rot);		//影の設置処理
			g_aItem[nCntItem].state = state;
			g_aItem[nCntItem].type = type;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//Xファイルの読み込み
			D3DXLoadMeshFromX(ITEM_NAME,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aItem[nCntItem].pBuffMatItem,
				NULL,
				&g_aItem[nCntItem].nNumMatItem,
				&g_aItem[nCntItem].pMeshItem);

			int nNumVtx;			//頂点数
			DWORD sizeFVF;			//頂点フォーマットのサイズ
			BYTE *pVtxBuff;			//頂点バッファへのポインタ

			//頂点数の取得
			nNumVtx = g_aItem[nCntItem].pMeshItem->GetNumVertices();
			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aItem[nCntItem].pMeshItem->GetFVF());

			//頂点バッファのロック
			g_aItem[nCntItem].pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

			for (int nCntItemVtx = 0; nCntItemVtx < nNumVtx; nCntItemVtx++)
			{
				//頂点座標を取得
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較してアイテムの最小値/最大値を取得
				g_aItem[nCntItem].vtxMaxItem.x = VertexMAXChange(vtx.x, g_aItem[nCntItem].vtxMaxItem.x);
				g_aItem[nCntItem].vtxMaxItem.y = VertexMAXChange(vtx.y, g_aItem[nCntItem].vtxMaxItem.y);
				g_aItem[nCntItem].vtxMaxItem.z = VertexMAXChange(vtx.z, g_aItem[nCntItem].vtxMaxItem.z);

				g_aItem[nCntItem].vtxMinItem.x = VertexMINChange(vtx.x, g_aItem[nCntItem].vtxMinItem.x);
				g_aItem[nCntItem].vtxMinItem.y = VertexMINChange(vtx.y, g_aItem[nCntItem].vtxMinItem.y);
				g_aItem[nCntItem].vtxMinItem.z = VertexMINChange(vtx.z, g_aItem[nCntItem].vtxMinItem.z);

				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}
			//頂点バッファのアンロック
			g_aItem[nCntItem].pMeshItem->UnlockVertexBuffer();

			break;
		}
	}
}

//=========================================
//アイテムの当たり判定の生成
//=========================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{//横のめり込み判定
		if (pPos->z - size.z / 2.0f > g_aItem[i].pos.z + g_aItem[i].vtxMaxItem.z
			&& pPos->z + size.z / 2.0f < g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z)
		{
			//左の当たり判定の設定
			if (pPosOld->x - size.z / 2.0f <= g_aItem[i].pos.x - g_aItem[i].vtxMinItem.x
				&& pPos->x - size.z / 2.0f > g_aItem[i].pos.x - g_aItem[i].vtxMinItem.x)
			{
				pPos->x = g_aItem[i].pos.x - g_aItem[i].vtxMinItem.x + size.z / 2.0f;
			}
			//右の当たり判定の設定
			if (pPosOld->x + size.z / 2.0f >= g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x
				&& pPos->x + size.z / 2.0f < g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x)
			{
				pPos->x = g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x - size.z / 2.0f;
			}
		}

		//上下の当たり判定
		if (pPos->x - size.z / 2.0f > g_aItem[i].pos.x + g_aItem[i].vtxMaxItem.x
			&& pPos->x + size.z / 2.0f < g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x)
		{
			//下の当たり判定の設定
			if (pPosOld->z - size.z / 2.0f <= g_aItem[i].pos.z - g_aItem[i].vtxMinItem.z
				&& pPos->z - size.z / 2.0f > g_aItem[i].pos.z - g_aItem[i].vtxMinItem.z)
			{
				pPos->z = g_aItem[i].pos.z - g_aItem[i].vtxMinItem.z + size.z / 2.0f - 0.1f;
			}
			//右の当たり判定の設定
			if (pPosOld->z + size.z / 2.0f >= g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z
				&& pPos->z + size.z / 2.0f < g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z)
			{
				pPos->z = g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z - size.z / 2.0f + 0.1f;
			}
		}
	}
}

//=========================================
//一番近くのアイテムを判定する
//=========================================
void PlayerDistanceItem()
{
	PLAYER *pPlayer = GetPlayer();
	s_mathMIN = 1000000;

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_aItem[nCnt].bUse == true)
		{
			s_mathWidth = pPlayer->pos.x - g_aItem[nCnt].pos.x;
			s_mathHeight = pPlayer->pos.z - g_aItem[nCnt].pos.z;

			s_mathBox = (int)sqrtf(s_mathWidth * s_mathWidth + s_mathHeight * s_mathHeight);

			if (s_mathBox <= s_mathMIN)
			{
				s_mathMIN = s_mathBox;
				SelectItem = nCnt;
			}
		}
	}

	if (s_mathMIN <= 10)
	{
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aItem[SelectItem].vtxMaxItem, D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMaxItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aItem[SelectItem].vtxMaxItem, D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMinItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMinItem.z), D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMinItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMinItem.z), D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMaxItem.z));

		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aItem[SelectItem].vtxMinItem, D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMinItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aItem[SelectItem].vtxMinItem, D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMaxItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMaxItem.z), D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMinItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMaxItem.z), D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMaxItem.z));

		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMinItem.z), D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMinItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMaxItem.z), D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMaxItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aItem[SelectItem].vtxMaxItem, D3DXVECTOR3(g_aItem[SelectItem].vtxMaxItem.x, g_aItem[SelectItem].vtxMinItem.y, g_aItem[SelectItem].vtxMaxItem.z));
		SetObjectLine(g_aItem[SelectItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aItem[SelectItem].vtxMinItem, D3DXVECTOR3(g_aItem[SelectItem].vtxMinItem.x, g_aItem[SelectItem].vtxMaxItem.y, g_aItem[SelectItem].vtxMinItem.z));
	}
}
//=========================================
//アイテムを調理道具に置いたときの処理
//=========================================
void KitchenInput(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	KITCHEN *pKitchen = GetKitchen();

	char ItemFile[255];

	//一番近くにあるキッチン/モデルを判定する
	int SelectKitchen = GetSelectKitchen();
	int SelectModel = GetSelectObject();

	pKitchen += SelectKitchen;					//キッチン
	pModel += SelectModel;						//モデル

	pPlayer->state = PLAYER_NORMAL;				//プレイヤーを何も持っていない状態にする
	g_aItem[SelectItem].state = ITEM_NORMAL;	//アイテムを初期状態にする
	pKitchen->cook = KITCHEN_MATERIAL;			//調理道具の中にものがある状態にする
	pKitchen->type = g_aItem[SelectItem].type;	//入れたアイテムの指定

	if (pKitchen->bTimer == false)
	{//キッチンタイマーが作動しているかしていないか
		pKitchen->bTimer = true;
		//キッチンタイマーを設置する
		SetKTimer(pKitchen->pos);
	}

	pModel->bIsLanding = true;					//モデルの上に物体があるかないか

	g_aItem[SelectItem].bUse = false;

	//ファイル名をtypeから入力させる
	sprintf(ItemFile, "data/MODEL/FOOD/food_%d_fresh.x", g_aItem[SelectItem].type);

	TSKitchen(D3DXVECTOR3(0.0f, 3.0f, 0.0f),ItemFile, SelectKitchen);	//調理中の道具を設置

	if (pModel->Type == 1)
	{//調理器具が乗っているブロックが調理台(1)だった場合
		PlaySound(SOUND_LABEL_HOT);
		pKitchen->cook = KITCHEN_COOK;						//調理中の状態にする。
	}
}
//=========================================
//　アイテムを調理する処理
//=========================================
void Cutting()
{
	//モデルの情報を取得する
	MODEL *pModel = GetModel();
	CTIMER *pCTimer = GetCTimer();
	PLAYER *pPlayer = GetPlayer();

	int SelectModel = GetSelectObject();

	pModel += SelectModel;						//モデル

	//アイテムのファイル名を収納する
	char ItemFile[255];
	
	if (g_aItem[SelectItem].bCut == false)
	{
		//調理の時間をインクリメントする
		g_aItem[SelectItem].CuttingTime++;

		if (g_aItem[SelectItem].bCook == false)
		{
			g_aItem[SelectItem].bCook = true;
			//カットタイマーの設置
			SetCTimer(g_aItem[SelectItem].pos);
		}
		if (g_aItem[SelectItem].CuttingTime > 180)
		{
			ItemFile[0] = {};
			g_aItem[SelectItem].CuttingTime = 0;			//調理の時間を初期化
			g_aItem[SelectItem].bUse = false;				//元々あったモデル

			//ファイル名をtypeから入力させる
			sprintf(ItemFile, "data/MODEL/FOOD/food_%d_fresh.x", g_aItem[SelectItem].type);
			//調理したアイテムを再設置する。
			SetItem(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z), ItemFile, ITEM_NORMAL, g_aItem[SelectItem].type, true);
			pCTimer->bUse = false;
			pPlayer->state = PLAYER_NORMAL;
			StopSound(SOUND_LABEL_CUTTING);
		}
	}
}
//=========================================
// 一番近いアイテムの番号の取得
//=========================================
int GetSelectItem()
{
	return SelectItem;
}