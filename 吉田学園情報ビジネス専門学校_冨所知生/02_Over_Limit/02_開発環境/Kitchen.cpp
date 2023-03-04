//=========================================
//
//	�L�b�`���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include <stdio.h>
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
#include "kitchen.h"
#include "objectline.h"
#include "contain.h"
#include "kitchentimer.h"
#include "sound.h"

//�O���[�o���ϐ��錾
KITCHEN g_aKitchen[MAX_KITCHEN];
static int s_nIdxShadow;							//�e�̔���
static int nCntNumKeySet = 0;						//���ݍĐ�����KeySet�ԍ�
static int g_nCntFrame = 0;							//�t���[����
static int s_mathMIN;								//�ŏ���
static int SelectKitchen = 0;						//�߂��L�b�`���̔ԍ�
//=====================================================
//�L�b�`���̏�����
//=====================================================
void InitKitchen(void)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		// �L�b�`���̏��̏�����
		memset(&g_aKitchen[nCntKitchen], 0, sizeof(g_aKitchen[nCntKitchen]));

		g_aKitchen[nCntKitchen].state = KITCHEN_NORMAL;										//�L�b�`���̏�Ԃ̏�����
		g_aKitchen[nCntKitchen].cook = KITCHEN_NONE;

		for (int nCntParts = 0; nCntParts < MAX_KITCHEN_PARTS; nCntParts++)
		{
			g_aKitchen[nCntKitchen].aParts[nCntParts].bUse = false;
			g_aKitchen[nCntKitchen].aParts[nCntParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aKitchen[nCntKitchen].aParts[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aKitchen[nCntKitchen].aParts[nCntParts].nIdxModelParent = 0;
			g_aKitchen[nCntKitchen].aParts[nCntParts].fFrame = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�A�j���[�V�����̃t���[�����̏�����
		}
	}
}

//=========================================
//�L�b�`���̔j��
//=========================================
void UninitKitchen(void)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		//���b�V���̔j��
		if (g_aKitchen[nCntKitchen].pMeshKitchen != NULL)
		{
			g_aKitchen[nCntKitchen].pMeshKitchen->Release();
			g_aKitchen[nCntKitchen].pMeshKitchen = NULL;
		}

		//�}�e���A���̔j��
		if (g_aKitchen[nCntKitchen].pBuffMatKitchen != NULL)
		{
			g_aKitchen[nCntKitchen].pBuffMatKitchen->Release();
			g_aKitchen[nCntKitchen].pBuffMatKitchen = NULL;
		}

		for (int nCntParts = 0; nCntParts < MAX_KITCHEN_PARTS; nCntParts++)
		{
			//���b�V���̔j��
			if (g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh != NULL)
			{
				g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->Release();
				g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat != NULL)
			{
				g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat->Release();
				g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat = NULL;
			}
		}
	}
}

//=========================================
//�L�b�`���̍X�V����
//=========================================
void UpdateKitchen(void)
{
	//�v���C���[�̏����擾����
	PLAYER *pPlayer = GetPlayer();
	//���f���̏����擾����
	MODEL *pModel = GetModel();
	//�e��̏����擾����
	CONTAIN *pContain = GetContain();
	//�L�b�`���^�C�}�[�̏����擾����
	KTIMER *pKTimer = GetKTimer();
	//���f���ƃv���C���[�̋���
	int ModelDistance = GetObjectDistance();
	//�e��ƃv���C���[�̋���
	int ContainDistance = GetContainDistance();

	//�ł��߂����f���Ɨe��̔ԍ�
	int SelectModel = GetSelectObject();
	int SelectContain = GetSelectContain();

	//�|�C���^�[���ł��߂����̂ɉ��Z����
	pModel += SelectModel;
	pContain += SelectContain;

	//�L�b�`���ƃL�b�`���̋����𑪂�
	PlayerDistanceKitchen();

	//�L�b�`���Œ������鏈��
	LetsCooking();

	if (s_mathMIN <= 10)
	{
		if (ModelDistance <= 10)
		{
			if (((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0))) &&
				pPlayer->state == PLAYER_NORMAL && g_aKitchen[SelectKitchen].state == KITCHEN_NORMAL && pModel->bIsLanding == true)
			{//�u���b�N�̏ォ�璲�������������鏈��
				if (g_aKitchen[SelectKitchen].bUse)
				{
					pPlayer->state = PLAYER_HAVE;											//�v���C���[�������Ă����Ԃɂ���
					g_aKitchen[SelectKitchen].state = KITCHEN_HAVE;							//��������������Ă����Ԃɂ���
					pModel->bIsLanding = false;												//���f���̏�ɉ����Ȃ���Ԃɂ���

					//��ԋ߂����f������������(1)�Ȃ�
					if (pModel->Type == 1)
					{
						if (g_aKitchen[SelectKitchen].cook == KITCHEN_COOK)
						{//�������������ꍇ
							g_aKitchen[SelectKitchen].cook = KITCHEN_MATERIAL;				//�������̏�Ԃ𒆂ɑf�ނ������Ԃɂ���
							pModel->cook = false;
							StopSound(SOUND_LABEL_HOT);
							PlaySound(SOUND_LABEL_OPEN);
						}
						if (g_aKitchen[SelectKitchen].cook == KITCHEN_OVER)
						{//�����������Ƃ������ꍇ
							g_aKitchen[SelectKitchen].cook = KITCHEN_COMPLETE;				//�������̏�Ԃ�����������Ԃɂ���
							StopSound(SOUND_LABEL_HOTOVER);
							PlaySound(SOUND_LABEL_OPEN);
							pModel->cook = false;
						}
						for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
						{
							pKTimer->bUse = false;											//�L�b�`���^�C�}�[���g�p���Ă��Ȃ���Ԃɂ���
							pKTimer++;
						}
						pKTimer = GetKTimer();

						g_aKitchen[SelectKitchen].bTimer = false;							//�^�C�}�[���g���ĂȂ���Ԃɂ���
					}
				}
			}
			else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) 
				&& pPlayer->state == PLAYER_HAVE && g_aKitchen[SelectKitchen].state == KITCHEN_HAVE && pModel->Type != 5)
			{//�u���b�N�̏�ɒ��������ݒu���鏈��
				if (ContainDistance <= 10)
				{//�e��̋߂��ɒ�������������ꍇ
					//�����������������Ԃ������ꍇ
					if (g_aKitchen[SelectKitchen].cook == KITCHEN_COMPLETE)
					{//�M�ɐ���t����
						g_aKitchen[SelectKitchen].CookCount = 0;							//�������Ԃ̃J�E���g��0�ɂ���

						if (pContain->food != g_aKitchen[SelectKitchen].type)
						{
							pContain->bUse = false;
							//�t�@�C������type������͂�����
							g_aKitchen[SelectKitchen].cook = KITCHEN_NONE;						//�������Ă��Ȃ���Ԃɂ���
							g_aKitchen[SelectKitchen].aParts[2].bUse = false;					//�������̒��ŏĂ���Ă�����̂�false�ɂ���
							PlaySound(SOUND_LABEL_SELECT);

							TSContain(pContain->pos, CONTAIN_NORMAL, CONTAIN_COMPLETE, g_aKitchen[SelectKitchen].type);	//�M�̒��g���L�b�`���̒��ɓ����Ă������̂ɂ���
						}
					}
				}
				else
				{
					if (pModel->bIsLanding == false)
					{
						pPlayer->state = PLAYER_NORMAL;																					//�v���C���[�����������Ă��Ȃ���Ԃɂ���
						g_aKitchen[SelectKitchen].state = KITCHEN_NORMAL;																//��������������Ă��Ȃ���Ԃɂ���
						g_aKitchen[SelectKitchen].pos = D3DXVECTOR3(pModel->pos.x, pModel->pos.y + 10.0f, pModel->pos.z);				//�����������f���̐^��ɐݒu����
						g_aKitchen[SelectKitchen].rot = D3DXVECTOR3(pPlayer->rot.x, pPlayer->rot.y + D3DX_PI, -pPlayer->rot.z);			//�������̊p�x�𒲐�����
						pModel->bIsLanding = true;																						//���f���̏�ɕ��������Ԃɂ���

						//��ԋ߂����f������������(1)�Ȃ�
						if (pModel->Type == 1)
						{
							if (g_aKitchen[SelectKitchen].cook == KITCHEN_MATERIAL)
							{//�ݒu�������̂����������O�������Ƃ�
								g_aKitchen[SelectKitchen].cook = KITCHEN_COOK;					//�������̏�Ԃ𒲗����ɂ���
								PlaySound(SOUND_LABEL_HOT);
								pModel->cook = true;											//���f���𒲗����ɂ���
							}
							else if (g_aKitchen[SelectKitchen].cook == KITCHEN_COMPLETE)
							{//�ݒu�������̂̒����������ゾ������
								g_aKitchen[SelectKitchen].cook = KITCHEN_OVER;					//�������̏�Ԃ��ł�����Ԃɂ���
								PlaySound(SOUND_LABEL_HOTOVER);
								pModel->cook = true;											//���f���𒲗����ɂ���
							}
							if (g_aKitchen[SelectKitchen].bTimer == false)
							{//�L�b�`���^�C�}�[���쓮���Ă��邩���Ă��Ȃ���
								g_aKitchen[SelectKitchen].bTimer = true;
								//�L�b�`���^�C�}�[��ݒu����
								SetKTimer(g_aKitchen[SelectKitchen].pos);
							}
							PlaySound(SOUND_LABEL_SELECT);
						}
					}
				}
			}
			else if ((GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_B, 0)) 
				&& pPlayer->state == PLAYER_HAVE && g_aKitchen[SelectKitchen].state == KITCHEN_HAVE && pModel->Type == 5)
			{//�S�~��(5)�ɒ������̒��ɂ�����̂��̂Ă�
				g_aKitchen[SelectKitchen].aParts[2].bUse = false;					//�������̒��ŏĂ���Ă�����̂�false�ɂ���
				//pKTimer->bUse = false;											//�L�b�`���^�C�}�[���g�p���Ă��Ȃ���Ԃɂ���
				g_aKitchen[SelectKitchen].cook = KITCHEN_NONE;						//���f�����������Ă��Ȃ���Ԃɂ���
				g_aKitchen[SelectKitchen].CookCount = 0;							//�������Ԃ�����������
				g_aKitchen[SelectKitchen].bTimer = false;							//�^�C�}�[���g���ĂȂ���Ԃɂ���

				for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
				{
					pKTimer->bUse = false;											//�L�b�`���^�C�}�[���g�p���Ă��Ȃ���Ԃɂ���
					pKTimer++;
				}
				pKTimer = GetKTimer();
			}
		}
	}
	//���ׂẴL�b�`���ŉ񂷏���
	for (int nCnt = 0; nCnt < MAX_KITCHEN; nCnt++)
	{
		if (g_aKitchen[nCnt].state == KITCHEN_HAVE)
		{//�L�b�`���������Ă�����
			g_aKitchen[nCnt].pos = pPlayer->pos;			//�L�b�`���̈ʒu���v���C���[�̈ʒu�ɂ���
		}
	}
}

//=========================================
//�L�b�`���̕`�揈��
//=========================================
void DrawKitchen(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	
	PLAYER *pPlayer = GetPlayer();

	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		if (g_aKitchen[nCntKitchen].bUse)
		{//���������g�p���Ă��邩���Ă��Ȃ���
			if (g_aKitchen[nCntKitchen].state == KITCHEN_NORMAL)
			{//�����𔽉f
			 //���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aKitchen[nCntKitchen].mtxWorldKitchen);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aKitchen[nCntKitchen].rot.y, g_aKitchen[nCntKitchen].rot.x, g_aKitchen[nCntKitchen].rot.z);

				D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].mtxWorldKitchen, &g_aKitchen[nCntKitchen].mtxWorldKitchen, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aKitchen[nCntKitchen].pos.x, g_aKitchen[nCntKitchen].pos.y, g_aKitchen[nCntKitchen].pos.z);
				D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].mtxWorldKitchen, &g_aKitchen[nCntKitchen].mtxWorldKitchen, &mtxTrans);
			}
			else if (g_aKitchen[nCntKitchen].state == KITCHEN_HAVE)
			{//�������������Ă���Ƃ�
				if (pPlayer->state == PLAYER_HAVE)
				{//�����̔��f
					D3DXMATRIX Kichen_have;

					//���[���h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&Kichen_have);

					//�����𔽉f
					D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DX_PI, 0.0f, 0.0f);

					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxRot);

					//�ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, 0.0f, 3.0f, -10.0f);
					D3DXMatrixMultiply(&Kichen_have, &Kichen_have, &mtxTrans);
					
					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].mtxWorldKitchen, &Kichen_have,&pPlayer->mtxWorldPlayer);
				}
			}

			for (int nCntParts = 0; nCntParts < MAX_KITCHEN_PARTS; nCntParts++)
			{
				if (g_aKitchen[nCntKitchen].aParts[nCntParts].bUse)
				{//�������̎��������L���Ȏ�
					//���[���h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld);

					//�����𔽉f
					D3DXMatrixRotationYawPitchRoll(&mtxRot,
						g_aKitchen[nCntKitchen].aParts[nCntParts].rot.y, g_aKitchen[nCntKitchen].aParts[nCntParts].rot.x, g_aKitchen[nCntKitchen].aParts[nCntParts].rot.z);

					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &mtxRot);

					//�ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, g_aKitchen[nCntKitchen].aParts[nCntParts].pos.x, g_aKitchen[nCntKitchen].aParts[nCntParts].pos.y, g_aKitchen[nCntKitchen].aParts[nCntParts].pos.z);
					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &mtxTrans);

					D3DXMATRIX mtxParent;

					//�e�̃��[���h�}�g���N�X�̐ݒ�
					if (nCntParts == g_aKitchen[nCntKitchen].aParts[nCntParts].nIdxModelParent)
					{
						mtxParent = g_aKitchen[nCntKitchen].mtxWorldKitchen;
					}
					else
					{
						//�����̐e�̃}�g���N�X����
						mtxParent = g_aKitchen[nCntKitchen].aParts[g_aKitchen[nCntKitchen].aParts[nCntParts].nIdxModelParent].mtxWorld;
					}

					//���[�J�����W�����[���h���W�ɓK��������
					D3DXMatrixMultiply(&g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld, &mtxParent);

					//���[���h�}�g���b�N�X���X�V
					pDevice->SetTransform(D3DTS_WORLD, &g_aKitchen[nCntKitchen].aParts[nCntParts].mtxWorld);

					//���݂̃}�e���A����ێ�(�ޔ�)
					pDevice->GetMaterial(&matDef);

					//�}�e���A���f�[�^�̃|�C���^���擾����
					pMat = (D3DXMATERIAL*)g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)g_aKitchen[nCntKitchen].aParts[nCntParts].nNumMat; nCntMat++)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//�L�b�`���p�[�c�̕`��
						g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->DrawSubset(nCntMat);
					}

					//�ێ����Ă����}�e���A����߂�
					pDevice->SetMaterial(&matDef);
				}
			}
		}
	}
}

//=========================================
//�L�b�`���̏��̎擾
//=========================================
KITCHEN* GetKitchen()
{
	return g_aKitchen;
}

//=========================================
//�L�b�`���̐ݒu
//=========================================
void SetKitchen(D3DXVECTOR3 pos,KITCHEN_STATE state)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		if (g_aKitchen[nCntKitchen].bUse == false)
		{
			g_aKitchen[nCntKitchen].pos = pos;
			g_aKitchen[nCntKitchen].bUse = true;
			g_aKitchen[nCntKitchen].Shadow = SetShadow(g_aKitchen[nCntKitchen].pos, g_aKitchen[nCntKitchen].rot);		//�e�̐ݒu����
			g_aKitchen[nCntKitchen].state = state;

			break;
		}
	}
}

//=========================================
//���f���̃p�[�c�̐ݒu
//=========================================
void SetKitchenParts(D3DXVECTOR3 pos, char KITCHEN_NAME[128], int nCntParts)
{
	for (int nCntKitchen = 0; nCntKitchen < MAX_KITCHEN; nCntKitchen++)
	{
		g_aKitchen[nCntKitchen].aParts[nCntParts].pos = pos;
		g_aKitchen[nCntKitchen].aParts[1].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

		g_aKitchen[nCntKitchen].aParts[nCntParts].posOrigin = g_aKitchen[nCntKitchen].aParts[nCntParts].pos;
		g_aKitchen[nCntKitchen].aParts[nCntParts].rotOrigin = g_aKitchen[nCntKitchen].aParts[nCntParts].rot;
		g_aKitchen[nCntKitchen].aParts[nCntParts].bUse = true;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(KITCHEN_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aKitchen[nCntKitchen].aParts[nCntParts].pBuffMat,
			NULL,
			&g_aKitchen[nCntKitchen].aParts[nCntParts].nNumMat,
			&g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh);

		int nNumVtx;			//���_��
		DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W���擾
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ăL�b�`���̍ŏ��l/�ő�l���擾
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.x = VertexMAXChange(vtx.x, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.x);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.y = VertexMAXChange(vtx.y, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.y);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.z = VertexMAXChange(vtx.z, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMax.z);

			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.x = VertexMINChange(vtx.x, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.x);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.y = VertexMINChange(vtx.y, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.y);
			g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.z = VertexMINChange(vtx.z, g_aKitchen[nCntKitchen].aParts[nCntParts].vtxMin.z);

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}
		//���_�o�b�t�@�̃A�����b�N
		g_aKitchen[nCntKitchen].aParts[nCntParts].pMesh->UnlockVertexBuffer();
	}
}

//=========================================
//�L�b�`���̌����ڂ̏�Ԃ̕ω�
//=========================================
void TSKitchen(D3DXVECTOR3 pos, char KITCHEN_NAME[128],int nCnt)
{
		g_aKitchen[nCnt].aParts[2].posOrigin = g_aKitchen[nCnt].aParts[2].pos;
		g_aKitchen[nCnt].aParts[2].rotOrigin = g_aKitchen[nCnt].aParts[2].rot;
		g_aKitchen[nCnt].aParts[2].pos = pos;
		g_aKitchen[nCnt].aParts[2].bUse = true;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(KITCHEN_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aKitchen[nCnt].aParts[2].pBuffMat,
			NULL,
			&g_aKitchen[nCnt].aParts[2].nNumMat,
			&g_aKitchen[nCnt].aParts[2].pMesh);

		int nNumVtx;			//���_��
		DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aKitchen[nCnt].aParts[2].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aKitchen[nCnt].aParts[2].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aKitchen[nCnt].aParts[2].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W���擾
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ăL�b�`���̍ŏ��l/�ő�l���擾
			g_aKitchen[nCnt].aParts[2].vtxMax.x = VertexMAXChange(vtx.x, g_aKitchen[nCnt].aParts[2].vtxMax.x);
			g_aKitchen[nCnt].aParts[2].vtxMax.y = VertexMAXChange(vtx.y, g_aKitchen[nCnt].aParts[2].vtxMax.y);
			g_aKitchen[nCnt].aParts[2].vtxMax.z = VertexMAXChange(vtx.z, g_aKitchen[nCnt].aParts[2].vtxMax.z);

			g_aKitchen[nCnt].aParts[2].vtxMin.x = VertexMINChange(vtx.x, g_aKitchen[nCnt].aParts[2].vtxMin.x);
			g_aKitchen[nCnt].aParts[2].vtxMin.y = VertexMINChange(vtx.y, g_aKitchen[nCnt].aParts[2].vtxMin.y);
			g_aKitchen[nCnt].aParts[2].vtxMin.z = VertexMINChange(vtx.z, g_aKitchen[nCnt].aParts[2].vtxMin.z);

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}
		//���_�o�b�t�@�̃A�����b�N
		g_aKitchen[nCnt].aParts[2].pMesh->UnlockVertexBuffer();
}
//=========================================
//�������̏���
//=========================================
void LetsCooking()
{
	//�L�b�`���^�C�}�[�̏����擾
	KTIMER *pKTimer = GetKTimer();

	//enum���t�@�C�����ɂ��邽�߂̊֐�
	char KitchenFile[255];

	for (int nCnt = 0; nCnt < MAX_KITCHEN; nCnt++)
	{
		if (g_aKitchen[nCnt].cook == KITCHEN_COOK)
		{//���f�����������������ꍇ
			g_aKitchen[nCnt].CookCount++;

			if (g_aKitchen[nCnt].CookCount == 360)
			{//2�b��������
				g_aKitchen[nCnt].CookCount = 0;
				sprintf(KitchenFile, "data/MODEL/FOOD/food_%d_cook.x", g_aKitchen[nCnt].type);				//type��TSKitchen�ɓ��͂��邽�߂̏���
				TSKitchen(D3DXVECTOR3(0.0f,0.0f,0.0f), KitchenFile,nCnt);
				PlaySound(SOUND_LABEL_HOTOVER);
				g_aKitchen[nCnt].cook = KITCHEN_OVER;
			}
		}
		else if (g_aKitchen[nCnt].cook == KITCHEN_OVER)
		{//���f������������������M����Ă����ꍇ
			g_aKitchen[nCnt].CookCount++;

			if (g_aKitchen[nCnt].CookCount == 360)
			{//6�b��������
				g_aKitchen[nCnt].CookCount = 0;
				sprintf(KitchenFile, "data/MODEL/FOOD/food_%d_over.x", g_aKitchen[nCnt].type);				//type��TSKitchen�ɓ��͂��邽�߂̏���
				TSKitchen(D3DXVECTOR3(0.0f,0.0f,0.0f), KitchenFile,nCnt);
				g_aKitchen[nCnt].cook = KITCHEN_BURN;
				g_aKitchen[nCnt].bTimer = false;							//�^�C�}�[���g���Ă��Ȃ���Ԃɂ���
				
				for (int i = 0; i < MAX_KITCHENTIMER; i++)
				{
					pKTimer->bUse = false;										//�L�b�`���^�C�}�[��false�ɂ���
					pKTimer++;
				}
				pKTimer = GetKTimer();
			}
		}
	}
}
//=========================================
//��ԋ߂��̃L�b�`���𔻒肷��
//=========================================
void PlayerDistanceKitchen()
{
	PLAYER *pPlayer = GetPlayer();
	s_mathMIN = 1000000;

	float mathWidth = 0;
	float mathHeight = 0;
	float mathBox = 0;

	for (int nCnt = 0; nCnt < MAX_KITCHEN; nCnt++)
	{
		if (g_aKitchen[nCnt].bUse == true)
		{
			mathWidth = (pPlayer->pos.x - g_aKitchen[nCnt].pos.x);
			mathHeight = (pPlayer->pos.z - g_aKitchen[nCnt].pos.z);

			mathBox = sqrtf(mathWidth * mathWidth + mathHeight * mathHeight);

			if (mathBox <= s_mathMIN)
			{
				s_mathMIN = (int)mathBox;
				SelectKitchen = nCnt;
			}
		}
	}

	if (s_mathMIN <= 10)
	{
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMaxKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMaxKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));

		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMinKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMinKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));

		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z), D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMaxKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMaxKitchen.x, g_aKitchen[SelectKitchen].vtxMinKitchen.y, g_aKitchen[SelectKitchen].vtxMaxKitchen.z));
		SetObjectLine(g_aKitchen[SelectKitchen].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), g_aKitchen[SelectKitchen].vtxMinKitchen, D3DXVECTOR3(g_aKitchen[SelectKitchen].vtxMinKitchen.x, g_aKitchen[SelectKitchen].vtxMaxKitchen.y, g_aKitchen[SelectKitchen].vtxMinKitchen.z));
	}
}
//=========================================
//��������ƃv���C���[�̋����̎擾
//=========================================
int GetKitchenDistance()
{
	return s_mathMIN;
}

//=========================================
//�ǂ̃L�b�`������ԋ߂����̏��̎擾
//=========================================
int GetSelectKitchen()
{
	return SelectKitchen;
}