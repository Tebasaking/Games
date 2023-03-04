//=========================================
//
//	���f���̓��o�͏���
//	Author : �y���m��
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

//�O���[�o���ϐ��錾
MODEL g_aModel[MAX_MODEL];
static int s_nIdxShadow;							//�e�̔���
static int s_nIdxModel;
static int s_ModelDistance;							//�v���C���[�ƃ��f���̋���
static float s_mathWidth;
static float s_mathHeight;
static float s_mathMIN = 1000000;
static int s_mathBox;
static int s_Submission;							//��o����Ƃ��Ƃ̋���
static int s_nCount;
//=====================================================
//���f���̏�����
//=====================================================
void InitModel(void)
{	
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// ���f���̏��̏�����
		memset(&g_aModel[nCntModel], 0, sizeof(g_aModel[nCntModel]));
	
		//�ړI�̌����̏����ݒ�
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
//���f���̔j��
//=========================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (int i = 0; i < (int)g_aModel[nCntModel].nNumMatModel; i++)
		{
			if (g_aModel[nCntModel].pTexture[i] != NULL)
			{// �e�N�X�`���̉��
				g_aModel[nCntModel].pTexture[i]->Release();
				g_aModel[nCntModel].pTexture[i] = NULL;
			}
		}

		//���b�V���̔j��
		if (g_aModel[nCntModel].pMeshModel != NULL)
		{
			g_aModel[nCntModel].pMeshModel->Release();
			g_aModel[nCntModel].pMeshModel = NULL;
		}
		//�}�e���A���̔j��
		if (g_aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_aModel[nCntModel].pBuffMatModel->Release();
			g_aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=========================================
//���f���̍X�V����
//=========================================
void UpdateModel(void)
{
	//�v���C���[�̏����擾����
	PLAYER *pPlayer = GetPlayer();
	ITEM *pItem = GetItem();

	//��ԋ߂��A�C�e���Ƀ|�C���^�[�����炷
	pItem += GetSelectItem();

	//�v���C���[�̋߂��̃��C�������点�鏈��
	PlayerDistanceModel();

	//***********
	//��̏���
	//***********
	if (g_aModel[s_ModelDistance].Type == 6 && GetKeyboardTrigger(DIK_LCONTROL) || GetJoypadTrigger(JOYKEY_A, 0) && g_aModel[s_ModelDistance].bIsLanding)
	{//���f���̃^�C�v��6�̎��A���R���g���[���������Ă��鎞
		PlaySound(SOUND_LABEL_CUTTING);
		pPlayer->state = PLAYER_CUTTING;
	}
}

//=========================================
//���f���̕`�揈��
//=========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for(int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{ 
		if (g_aModel[nCntModel].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorldModel);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorldModel, &g_aModel[nCntModel].mtxWorldModel, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorldModel, &g_aModel[nCntModel].mtxWorldModel, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorldModel);

			//���݂̃}�e���A����ێ�(�ޔ�)
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^���擾����
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aModel[nCntModel].pTexture[nCntMat]);

				//���f���p�[�c�̕`��
				g_aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================
//���f���̏��̎擾
//=========================================
MODEL* GetModel()
{
	return &g_aModel[0];
}

//=========================================
//���f���̐ݒu
//=========================================
void SetModel(D3DXVECTOR3 pos, char MODEL_NAME[128], int nCnt ,int nType)
{
	if (g_aModel[nCnt].bUse == false)
	{
		g_aModel[nCnt].pos = pos;
		g_aModel[nCnt].bUse = true;
		g_aModel[nCnt].Shadow = SetShadow(g_aModel[nCnt].pos, g_aModel[nCnt].rot);		//�e�̐ݒu����
		g_aModel[nCnt].Type = nType;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCnt].pBuffMatModel,
			NULL,
			&g_aModel[nCnt].nNumMatModel,
			&g_aModel[nCnt].pMeshModel);

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_aModel[nCnt].pBuffMatModel->GetBufferPointer();

		// �e���b�V���̃}�e���A�������擾����
		for (int i = 0; i < (int)g_aModel[nCnt].nNumMatModel; i++)
		{
			g_aModel[nCnt].pTexture[i] = NULL;

			if (pMat[i].pTextureFilename != NULL)
			{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
				D3DXCreateTextureFromFileA(pDevice,
					pMat[i].pTextureFilename,
					&g_aModel[nCnt].pTexture[i]);
			}
		}
		int nNumVtx;			//���_��
		DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aModel[nCnt].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCnt].pMeshModel->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aModel[nCnt].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W���擾
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l/�ő�l���擾
			g_aModel[nCnt].vtxMaxModel.x = VertexMAXChange(vtx.x, g_aModel[nCnt].vtxMaxModel.x);
			g_aModel[nCnt].vtxMaxModel.y = VertexMAXChange(vtx.y, g_aModel[nCnt].vtxMaxModel.y);
			g_aModel[nCnt].vtxMaxModel.z = VertexMAXChange(vtx.z, g_aModel[nCnt].vtxMaxModel.z);

			g_aModel[nCnt].vtxMinModel.x = VertexMINChange(vtx.x, g_aModel[nCnt].vtxMinModel.x);
			g_aModel[nCnt].vtxMinModel.y = VertexMINChange(vtx.y, g_aModel[nCnt].vtxMinModel.y);
			g_aModel[nCnt].vtxMinModel.z = VertexMINChange(vtx.z, g_aModel[nCnt].vtxMinModel.z);

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}
		//���_�o�b�t�@�̃A�����b�N
		g_aModel[nCnt].pMeshModel->UnlockVertexBuffer();

		if (g_aModel[nCnt].Type == 1)
		{//���f���̃^�C�v���������(1)�������ꍇ
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
//���f���̓����蔻��̐���
//=========================================
void CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_MODEL; i++)
	{//���̂߂荞�ݔ���
		if (pPos->z - size.z / 2.0f > g_aModel[i].pos.z + g_aModel[i].vtxMaxModel.z
			&& pPos->z + size.z / 2.0f < g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z)
		{
			//���̓����蔻��̐ݒ�
			if (pPosOld->x - size.z / 2.0f <= g_aModel[i].pos.x - g_aModel[i].vtxMinModel.x
				&& pPos->x - size.z / 2.0f > g_aModel[i].pos.x - g_aModel[i].vtxMinModel.x)
			{
				pPos->x = g_aModel[i].pos.x - g_aModel[i].vtxMinModel.x + size.z / 2.0f;
			}
			//�E�̓����蔻��̐ݒ�
			if (pPosOld->x + size.z / 2.0f >= g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x
				&& pPos->x + size.z / 2.0f < g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x)
			{
				pPos->x = g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x - size.z / 2.0f;
			}
		}

		//�㉺�̓����蔻��
		if (pPos->x - size.z / 2.0f > g_aModel[i].pos.x + g_aModel[i].vtxMaxModel.x
			&& pPos->x + size.z / 2.0f < g_aModel[i].pos.x + g_aModel[i].vtxMinModel.x)
		{
			//���̓����蔻��̐ݒ�
			if (pPosOld->z - size.z / 2.0f <= g_aModel[i].pos.z - g_aModel[i].vtxMinModel.z
				&& pPos->z - size.z / 2.0f > g_aModel[i].pos.z - g_aModel[i].vtxMinModel.z)
			{
				pPos->z = g_aModel[i].pos.z - g_aModel[i].vtxMinModel.z + size.z / 2.0f - 0.1f;
			} 

			//�E�̓����蔻��̐ݒ�
			if (pPosOld->z + size.z / 2.0f >= g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z
				&& pPos->z + size.z / 2.0f < g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z)
			{
				pPos->z = g_aModel[i].pos.z + g_aModel[i].vtxMinModel.z - size.z / 2.0f + 0.1f;
			}
		}	
	}
}

//=========================================
//���_�̍ő�l��r�p
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
//���_�̍ŏ��l��r�p
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
//�v���C���[�ƍł��߂��I�u�W�F�N�g�����߂�
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
			{//���f���̃^�C�v���J�E���^�[(3)���������̃��f���̋���
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
//���f���̔ԍ��̎擾
//=========================================
int GetSelectObject()
{
	return s_ModelDistance;
}

//=========================================
//���f���Ƃ̋����̎擾
//=========================================
int GetObjectDistance()
{
	return s_mathMIN;
}