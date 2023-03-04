//=========================================
//
//	�A�C�e���̓��o�͏���
//	Author : �y���m��
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

//�O���[�o���ϐ��錾
ITEM g_aItem[MAX_ITEM];
static int s_nIdxShadow;							//�e�̔���
static int SelectItem;								//���Ԗڂ̃A�C�e���������Ă��邩

//��ԋ߂��̃A�C�e���𔻒肷��̂ɕK�v�Ȑ��l�ꎮ
static float s_mathWidth;
static float s_mathHeight;
static int s_mathMIN;
static int s_mathBox;
//=====================================================
//�A�C�e���̏�����
//=====================================================
void InitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// �A�C�e���̏��̏�����
		memset(&g_aItem[nCntItem], 0, sizeof(g_aItem[nCntItem]));

		g_aItem[nCntItem].vtxMaxItem = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aItem[nCntItem].vtxMaxItem = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		g_aItem[nCntItem].state = ITEM_NORMAL;										//�A�C�e���̏�Ԃ̏�����
	}
	SelectItem = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
}

//=========================================
//�A�C�e���̔j��
//=========================================
void UninitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���b�V���̔j��
		if (g_aItem[nCntItem].pMeshItem != NULL)
		{
			g_aItem[nCntItem].pMeshItem->Release();
			g_aItem[nCntItem].pMeshItem = NULL;
		}

		//�}�e���A���̔j��
		if (g_aItem[nCntItem].pBuffMatItem != NULL)
		{
			g_aItem[nCntItem].pBuffMatItem->Release();
			g_aItem[nCntItem].pBuffMatItem = NULL;
		}
	}
}

//=========================================
//�A�C�e���̍X�V����
//=========================================
void UpdateItem(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	KITCHEN *pKitchen = GetKitchen();
	CONTAIN *pContain = GetContain();

	//���f���Ƃ̋���
	int ModelDistance = GetObjectDistance();
	int KitchenDistance = GetKitchenDistance();
	int ContainDistance = GetContainDistance();

	//��ԋ߂��ɂ���L�b�`��/���f��/�e��𔻒肷��
	int SelectKitchen = GetSelectKitchen();
	int SelectContain = GetSelectContain();
	int SelectModel = GetSelectObject();

	//�|�C���^�[���擾���������i�߂�
	pKitchen += SelectKitchen;				//�L�b�`���̃|�C���^�[
	pModel += SelectModel;					//���f���̃|�C���^�[
	pContain += SelectContain;				//�e��̃|�C���^�[

	//�v���C���[�ƃA�C�e���Ƃ̋����𑪂�A���C����ݒu���鏈��
	PlayerDistanceItem();

	if (ModelDistance <= 10)
	{//���f���Ƃ̋������߂��Ƃ�
		//�v���C���[���A�C�e�����擾���鏈��
		if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) && pPlayer->state == PLAYER_NORMAL && pModel->bIsLanding == false)
		{//�X�y�[�X���������Ƃ����A�v���C���[�̏�Ԃ����������Ă��Ȃ��Ƃ�
			//���A���f���̃^�C�v��������(1)���J�E���^�[(3)�ł͂Ȃ��Ƃ�
			//���f�����v���C���[�̋߂��ɂ��鎞
			if (pModel->Type == 0)
			{
				PlaySound(SOUND_LABEL_OPEN);
				SetItem(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z), "data/MODEL/Object/Material/Material_1.x", ITEM_HAVE, ITEM_MEAT, false);
				pPlayer->state = PLAYER_HAVE;		//�v���C���[�����̂��������Ă����Ԃɂ���
			}
			else if (pModel->Type == 4)
			{
				PlaySound(SOUND_LABEL_OPEN);
				SetItem(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z), "data/MODEL/Object/Material/Material_2.x", ITEM_HAVE, ITEM_CABBAGE, false);
				pPlayer->state = PLAYER_HAVE;		//�v���C���[�����̂��������Ă����Ԃɂ���
			}
		}
		else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) && pPlayer->state == PLAYER_NORMAL && g_aItem[SelectItem].state == ITEM_NORMAL && pModel->bIsLanding == true)
		{//�u���b�N�̏ォ��A�C�e����������鏈��
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
		//�A�C�e���������Ă���Ƃ��X�y�[�X����������A�C�e���������̃u���b�N�̏�ɒu������
		else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0))&& g_aItem[SelectItem].state == ITEM_HAVE && pPlayer->state == PLAYER_HAVE)
		{
			if (s_mathMIN <= 10)
			{//��ԋ߂��ɂ���I�u�W�F�N�g�������������ꍇ
				if (pModel->bIsLanding)
				{//���łɕ����ݒu����Ă���Ƃ�
					if (KitchenDistance <= 10)
					{//�A�C�e���𒲗����̒��ɓ����
						if ((pKitchen->cook == KITCHEN_NORMAL || pKitchen->cook == KITCHEN_NONE) && g_aItem[SelectItem].bCut)
						{//�L�b�`���̏�Ԃ����������ĂȂ� || �ʏ��� || �A�C�e����؂������
							//�������̏���
							KitchenInput();
						}
						else
						{
							//�������Ȃ�
						}
					}
				}
				else if (ContainDistance <= 10)
				{//�e�킪�ł��߂����̂������ꍇ
				 //�������Ȃ�
				}
				else
				{//���f���̏�ɉ�������Ă��Ȃ��Ƃ�
					if (pModel->bIsLanding == false)
					{
						if (ModelDistance <= 10)
						{//���f���Ƃ̋�����10�ȉ��̎�
							pPlayer->state = PLAYER_NORMAL;				//�v���C���[�����������Ă��Ȃ���Ԃɂ���
							g_aItem[SelectItem].state = ITEM_NORMAL;	//�A�C�e����������Ԃɂ���
							pModel->bIsLanding = true;					//���f���̏�ɕ��̂����邩�Ȃ���
							PlaySound(SOUND_LABEL_SELECT);

							//�A�C�e�������f���̏�ɐݒu����
							g_aItem[SelectItem].pos = (D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 11.0f, pModel->pos.z));
						}
					}
				}
			}
		}
		else if (pPlayer->state == PLAYER_CUTTING)
		{//�v���C���[��؂��Ă����Ԃɂ���
			Cutting();
		}
	}

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_aItem[nCnt].state == ITEM_HAVE)
		{//�A�C�e����������Ă���Ƃ�
			if (pPlayer->state == PLAYER_HAVE)
			{
				g_aItem[nCnt].pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 5.0f, pPlayer->pos.z);
			}
		}
	}
}

//=========================================
//�A�C�e���̕`�揈��
//=========================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	//�v���C���[�̏����擾
	PLAYER *pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			if(g_aItem[nCntItem].state == ITEM_NORMAL)
			{ 
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorldItem);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aItem[nCntItem].rot.y, g_aItem[nCntItem].rot.x, g_aItem[nCntItem].rot.z);

			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldItem, &g_aItem[nCntItem].mtxWorldItem, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldItem, &g_aItem[nCntItem].mtxWorldItem, &mtxTrans);
			}
			else if (g_aItem[nCntItem].state == ITEM_HAVE)
			{//�A�C�e����������Ă���Ƃ�
				if (pPlayer->state == PLAYER_HAVE)
				{//�����̔��f
					D3DXMATRIX Kichen_have;

					D3DXMatrixIdentity(&Kichen_have);

					D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DX_PI, 0.0f, 0.0f);

					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxRot);

					//�ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, -5.0f);
					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxTrans);

					D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldItem, &Kichen_have, &pPlayer->mtxWorldPlayer);
				}
			}
			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorldItem);

			//���݂̃}�e���A����ێ�(�ޔ�)
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^���擾����
			pMat = (D3DXMATERIAL*)g_aItem[nCntItem].pBuffMatItem->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aItem[nCntItem].nNumMatItem; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�A�C�e���p�[�c�̕`��
				g_aItem[nCntItem].pMeshItem->DrawSubset(nCntMat);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================
//�A�C�e���̏��̎擾
//=========================================
ITEM* GetItem()
{
	return g_aItem;
}

//=========================================
//�A�C�e���̐ݒu
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
			g_aItem[nCntItem].Shadow = SetShadow(g_aItem[nCntItem].pos, g_aItem[nCntItem].rot);		//�e�̐ݒu����
			g_aItem[nCntItem].state = state;
			g_aItem[nCntItem].type = type;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(ITEM_NAME,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aItem[nCntItem].pBuffMatItem,
				NULL,
				&g_aItem[nCntItem].nNumMatItem,
				&g_aItem[nCntItem].pMeshItem);

			int nNumVtx;			//���_��
			DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

			//���_���̎擾
			nNumVtx = g_aItem[nCntItem].pMeshItem->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aItem[nCntItem].pMeshItem->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aItem[nCntItem].pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

			for (int nCntItemVtx = 0; nCntItemVtx < nNumVtx; nCntItemVtx++)
			{
				//���_���W���擾
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ăA�C�e���̍ŏ��l/�ő�l���擾
				g_aItem[nCntItem].vtxMaxItem.x = VertexMAXChange(vtx.x, g_aItem[nCntItem].vtxMaxItem.x);
				g_aItem[nCntItem].vtxMaxItem.y = VertexMAXChange(vtx.y, g_aItem[nCntItem].vtxMaxItem.y);
				g_aItem[nCntItem].vtxMaxItem.z = VertexMAXChange(vtx.z, g_aItem[nCntItem].vtxMaxItem.z);

				g_aItem[nCntItem].vtxMinItem.x = VertexMINChange(vtx.x, g_aItem[nCntItem].vtxMinItem.x);
				g_aItem[nCntItem].vtxMinItem.y = VertexMINChange(vtx.y, g_aItem[nCntItem].vtxMinItem.y);
				g_aItem[nCntItem].vtxMinItem.z = VertexMINChange(vtx.z, g_aItem[nCntItem].vtxMinItem.z);

				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}
			//���_�o�b�t�@�̃A�����b�N
			g_aItem[nCntItem].pMeshItem->UnlockVertexBuffer();

			break;
		}
	}
}

//=========================================
//�A�C�e���̓����蔻��̐���
//=========================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{//���̂߂荞�ݔ���
		if (pPos->z - size.z / 2.0f > g_aItem[i].pos.z + g_aItem[i].vtxMaxItem.z
			&& pPos->z + size.z / 2.0f < g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z)
		{
			//���̓����蔻��̐ݒ�
			if (pPosOld->x - size.z / 2.0f <= g_aItem[i].pos.x - g_aItem[i].vtxMinItem.x
				&& pPos->x - size.z / 2.0f > g_aItem[i].pos.x - g_aItem[i].vtxMinItem.x)
			{
				pPos->x = g_aItem[i].pos.x - g_aItem[i].vtxMinItem.x + size.z / 2.0f;
			}
			//�E�̓����蔻��̐ݒ�
			if (pPosOld->x + size.z / 2.0f >= g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x
				&& pPos->x + size.z / 2.0f < g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x)
			{
				pPos->x = g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x - size.z / 2.0f;
			}
		}

		//�㉺�̓����蔻��
		if (pPos->x - size.z / 2.0f > g_aItem[i].pos.x + g_aItem[i].vtxMaxItem.x
			&& pPos->x + size.z / 2.0f < g_aItem[i].pos.x + g_aItem[i].vtxMinItem.x)
		{
			//���̓����蔻��̐ݒ�
			if (pPosOld->z - size.z / 2.0f <= g_aItem[i].pos.z - g_aItem[i].vtxMinItem.z
				&& pPos->z - size.z / 2.0f > g_aItem[i].pos.z - g_aItem[i].vtxMinItem.z)
			{
				pPos->z = g_aItem[i].pos.z - g_aItem[i].vtxMinItem.z + size.z / 2.0f - 0.1f;
			}
			//�E�̓����蔻��̐ݒ�
			if (pPosOld->z + size.z / 2.0f >= g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z
				&& pPos->z + size.z / 2.0f < g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z)
			{
				pPos->z = g_aItem[i].pos.z + g_aItem[i].vtxMinItem.z - size.z / 2.0f + 0.1f;
			}
		}
	}
}

//=========================================
//��ԋ߂��̃A�C�e���𔻒肷��
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
//�A�C�e���𒲗�����ɒu�����Ƃ��̏���
//=========================================
void KitchenInput(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	KITCHEN *pKitchen = GetKitchen();

	char ItemFile[255];

	//��ԋ߂��ɂ���L�b�`��/���f���𔻒肷��
	int SelectKitchen = GetSelectKitchen();
	int SelectModel = GetSelectObject();

	pKitchen += SelectKitchen;					//�L�b�`��
	pModel += SelectModel;						//���f��

	pPlayer->state = PLAYER_NORMAL;				//�v���C���[�����������Ă��Ȃ���Ԃɂ���
	g_aItem[SelectItem].state = ITEM_NORMAL;	//�A�C�e����������Ԃɂ���
	pKitchen->cook = KITCHEN_MATERIAL;			//��������̒��ɂ��̂������Ԃɂ���
	pKitchen->type = g_aItem[SelectItem].type;	//���ꂽ�A�C�e���̎w��

	if (pKitchen->bTimer == false)
	{//�L�b�`���^�C�}�[���쓮���Ă��邩���Ă��Ȃ���
		pKitchen->bTimer = true;
		//�L�b�`���^�C�}�[��ݒu����
		SetKTimer(pKitchen->pos);
	}

	pModel->bIsLanding = true;					//���f���̏�ɕ��̂����邩�Ȃ���

	g_aItem[SelectItem].bUse = false;

	//�t�@�C������type������͂�����
	sprintf(ItemFile, "data/MODEL/FOOD/food_%d_fresh.x", g_aItem[SelectItem].type);

	TSKitchen(D3DXVECTOR3(0.0f, 3.0f, 0.0f),ItemFile, SelectKitchen);	//�������̓����ݒu

	if (pModel->Type == 1)
	{//����������Ă���u���b�N��������(1)�������ꍇ
		PlaySound(SOUND_LABEL_HOT);
		pKitchen->cook = KITCHEN_COOK;						//�������̏�Ԃɂ���B
	}
}
//=========================================
//�@�A�C�e���𒲗����鏈��
//=========================================
void Cutting()
{
	//���f���̏����擾����
	MODEL *pModel = GetModel();
	CTIMER *pCTimer = GetCTimer();
	PLAYER *pPlayer = GetPlayer();

	int SelectModel = GetSelectObject();

	pModel += SelectModel;						//���f��

	//�A�C�e���̃t�@�C���������[����
	char ItemFile[255];
	
	if (g_aItem[SelectItem].bCut == false)
	{
		//�����̎��Ԃ��C���N�������g����
		g_aItem[SelectItem].CuttingTime++;

		if (g_aItem[SelectItem].bCook == false)
		{
			g_aItem[SelectItem].bCook = true;
			//�J�b�g�^�C�}�[�̐ݒu
			SetCTimer(g_aItem[SelectItem].pos);
		}
		if (g_aItem[SelectItem].CuttingTime > 180)
		{
			ItemFile[0] = {};
			g_aItem[SelectItem].CuttingTime = 0;			//�����̎��Ԃ�������
			g_aItem[SelectItem].bUse = false;				//���X���������f��

			//�t�@�C������type������͂�����
			sprintf(ItemFile, "data/MODEL/FOOD/food_%d_fresh.x", g_aItem[SelectItem].type);
			//���������A�C�e�����Đݒu����B
			SetItem(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z), ItemFile, ITEM_NORMAL, g_aItem[SelectItem].type, true);
			pCTimer->bUse = false;
			pPlayer->state = PLAYER_NORMAL;
			StopSound(SOUND_LABEL_CUTTING);
		}
	}
}
//=========================================
// ��ԋ߂��A�C�e���̔ԍ��̎擾
//=========================================
int GetSelectItem()
{
	return SelectItem;
}