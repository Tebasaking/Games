//=========================================
//
//	�e��̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include <stdio.h>
#include "main.h"
#include "contain.h"
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
#include "order.h"
#include "score.h"
#include "sound.h"

//�O���[�o���ϐ��錾
CONTAIN g_aContain[MAX_CONTAIN];
FOOD_COUNT g_aFoodCount;							//�H�ו��������ꂽ���̃J�E���g
static int s_nIdxShadow;							//�e�̔���
static int SelectModel;								//��ԋ߂��ɂ���u���b�N�����Ԗڂ�
static int SelectContain;							//���Ԗڂ̗e��������Ă��邩

//��ԋ߂��̗e��𔻒肷��̂ɕK�v�Ȑ��l�ꎮ
static float s_mathWidth;
static float s_mathHeight;
static int s_mathMIN;
static int s_mathBox;
static int State;

//���ꂽ�M���J�E���g����
static int s_ConutDContain;
//�o��������e��̃t�@�C������������
static char filename[255];
//=====================================================
//�e��̏�����
//=====================================================
void InitContain(void)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		// �J�b�g�^�C�}�[�̏��̏�����
		memset(&g_aContain[nCntContain], 0, sizeof(g_aContain[nCntContain]));

		g_aContain[nCntContain].vtxMaxContain = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aContain[nCntContain].vtxMaxContain = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	//�H�ו������擾���ꂽ���̃J�E���g
	memset(&g_aFoodCount, 0, sizeof(g_aFoodCount));

	s_ConutDContain = 0;
	SelectContain = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
	SelectModel = 0;
}

//=========================================
//�e��̔j��
//=========================================
void UninitContain(void)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		//���b�V���̔j��
		if (g_aContain[nCntContain].pMeshContain != NULL)
		{
			g_aContain[nCntContain].pMeshContain->Release();
			g_aContain[nCntContain].pMeshContain = NULL;
		}

		//�}�e���A���̔j��
		if (g_aContain[nCntContain].pBuffMatContain != NULL)
		{
			g_aContain[nCntContain].pBuffMatContain->Release();
			g_aContain[nCntContain].pBuffMatContain = NULL;
		}
	}
}

//=========================================
//�e��̍X�V����
//=========================================
void UpdateContain(void)
{
	PLAYER *pPlayer = GetPlayer();
	MODEL *pModel = GetModel();
	ORDER *pOrder = GetOrder();

	SelectModel = GetSelectObject();
	pModel += SelectModel;

	int ModelDistance = GetObjectDistance();

	//�v���C���[�Ɨe��̋����𑪂�
	PlayerDistanceContain();

	if (ModelDistance <= 10)
	{
		if (pPlayer->state == PLAYER_NORMAL)
		{
			if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)))
			{//�X�y�[�X���������Ƃ�
				if (pModel->Type == 2 && s_ConutDContain < MAX_CONTAIN)
				{//���f���̃^�C�v��2(�M���o��ꏊ)�������ꍇ
					SetContain(D3DXVECTOR3(pModel->pos.x, pModel->pos.y + DISH_SIZE, pModel->pos.z),
						"data/MODEL/Object/Contain/dish.x", CONTAIN_HAVE);
					//���ݏ�ɏo�Ă���M�̐������Z����
					s_ConutDContain++;

					//�v���C���[�������Ă����Ԃɂ���
					pPlayer->state = PLAYER_HAVE;
				}
			}
		}

		if (s_mathMIN <= 10)
		{
			if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) &&
				pPlayer->state == PLAYER_NORMAL && g_aContain[SelectContain].state == CONTAIN_NORMAL && pModel->bIsLanding)
			{//�u���b�N�̏ォ��e���������鏈��
				if (g_aContain[SelectContain].bUse)
				{
					PlaySound(SOUND_LABEL_OPEN);
					pPlayer->state = PLAYER_HAVE;
					g_aContain[SelectContain].state = CONTAIN_HAVE;
					pModel->bIsLanding = false;
				}
			}
			else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) &&
				pPlayer->state == PLAYER_HAVE && g_aContain[SelectContain].state == CONTAIN_HAVE && !pModel->bIsLanding)
			{//�u���b�N�̏�ɗe���ݒu���鏈��
				if (pModel->Type == 3)
				{//�J�E���^�[(3)�ɒ�o����B
					int NumberCount;
					bool ForCheck = false;
					UninitCalculation();

					for (NumberCount = 0; NumberCount < NUM_ORDER + 1; NumberCount++)
					{
						for (int nCntOrder = 0; nCntOrder < NUM_ORDER; nCntOrder++)
						{//�I�[�_�[��nType(�������e)�Ƃł���������������������
							if (pOrder->bUse)
							{//�L���ȃI�[�_�[�̂ݒʂ�
								if (pOrder->nType == (ITEMTYPE)g_aContain[SelectContain].food && pOrder->nNumber == NumberCount)
								{//�I�[�_�[��false�ɂ��āA�X�R�A�����Z����
									pOrder->bUse = false;
									//�I�[�_�[�𓮂���
									MoveOrder(pOrder->nNumber);
									//�I�[�_�[�̌�������炷
									SubOrderCount();
									//�I�[�_�[�ƒ������e���r����for�����ʂ����ꍇtrue�ɂ���
									ForCheck = true;
									//�e���false�ɂ���
									g_aContain[SelectContain].bUse = false;
									//�M�̐����f�N�������g����
									s_ConutDContain--;
									//�v���C���[�̏�Ԃ����������Ă��Ȃ���Ԃ�
									pPlayer->state = PLAYER_NORMAL;
									//�ł��������̏�����
									g_aContain[SelectContain].food = 0;

									if (pOrder->nType == 1)
									{
										g_aFoodCount.meat++;
										//�X�R�A�̉��Z
										AddScore(10);
									}
									else if (pOrder->nType == 2)
									{
										g_aFoodCount.cabbage++;
										//�X�R�A�̉��Z
										AddScore(10);
									}
									else if (pOrder->nType == 3)
									{
										g_aFoodCount.vegetable++;
										//�X�R�A�̉��Z
										AddScore(30);
									}
									PlaySound(SOUND_LABEL_REGI);
									break;
								}
							}
							//�I�[�_�[�̓��e��S�Ċm�F���邽�߂Ƀ|�C���^�[��i�߂�
							pOrder += 1;
						}
						//�I�[�_�[�̃|�C���^�[������������
						pOrder = GetOrder();

						if (ForCheck)
						{//true�̎��A��d���[�v��j�����邽�߂�break����B
							ForCheck = false;
							break;
						}
					}
					//�ԍ����J�E���g���鐔�l������������
					NumberCount = 0;
				}
				else if (pModel->Type == 2)
				{
					//�������Ȃ�
				}
				else
				{
					pPlayer->state = PLAYER_NORMAL;
					g_aContain[SelectContain].state = CONTAIN_NORMAL;
					g_aContain[SelectContain].pos = D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z);
					pModel->bIsLanding = true;
				}
				PlaySound(SOUND_LABEL_OPEN);
			}
		}

		for (int nCnt = 0; nCnt < MAX_CONTAIN; nCnt++)
		{
			if (g_aContain[nCnt].state == CONTAIN_HAVE)
			{//�e�킪������Ă���Ƃ�
				if (pPlayer->state == PLAYER_HAVE)
				{
					g_aContain[nCnt].pos = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 10.0f, pPlayer->pos.z);
				}
			}
		}
	}
}

//=========================================
//�e��̕`�揈��
//=========================================
void DrawContain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	//�v���C���[�̏����擾
	PLAYER *pPlayer = GetPlayer();

	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		if (g_aContain[nCntContain].bUse)
		{
			if (g_aContain[nCntContain].state == CONTAIN_NORMAL)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aContain[nCntContain].mtxWorldContain);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aContain[nCntContain].rot.y, g_aContain[nCntContain].rot.x, g_aContain[nCntContain].rot.z);

				D3DXMatrixMultiply(&g_aContain[nCntContain].mtxWorldContain, &g_aContain[nCntContain].mtxWorldContain, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aContain[nCntContain].pos.x, g_aContain[nCntContain].pos.y, g_aContain[nCntContain].pos.z);
				D3DXMatrixMultiply(&g_aContain[nCntContain].mtxWorldContain, &g_aContain[nCntContain].mtxWorldContain, &mtxTrans);
			}
			else if (g_aContain[nCntContain].state == CONTAIN_HAVE)
			{//�e�킪������Ă���Ƃ�
				if (pPlayer->state == PLAYER_HAVE)
				{//�����̔��f
					D3DXMATRIX Kichen_have;

					D3DXMatrixIdentity(&Kichen_have);

					D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DX_PI, 0.0f, 0.0f);

					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxRot);

					//�ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, -5.0f);
					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxTrans);

					D3DXMatrixMultiply(&g_aContain[nCntContain].mtxWorldContain, &Kichen_have, &pPlayer->mtxWorldPlayer);
				}
		}
			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aContain[nCntContain].mtxWorldContain);

			//���݂̃}�e���A����ێ�(�ޔ�)
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^���擾����
			pMat = (D3DXMATERIAL*)g_aContain[nCntContain].pBuffMatContain->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aContain[nCntContain].nNumMatContain; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e��p�[�c�̕`��
				g_aContain[nCntContain].pMeshContain->DrawSubset(nCntMat);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================
//�e��̏��̎擾
//=========================================
CONTAIN* GetContain()
{
	return g_aContain;
}

//=========================================
//�ǂ̗e�킪��ԋ߂����̏��̎擾
//=========================================
int GetSelectContain()
{
	return SelectContain;
}

//=========================================
//�e��̐ݒu
//=========================================
void SetContain(D3DXVECTOR3 pos, char CONTAIN_NAME[128], CONTAIN_STATE state)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		if (g_aContain[nCntContain].bUse == false)
		{
			g_aContain[nCntContain].pos = pos;
			g_aContain[nCntContain].bUse = true;
			g_aContain[nCntContain].Shadow = SetShadow(g_aContain[nCntContain].pos, g_aContain[nCntContain].rot);		//�e�̐ݒu����
			g_aContain[nCntContain].state = state;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(CONTAIN_NAME,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aContain[nCntContain].pBuffMatContain,
				NULL,
				&g_aContain[nCntContain].nNumMatContain,
				&g_aContain[nCntContain].pMeshContain);

			int nNumVtx;			//���_��
			DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

			//���_���̎擾
			nNumVtx = g_aContain[nCntContain].pMeshContain->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aContain[nCntContain].pMeshContain->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aContain[nCntContain].pMeshContain->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

			//���_�o�b�t�@�̃A�����b�N
			g_aContain[nCntContain].pMeshContain->UnlockVertexBuffer();

			break;
		}
	}
}

//=========================================
//�e��̌����ڂ̏�Ԃ̕ω�
//=========================================
void TSContain(D3DXVECTOR3 pos, CONTAIN_STATE state, CONTAIN_COOKING cook, ITEMTYPE type)
{
	for (int nCntContain = 0; nCntContain < MAX_CONTAIN; nCntContain++)
	{
		if (g_aContain[nCntContain].bUse == false)
		{
			g_aContain[nCntContain].pos = pos;
			g_aContain[nCntContain].bUse = true;
			g_aContain[nCntContain].Shadow = SetShadow(g_aContain[nCntContain].pos, g_aContain[nCntContain].rot);		//�e�̐ݒu����
			Calculation(type);
			g_aContain[nCntContain].state = state;
			g_aContain[nCntContain].cook = cook;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(filename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aContain[nCntContain].pBuffMatContain,
				NULL,
				&g_aContain[nCntContain].nNumMatContain,
				&g_aContain[nCntContain].pMeshContain);

			int nNumVtx;			//���_��
			DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

									//���_���̎擾
			nNumVtx = g_aContain[nCntContain].pMeshContain->GetNumVertices();
			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aContain[nCntContain].pMeshContain->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_aContain[nCntContain].pMeshContain->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

			for (int nCntContainVtx = 0; nCntContainVtx < nNumVtx; nCntContainVtx++)
			{
				//���_���W���擾
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ėe��̍ŏ��l/�ő�l���擾
				g_aContain[nCntContain].vtxMaxContain.x = VertexMAXChange(vtx.x, g_aContain[nCntContain].vtxMaxContain.x);
				g_aContain[nCntContain].vtxMaxContain.y = VertexMAXChange(vtx.y, g_aContain[nCntContain].vtxMaxContain.y);
				g_aContain[nCntContain].vtxMaxContain.z = VertexMAXChange(vtx.z, g_aContain[nCntContain].vtxMaxContain.z);

				g_aContain[nCntContain].vtxMinContain.x = VertexMINChange(vtx.x, g_aContain[nCntContain].vtxMinContain.x);
				g_aContain[nCntContain].vtxMinContain.y = VertexMINChange(vtx.y, g_aContain[nCntContain].vtxMinContain.y);
				g_aContain[nCntContain].vtxMinContain.z = VertexMINChange(vtx.z, g_aContain[nCntContain].vtxMinContain.z);

				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}
			//���_�o�b�t�@�̃A�����b�N
			g_aContain[nCntContain].pMeshContain->UnlockVertexBuffer();

			break;
		}
	}
}
//=========================================
//�e��̓����蔻��̐���
//=========================================
void CollisionContain(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_CONTAIN; i++)
	{//���̂߂荞�ݔ���
		if (pPos->z - size.z / 2.0f > g_aContain[i].pos.z + g_aContain[i].vtxMaxContain.z
			&& pPos->z + size.z / 2.0f < g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z)
		{
			//���̓����蔻��̐ݒ�
			if (pPosOld->x - size.z / 2.0f <= g_aContain[i].pos.x - g_aContain[i].vtxMinContain.x
				&& pPos->x - size.z / 2.0f > g_aContain[i].pos.x - g_aContain[i].vtxMinContain.x)
			{
				pPos->x = g_aContain[i].pos.x - g_aContain[i].vtxMinContain.x + size.z / 2.0f;
			}
			//�E�̓����蔻��̐ݒ�
			if (pPosOld->x + size.z / 2.0f >= g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x
				&& pPos->x + size.z / 2.0f < g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x)
			{
				pPos->x = g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x - size.z / 2.0f;
			}
		}

		//�㉺�̓����蔻��
		if (pPos->x - size.z / 2.0f > g_aContain[i].pos.x + g_aContain[i].vtxMaxContain.x
			&& pPos->x + size.z / 2.0f < g_aContain[i].pos.x + g_aContain[i].vtxMinContain.x)
		{
			//���̓����蔻��̐ݒ�
			if (pPosOld->z - size.z / 2.0f <= g_aContain[i].pos.z - g_aContain[i].vtxMinContain.z
				&& pPos->z - size.z / 2.0f > g_aContain[i].pos.z - g_aContain[i].vtxMinContain.z)
			{
				pPos->z = g_aContain[i].pos.z - g_aContain[i].vtxMinContain.z + size.z / 2.0f - 0.1f;
			}

			//�E�̓����蔻��̐ݒ�
			if (pPosOld->z + size.z / 2.0f >= g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z
				&& pPos->z + size.z / 2.0f < g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z)
			{
				pPos->z = g_aContain[i].pos.z + g_aContain[i].vtxMinContain.z - size.z / 2.0f + 0.1f;
			}
		}
	}
}

//=========================================
//��ԋ߂��̗e��𔻒肷��
//=========================================
void PlayerDistanceContain()
{
	PLAYER *pPlayer = GetPlayer();
	s_mathMIN = 1000000;

	for (int nCnt = 0; nCnt < MAX_CONTAIN; nCnt++)
	{
		if (g_aContain[nCnt].bUse == true)
		{
			s_mathWidth = pPlayer->pos.x - g_aContain[nCnt].pos.x;
			s_mathHeight = pPlayer->pos.z - g_aContain[nCnt].pos.z;

			s_mathBox = (int)sqrtf(s_mathWidth * s_mathWidth + s_mathHeight * s_mathHeight);

			if (s_mathBox <= s_mathMIN)
			{
				s_mathMIN = s_mathBox;
				SelectContain = nCnt;
			}
		}
	}

	if (s_mathMIN <= 10)
	{
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMaxContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMaxContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMaxContain.z));

		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMinContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMinContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));

		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMinContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMaxContain.z), D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMaxContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMaxContain.x, g_aContain[SelectContain].vtxMinContain.y, g_aContain[SelectContain].vtxMaxContain.z));
		SetObjectLine(g_aContain[SelectContain].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aContain[SelectContain].vtxMinContain, D3DXVECTOR3(g_aContain[SelectContain].vtxMinContain.x, g_aContain[SelectContain].vtxMaxContain.y, g_aContain[SelectContain].vtxMinContain.z));
	}
}
//=========================================
//�e��ƃv���C���[�̋����̎擾
//=========================================
int GetContainDistance()
{
	return s_mathMIN;
}
//=========================================
//bit���Z�̌v�Z
//=========================================
void Calculation(ITEMTYPE item)
{
	//�v���C���[�Ɨe��̋����𑪂�
	PlayerDistanceContain();

	//Item�ԍ��̉��Z
	g_aContain[SelectContain].food |= item;

	if (UseFood(ITEM_CABBAGE, g_aContain[SelectContain].food)
		&& UseFood(ITEM_MEAT, g_aContain[SelectContain].food))
	{
		sprintf(filename, "data/MODEL/FOOD/complete_1.x");
	}
	else if (UseFood(item , g_aContain[SelectContain].food))
	{
		sprintf(filename,"data/MODEL/Object/Contain/food_%d.x", item);
	}
}

//=========================================
//�e��ɉ����������Ă��邩���肷�鏈��
//=========================================
bool UseFood(ITEMTYPE type, unsigned int dish)
{
	return (type & dish) != 0;
}
//=========================================
//�t���O�̖�������
//=========================================
void UninitCalculation()
{
	//���ׂẴt���O�𖳌��ɂ���
	State = 0;
}

//=========================================
//�ǂ̐H�ו�����ꂽ���J�E���g�������l���擾����
//=========================================
FOOD_COUNT* GetFoodCount()
{
	return &g_aFoodCount;
}