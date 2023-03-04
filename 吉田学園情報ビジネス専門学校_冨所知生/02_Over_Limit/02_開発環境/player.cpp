//=========================================
//
//	�v���C���[�̓��o�͏���
//	Author : �y���m��
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

//�O���[�o���ϐ��錾
PLAYER g_aPlayer[MAX_PLAYER];
static int s_nIdxShadow;							//�e�̔���
static int nCntNumKeySet = 0;						//���ݍĐ�����KeySet�ԍ�
static int g_nCntFrame = 0;							//�t���[����
static int g_nDash;
MotionSet g_motionSet[MAX_ANIMATION];				//�A�j���[�V�����̍\����
//=====================================================
//�v���C���[�̏�����
//=====================================================
void InitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].bUse = false;													//�g�p���Ă��Ȃ�
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�ړ��ʂ̏�����
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�ʒu�̏����ݒ�
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�����̏����ݒ�
		g_aPlayer[nCntPlayer].rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړI�̌����̏����ݒ�
		g_aPlayer[nCntPlayer].state = PLAYER_NORMAL;										//�v���C���[�̏�Ԃ̏�����
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
//�v���C���[�̔j��
//=========================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//���b�V���̔j��
		if (g_aPlayer[nCntPlayer].pMeshPlayer != NULL)
		{
			g_aPlayer[nCntPlayer].pMeshPlayer->Release();
			g_aPlayer[nCntPlayer].pMeshPlayer = NULL;
		}

		//�}�e���A���̔j��
		if (g_aPlayer[nCntPlayer].pBuffMatPlayer != NULL)
		{
			g_aPlayer[nCntPlayer].pBuffMatPlayer->Release();
			g_aPlayer[nCntPlayer].pBuffMatPlayer = NULL;
		}	

		for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
		{
			//���b�V���̔j��
			if (g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh != NULL)
			{
				g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh->Release();
				g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat != NULL)
			{
				g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat->Release();
				g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat = NULL;
			}
		}
	}
}

//=========================================
//�v���C���[�̍X�V����
//=========================================
void UpdatePlayer(void)
{
	//�J�������̎擾
	Camera *pCamera = GetCamera();

	if (g_aPlayer[0].bUse)
	{
		if (g_aPlayer[0].state != PLAYER_CUTTING)
		{
			//�ړ�����
			//W�L�[���������Ƃ�
			if (GetKeyboardPress(DIK_W) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).y < -0.5f)
			{
				//A�L�[���������Ƃ�
				if (GetKeyboardPress(DIK_A) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < 0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = D3DX_PI * 0.75f + pCamera->rot.y;
				}

				//D�L�[���������Ƃ�
				else if (GetKeyboardPress(DIK_D) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > -0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(-D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(-D3DX_PI * 0.75f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = -D3DX_PI * 0.75f + pCamera->rot.y;
				}

				//W�L�[���������ĂȂ��Ƃ�
				else
				{
					g_aPlayer[0].pos.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = pCamera->rot.y - D3DX_PI;
				}
			}

			//S�L�[���������Ƃ�
			else if (GetKeyboardPress(DIK_S) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).y > 0.5f)
			{
				//A�L�[���������Ƃ�
				if (GetKeyboardPress(DIK_A) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = D3DX_PI * 0.25f + pCamera->rot.y;
				}

				//D�L�[���������Ƃ�
				else if (GetKeyboardPress(DIK_D) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > 0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x > -0.5f)
				{
					g_aPlayer[0].pos.x -= sinf(-D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(-D3DX_PI * 0.25f + pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = -D3DX_PI * 0.25f + pCamera->rot.y;
				}

				//S�L�[���������ĂȂ��Ƃ�
				else
				{
					g_aPlayer[0].pos.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].pos.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;
					g_aPlayer[0].rotDestPlayer.y = pCamera->rot.y;
				}
			}
			//A�L�[���������Ƃ�
			else if (GetKeyboardPress(DIK_A) || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < -0.5f && GetJoypadStick(JOYKEY_LEFT_STICK, 0).x < 0.5f)
			{
				g_aPlayer[0].pos.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y) * PLAYER_MOVE;
				g_aPlayer[0].pos.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y) * PLAYER_MOVE;
				g_aPlayer[0].rotDestPlayer.y = D3DX_PI * 0.5f + pCamera->rot.y;
			}
			//D�L�[���������Ƃ�
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
				//�v���C���[�ƃ��f���̓����蔻��
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
				g_aPlayer[0].state = PLAYER_NORMAL;				//�v���C���[�̏�Ԃ�������Ԃɂ���
			}
		}

		switch (g_aPlayer[0].state)
		{//�A�j���[�V�������v���C���[�̏�Ԃɉ����ă��[�V������ς��鏈��
			case PLAYER_NORMAL:
			{
				//�j���[�g�������[�V����
				MotionPlayer(0);
				break;
			}
			case PLAYER_CUTTING:
			{
				//�J�b�g���[�V����
				MotionPlayer(1);
				break;
			}
		}

		//�p�x�𐳋K�����鏈��
		//�v���C���[�̌����Ă�������𒲐߂��鏈��
		g_aPlayer[0].rot.y += NormalizRot(g_aPlayer[0].rotDestPlayer.y - g_aPlayer[0].rot.y) * 0.05f;

		//�v���C���[�̌����Ă�������̐��K��
		g_aPlayer[0].rot.y = NormalizRot(g_aPlayer[0].rot.y);

		//�e�̏����擾
		Shadow* pShadow = GetShadow();

		//�e�ƃv���C���[�̋���
		g_aPlayer[0].ShadowSize = (g_aPlayer[0].pos.y + pShadow->pos.y) / 10;

		for (int i = 0; i < MAX_PLAYER; i++)
		{
			//�e�����Ă��鏈��
			SetPositionShadow(g_aPlayer[i].Shadow, g_aPlayer[i].pos, g_aPlayer[i].ShadowSize);
		}

		//�O��̈ʒu��ۑ�
		g_aPlayer[0].posOld = g_aPlayer[0].pos;

		//�ʒu���X�V
		g_aPlayer[0].pos.x += g_aPlayer[0].move.x;
		g_aPlayer[0].pos.z += g_aPlayer[0].move.z;

		g_aPlayer[0].move.x += (0.0f - g_aPlayer[0].move.x) * 0.25f;
		g_aPlayer[0].move.z += (0.0f - g_aPlayer[0].move.z) * 0.25f;
	}
}

//=========================================
//�v���C���[�̕`�揈��
//=========================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].mtxWorldPlayer);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aPlayer[nCntPlayer].rot.y, g_aPlayer[nCntPlayer].rot.x, g_aPlayer[nCntPlayer].rot.z);

			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorldPlayer, &g_aPlayer[nCntPlayer].mtxWorldPlayer, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorldPlayer, &g_aPlayer[nCntPlayer].mtxWorldPlayer, &mtxTrans);

			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aPlayer[nCntPlayer].aModel[nCntParts].rot.y, g_aPlayer[nCntPlayer].aModel[nCntParts].rot.x, g_aPlayer[nCntPlayer].aModel[nCntParts].rot.z);

				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].aModel[nCntParts].pos.x, g_aPlayer[nCntPlayer].aModel[nCntParts].pos.y, g_aPlayer[nCntPlayer].aModel[nCntParts].pos.z);
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld, &mtxTrans);

				D3DXMATRIX mtxParent;

				//�e�̃��[���h�}�g���N�X�̐ݒ�
				if (nCntParts == g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent)
				{
					mtxParent = g_aPlayer[nCntPlayer].mtxWorldPlayer;
				}
				else
				{
					//�����̐e�̃}�g���N�X����
					mtxParent = g_aPlayer[nCntPlayer].aModel[g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent].mtxWorld;
				}

				//���[�J�����W�����[���h���W�ɓK��������
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld,&g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld,&mtxParent);
				
				//���[���h�}�g���b�N�X���X�V
				pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].aModel[nCntParts].mtxWorld);

				//���݂̃}�e���A����ێ�(�ޔ�)
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�̃|�C���^���擾����
				pMat = (D3DXMATERIAL*)g_aPlayer[nCntPlayer].aModel[nCntParts].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aPlayer[nCntPlayer].aModel[nCntParts].nNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�v���C���[�p�[�c�̕`��
					g_aPlayer[nCntPlayer].aModel[nCntParts].pMesh->DrawSubset(nCntMat);
				}

				//�ێ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=========================================
//�v���C���[�̏��̎擾
//=========================================
PLAYER* GetPlayer()
{
	return g_aPlayer;
}

//=========================================
//�v���C���[�̐ݒu
//=========================================
void SetPlayer(D3DXVECTOR3 pos)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == false)
		{
			g_aPlayer[nCntPlayer].pos = pos;
			g_aPlayer[nCntPlayer].bUse = true;
			g_aPlayer[nCntPlayer].Shadow = SetShadow(g_aPlayer[nCntPlayer].pos, g_aPlayer[nCntPlayer].rot);		//�e�̐ݒu����
		}
	}
}

//=========================================
//���f���̃p�[�c�̐ݒu
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

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(PLAYER_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aPlayer[nCntPlayer].aModel[nCount].pBuffMat,
			NULL,
			&g_aPlayer[nCntPlayer].aModel[nCount].nNumMat,
			&g_aPlayer[nCntPlayer].aModel[nCount].pMesh);

		int nNumVtx;			//���_��
		DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aPlayer[nCntPlayer].aModel[nCount].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aPlayer[nCntPlayer].aModel[nCount].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aPlayer[nCntPlayer].aModel[nCount].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W���擾
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ăv���C���[�̍ŏ��l/�ő�l���擾
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.x = VertexMAXChange(vtx.x, g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.x);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.y = VertexMAXChange(vtx.y, g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.y);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.z = VertexMAXChange(vtx.z, g_aPlayer[nCntPlayer].aModel[nCount].vtxMax.z);

			g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.x = VertexMINChange(vtx.x, g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.x);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.y = VertexMINChange(vtx.y, g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.y);
			g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.z = VertexMINChange(vtx.z, g_aPlayer[nCntPlayer].aModel[nCount].vtxMin.z);

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}
		//���_�o�b�t�@�̃A�����b�N
		g_aPlayer[nCntPlayer].aModel[nCount].pMesh->UnlockVertexBuffer();
	}
}
//=========================================
//�A�j���[�V�����̃��[�h����
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
//���[�V�����̍X�V����
//=========================================
void MotionPlayer(int nCntMotionSet)
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		//�A�j���[�V������ǂݍ��ގ�ȏ���
		if (g_nCntFrame == 0)
		{
			g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest = g_aPlayer[0].aModel[g_aPlayer[0].Number].posOrigin + g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].aKey[g_aPlayer[0].Number].pos - g_aPlayer[0].aModel[g_aPlayer[0].Number].pos;
			g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest = g_aPlayer[0].aModel[g_aPlayer[0].Number].rotOrigin + g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].aKey[g_aPlayer[0].Number].rot - g_aPlayer[0].aModel[g_aPlayer[0].Number].rot;
		}

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.x = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.x);
		
		g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.y = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.y);

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.z = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.z);

		//�ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest.x / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest.y / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].posDest.z / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME);
		
		//�ϐ��錾
		D3DXVECTOR3 addRot = D3DXVECTOR3(g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.x / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.y / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME,
			g_aPlayer[0].aModel[g_aPlayer[0].Number].rotDest.z / g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME);

		//�ʒu�̉��Z
		g_aPlayer[0].aModel[g_aPlayer[0].Number].pos += addPos;

		//�����̉��Z
		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot += addRot;

		//�ړ������̐��K��
		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.x = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.x);

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.y = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.y);

		g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.z = NormalizRot(g_aPlayer[0].aModel[g_aPlayer[0].Number].rot.z);

		//�t���[���J�E���g�̉��Z
		g_nCntFrame++;

		if (g_nCntFrame >= g_motionSet[nCntMotionSet].aKeySet[nCntNumKeySet].nFRAME)
		{//�t���[���J�E���g���w��̃t���[�����𒴂����ꍇ
			//�t���[�����̏�����
			g_nCntFrame = 0;

			//�Đ����̃L�[�ԍ����̉��Z
			nCntNumKeySet++;

			if (nCntNumKeySet >= g_motionSet[nCntMotionSet].nNUM_KEY && g_motionSet[nCntMotionSet].bLOOP == true)
			{//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���B
				//�Đ����̃L�[���J�E���g��������
				nCntNumKeySet = 0;
			}
		}
	}
}

//=========================================
// ���[�V�����̍\���̂̎擾
//=========================================
MotionSet *GetMotionSet()
{
	return g_motionSet;
}