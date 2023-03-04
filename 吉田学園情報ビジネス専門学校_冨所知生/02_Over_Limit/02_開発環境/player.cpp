//=========================================
//
//	プレイヤーの入出力処理
//	Author : 冨所知生
//
//=========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "polygon.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"
#include "wall.h"
#include "meshfield.h"
#include "particle.h"
#include "line.h"
#include "item.h"
#include "sound.h"

//グローバル変数宣言
PLAYER g_aPlayer[MAX_PLAYER];
static int s_nIdxShadow;							//影の判別
static int nCntNumKeySet = 0;						//現在再生中のKeySet番号
static int g_nCntFrame = 0;							//フレーム数
static int g_nDash;
MotionSet g_motionSet[MAX_ANIMATION];				//アニメーションの構造体
//=====================================================
//プレイヤーの初期化
//=====================================================
void InitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].bUse = false;													//使用していない
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//移動量の初期化
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//位置の初期設定
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//向きの初期設定
		g_aPlayer[nCntPlayer].rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//目的の向きの初期設定
		g_aPlayer[nCntPlayer].state = PLAYER_NORMAL;										//プレイヤーの状態の初期化
		g_aPlayer[nCntPlayer].Number = 0;

		for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
		{
			g_aPlayer[nCntPlayer].aModel[nCntParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPlayer[nCntPlayer].aModel[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent = 0;
			g_aPlayer[nCntPlayer].aModel[nCntParts].fFrame = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
	g_nDash = 0;
}

//=========================================
//プレイヤーの破棄
//=========================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//メッシュの破棄
		if (g_aPlayer[nCntPlayer].pMeshPlayer != NULL)
		{
			g_aPlayer[nCntPlayer].pMeshPlayer->Release();
			g_aPlayer[nCntPlayer].pMeshPlayer = NULL;
		}

		//マテリアルの破棄
		if (g_aPlayer[nCntPlayer].pBuffMatPlayer != NULL)
		{
			g_aPlayer[nCntPlayer].pBuffMatPlayer->Release();
			g_aPlayer[nCntPlayer].pBuffMatPlayer = NULL;
		}	

		for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
		{
			//メッシュの破棄
			if (g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh != NULL)
			{
				g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh->Release();
				g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat != NULL)
			{
				g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat->Release();
				g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat = NULL;
			}
		}
	}
}

//=========================================
//プレイヤーの更新処理
//=========================================
void UpdatePlayer(void)
{
	//カメラ情報の取得
	Camera *pCamera = GetCamera();

	if (g_aPlayer[0].bUse)
	{
		if (g_aPlayer[0].state != PLAYER_CUTTING)
		{
			//移動処理
			//Wキーを押したとき
			if (GetKeyboardPress(DIK_W) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < -0.5f)
			{
				//Aキーを押したとき
				if (GetKeyboardPress(DIK_A) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < 0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = D3DX_PI * 0.75f + pCamera->rot.y;
				}

				//Dキーを押したとき
				else if (GetKeyboardPress(DIK_D) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > -0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(-D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(-D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = -D3DX_PI * 0.75f + pCamera->rot.y;
				}

				//Wキーしか押してないとき
				else
				{
					g_aPlayer[0].pos.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = pCamera->rot.y - D3DX_PI;
				}
			}

			//Sキーを押したとき
			else if (GetKeyboardPress(DIK_S) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > 0.5f)
			{
				//Aキーを押したとき
				if (GetKeyboardPress(DIK_A) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = D3DX_PI * 0.25f + pCamera->rot.y;
				}

				//Dキーを押したとき
				else if (GetKeyboardPress(DIK_D) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > -0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(-D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(-D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = -D3DX_PI * 0.25f + pCamera->rot.y;
				}

				//Sキーしか押してないとき
				else
				{
					g_aPlayer[0].pos.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = pCamera->rot.y;
				}
			}
			//Aキーを押したとき
			else if (GetKeyboardPress(DIK_A) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < 0.5f)
			{
				g_aPlayer[0].pos.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y) * PLAYER_MOVE;
				g_aPlayer[0].pos.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y) * PLAYER_MOVE;
				g_aPlayer[0].rotDestPlayer.y = D3DX_PI * 0.5f + pCamera->rot.y;
			}
			//Dキーを押したとき
			else if (GetKeyboardPress(DIK_D) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > -0.5f)
			{
				g_aPlayer[0].pos.x -= sinf(-D3DX_PI * 0.5f + pCamera->rot.y) * PLAYER_MOVE;
				g_aPlayer[0].pos.z -= cosf(-D3DX_PI * 0.5f + pCamera->rot.y) * PLAYER_MOVE;
				g_aPlayer[0].rotDestPlayer.y = -D3DX_PI * 0.5f + pCamera->rot.y;
			}
			if (GetKeyboardTrigger(DIK_LSHIFT))
			{
				g_aPlayer[0].move.x -= sinf(g_aPlayer[0].rotDestPlayer.y) * 5.0f;
				g_aPlayer[0].move.z -= cosf(g_aPlayer[0].rotDestPlayer.y) * 5.0f;
			}
			
			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
			{
				//プレイヤーとモデルの当たり判定
				CollisionModel(&g_aPlayer[0].pos,
					&g_aPlayer[0].posOld,
					D3DXVECTOR3(g_aPlayer[0].aModel[nCntParts].vtxMax.x - g_aPlayer[0].aModel[nCntParts].vtxMin.x,
						0.0f,
						g_aPlayer[0].aModel[nCntParts].vtxMax.z - g_aPlayer[0].aModel[nCntParts].vtxMin.z));
			}
		}
		else
		{
			if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_D)
				|| GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_W)
				|| (GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > -0.5f)
				|| (GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < 0.5f)
				|| (GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > 0.5f)
				|| (GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < 0.5f))
			{
				StopSound(SOUND_LABEL_CUTTING);
				g_aPlayer[0].state = PLAYER_NORMAL;				//プレイヤーの状態を初期状態にする
			}
		}

		switch (g_aPlayer[0].state)
		{//アニメーションをプレイヤーの状態に応じてモーションを変える処理
			case PLAYER_NORMAL:
			{
				//ニュートラルモーション
				MotionPlayer(0);
				break;
			}
			case PLAYER_CUTTING:
			{
				//カットモーション
				MotionPlayer(1);
				break;
			}
		}

		//角度を正規化する処理
		//プレイヤーの向いている方向を調節する処理
		g_aPlayer[0].rot.y += NormalizRot(g_aPlayer[0].rotDestPlayer.y - g_aPlayer[0].rot.y) * 0.05f;

		//プレイヤーの向いている方向の正規化
		g_aPlayer[0].rot.y = NormalizRot(g_aPlayer[0].rot.y);

		//影の情報を取得
		Shadow* pShadow = GetShadow();

		//影とプレイヤーの距離
		g_aPlayer[0].ShadowSize = (g_aPlayer[0].pos.y + pShadow->pos.y) / 10;

		for (int i = 0; i < MAX_PLAYER; i++)
		{
			//影がついてくる処理
			SetPositionShadow(g_aPlayer[i].Shadow, g_aPlayer[i].pos, g_aPlayer[i].ShadowSize);
		}

		//前回の位置を保存
		g_aPlayer[0].posOld = g_aPlayer[0].pos;

		//位置を更新
		g_aPlayer[0].pos.x += g_aPlayer[0].move.x;
		g_aPlayer[0].pos.z += g_aPlayer[0].move.z;

		g_aPlayer[0].move.x += (0.0f - g_aPlayer[0].move.x) * 0.25f;
		g_aPlayer[0].move.z += (0.0f - g_aPlayer[0].move.z) * 0.25f;
	}
}

//=========================================
//プレイヤーの描画処理
//=========================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].mtxWorldPlayer);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aPlayer[nCntPlayer].rot.y, g_aPlayer[nCntPlayer].rot.x, g_aPlayer[nCntPlayer].rot.z);

			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorldPlayer, &g_aPlayer[nCntPlayer].mtxWorldPlayer, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorldPlayer, &g_aPlayer[nCntPlayer].mtxWorldPlayer, &mtxTrans);

			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aPlayer[nCntPlayer].aModel[nCntParts].rot.y, g_aPlayer[nCntPlayer].aModel[nCntParts].rot.x, g_aPlayer[nCntPlayer].aModel[nCntParts].rot.z);

				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].aModel[nCntParts].pos.x, g_aPlayer[nCntPlayer].aModel[nCntParts].pos.y, g_aPlayer[nCntPlayer].aModel[nCntParts].pos.z);
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &mtxTrans);

				D3DXMATRIX mtxParent;

				//親のワールドマトリクスの設定
				if (nCntParts == g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent)
				{
					mtxParent = g_aPlayer[nCntPlayer].mtxWorldPlayer;
				}
				else
				{
					//自分の親のマトリクスを代入
					mtxParent = g_aPlayer[nCntPlayer].aModel[g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent].mtxWorld;
				}

				//ローカル座標をワールド座標に適応させる
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld,&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld,&mtxParent);
				
				//ワールドマトリックスを更新
				pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld);

				//現在のマテリアルを保持(退避)
				pDevice->GetMaterial(&matDef);

				//マテリアルデータのポインタを取得する
				pMat = (D3DXMATERIAL*)g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aPlayer[nCntPlayer].aModel[nCntParts].nNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//プレイヤーパーツの描画
					g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh->DrawSubset(nCntMat);
				}

				//保持していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=========================================
//プレイヤーの情報の取得
//=========================================
PLAYER* GetPlayer()
{
	return g_aPlayer;
}

//=========================================
//プレイヤーの設置
//=========================================
void SetPlayer(D3DXVECTOR3 pos)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == false)
		{
			g_aPlayer[nCntPlayer].pos = pos;
			g_aPlayer[nCntPlayer].bUse = true;
			g_aPlayer[nCntPlayer].Shadow = SetShadow(g_aPlayer[nCntPlayer].pos, g_aPlayer[nCntPlayer].rot);		//影の設置処理
		}
	}
}

//=========================================
//モデルのパーツの設置
//=========================================
void SetParts(D3DXVECTOR3 pos, char PLAYER_NAME[128], int nCount)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].aModel[nCount].pos = pos;
		g_aPlayer[nCntPlayer].aModel[1].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

		g_aPlayer[nCntPlayer].aModel[nCount].posOrigin = g_aPlayer[nCntPlayer].aModel[nCount].pos;
		g_aPlayer[nCntPlayer].aModel[nCount].rotOrigin = g_aPlayer[nCntPlayer].aModel[nCount].rot;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(PLAYER_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aPlayer[nCntPlayer].aModel[nCount].pBuffMat,
			NULL,
			&g_aPlayer[nCntPlayer].aModel[nCount].nNumMat,
			&g_aPlayer[nCntPlayer].aModel[nCount].pMesh);

		int nNumVtx;			//頂点数
		DWORD sizeFVF;			//頂点フォーマットのサイズ
		BYTE *pVtxBuff;			//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_aPlayer[nCntPlayer].aModel[nCount].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aPlayer[nCntPlayer].aModel[nCount].pMesh->GetFVF());

		//頂点バッファのロック
		g_aPlayer[nCntPlayer].aModel[nCount].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標を取得
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してプレイヤーの最小値/最大値を取得
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.x = VertexMAXChange(vtx.x, g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.x);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.y = VertexMAXChange(vtx.y, g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.y);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.z = VertexMAXChange(vtx.z, g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.z);

			g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.x = VertexMINChange(vtx.x, g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.x);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.y = VertexMINChange(vtx.y, g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.y);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.z = VertexMINChange(vtx.z, g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.z);

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
		//頂点バッファのアンロック
		g_aPlayer[nCntPlayer].aModel[nCount].pMesh->UnlockVertexBuffer();
	}
}
//=========================================
//アニメーションのロード処理
//=========================================
void LoadAnimation(int AnimNumber ,int KeyNumber ,int Number ,bool bLoop, int NUM_KEY, int FRAME, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	g_motionSet[AnimNumber].bLOOP = bLoop;
	g_motionSet[AnimNumber].nNUM_KEY = NUM_KEY;
	g_motionSet[AnimNumber].aKeySet[KeyNumber].nFRAME = (float)FRAME;
	g_motionSet[AnimNumber].aKeySet[KeyNumber].aKey[KeyNumber].pos = pos;
	g_motionSet[AnimNumber].aKeySet[KeyNumber].aKey[KeyNumber].rot = rot;

	g_aPlayer[0].Number = Number;
}

//=========================================
//モーションの更新処理
//=========================================
void MotionPlayer(int nCntMotionSet)
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		//アニメーションを読み込む主な処理
		if (g_nCntFrame == 0)
		{
			g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest = g_aPlayer[0].aModel[g_aPlayer[0].Number].posOrigin + g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].aKey[g_aPlayer[0].Number].pos - g_aPlayer[0].aModel[g_aPlayer[0].Number].pos;
			g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest = g_aPlayer[0].aModel[g_aPlayer[0].Number].rotOrigin + g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].aKey[g_aPlayer[0].Number].rot - g_aPlayer[0].aModel[g_aPlayer[0].Number].rot;
		}

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.x = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.x);
		
		g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.y = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.y);

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.z = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.z);

		//変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3(g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest.x / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest.y / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest.z / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME);
		
		//変数宣言
		D3DXVECTOR3 addRot = D3DXVECTOR3(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.x / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.y / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.z / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME);

		//位置の加算
		g_aPlayer[0].aModel[g_aPlayer[0].Number].pos += addPos;

		//向きの加算
		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot += addRot;

		//移動方向の正規化
		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.x = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.x);

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.y = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.y);

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.z = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.z);

		//フレームカウントの加算
		g_nCntFrame++;

		if (g_nCntFrame >= g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME)
		{//フレームカウントが指定のフレーム数を超えた場合
			//フレーム数の初期化
			g_nCntFrame = 0;

			//再生中のキー番号数の加算
			nCntNumKeySet++;

			if (nCntNumKeySet >= g_motionSet[nCntMotionSet].nNUM_KEY && g_motionSet[nCntMotionSet].bLOOP == true)
			{//再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している。
				//再生中のキー数カウントを初期化
				nCntNumKeySet = 0;
			}
		}
	}
}

//=========================================
// モーションの構造体の取得
//=========================================
MotionSet *GetMotionSet()
{
	return g_motionSet;
}