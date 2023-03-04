//=========================================
//
//	��̒������Ԃ̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "cuttingtimer.h"
#include "input.h"
#include "camera.h"
#include "item.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureCTimer[MAX_CUTTINGTIMER] = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCTimer = NULL;			//���_�o�b�t�@�ւ̃|�C���^
CTIMER g_aCTimer[MAX_CUTTINGTIMER];							//�L�b�`���^�C�}�[�̍\����

//=====================================================
//�L�b�`���^�C�}�[�̏�����
//=====================================================
void InitCTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_CUTTINGTIMER,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCTimer,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/timer_contain.png",
		&g_pTextureCTimer[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/kitchentimer000.png",
		&g_pTextureCTimer[1]);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_CUTTINGTIMER; nCnt++)
	{
		// �J�b�g�^�C�}�[�̏��̏�����
		memset(&g_aCTimer[nCnt], 0, sizeof(g_aCTimer[nCnt]));

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-CTIMER_WIDTH, CTIMER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+CTIMER_WIDTH, CTIMER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-CTIMER_WIDTH, -CTIMER_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+CTIMER_WIDTH, -CTIMER_HEIGHT, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_color�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCTimer->Unlock();
}

//=========================================
//�L�b�`���^�C�}�[�̔j��
//=========================================
void UninitCTimer(void)
{
	//���b�V���̔j��
	for (int i = 0; i < MAX_CUTTINGTIMER; i++)
	{
		if (g_pTextureCTimer[i] != NULL)
		{
			g_pTextureCTimer[i]->Release();
			g_pTextureCTimer[i] = NULL;
		}
	}
	//�}�e���A���̔j��
	if (g_pVtxBuffCTimer != NULL)
	{
		g_pVtxBuffCTimer->Release();
		g_pVtxBuffCTimer = NULL;
	}
}

//=========================================
//�L�b�`���^�C�}�[�̍X�V����
//=========================================
void UpdateCTimer(void)
{
	ITEM *pItem = GetItem();
	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	pItem += GetSelectItem();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_CUTTINGTIMER; nCnt++)
	{
		if (g_aCTimer[nCnt].bUse)
		{
			pVtx[4].pos = D3DXVECTOR3(-CTIMER_WIDTH, CTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(-CTIMER_WIDTH + (pItem->CuttingTime / 12), CTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-CTIMER_WIDTH, -CTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(-CTIMER_WIDTH + (pItem->CuttingTime / 12), -CTIMER_HEIGHT / 2, 0.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCTimer->Unlock();
}

//=========================================
//�L�b�`���^�C�}�[�̕`�揈��
//=========================================
void DrawCTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCTimer, 0, sizeof(VERTEX_3D));

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 132);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_CUTTINGTIMER; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureCTimer[g_aCTimer[nCnt].state]);

		if (g_aCTimer[nCnt].bUse)
		{//�L�b�`���̏��̎擾
			ITEM *pItem = GetItem();

			int SelectItem = GetSelectItem();

			//��ԋ߂��L�b�`���̔ԍ��̓���
			pItem += SelectItem;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aCTimer[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, 5.0f);
			D3DXMatrixMultiply(&g_aCTimer[nCnt].mtxWorld, &mtxTrans, &pItem->mtxWorldItem);

			//�J�����̋t�s���ݒ�
			g_aCTimer[nCnt].mtxWorld._11 = mtxView._11;
			g_aCTimer[nCnt].mtxWorld._12 = mtxView._21;
			g_aCTimer[nCnt].mtxWorld._13 = mtxView._31;
			g_aCTimer[nCnt].mtxWorld._31 = mtxView._13;
			g_aCTimer[nCnt].mtxWorld._32 = mtxView._23;
			g_aCTimer[nCnt].mtxWorld._33 = mtxView._33;

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aCTimer[nCnt].mtxWorld);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
				nCnt * 4,										//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);												//�v���~�e�B�u(�|���S��)��
		}
	}
	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	//���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�f�o�C�X�ݒ�̏�����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=========================================
//�L�b�`���^�C�}�[�̐ݒu����
//=========================================
void SetCTimer(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntCTimer;

	for (nCntCTimer = 0; nCntCTimer < MAX_CUTTINGTIMER; nCntCTimer++)
	{
		if (g_aCTimer[nCntCTimer].bUse == false)
		{
			g_aCTimer[nCntCTimer].pos = pos;
			g_aCTimer[nCntCTimer].bUse = true;

			break;
		}
		pVtx += 4 * nCntCTimer;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCTimer->Unlock();

	//�L�b�`���^�C�}�[�̃o�[��ݒu����
	SetCTimerBar(pos);
}
//=========================================
//�L�b�`���^�C�}�[�̃o�[�̐ݒu����
//=========================================
void SetCTimerBar(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntCTimer;

	for (nCntCTimer = 0; nCntCTimer < MAX_CUTTINGTIMER; nCntCTimer++)
	{
		if (g_aCTimer[nCntCTimer].bUse == false)
		{
			g_aCTimer[nCntCTimer].pos = pos;
			g_aCTimer[nCntCTimer].bUse = true;
			g_aCTimer[nCntCTimer].state = CTIMER_BAR;

			//���_���W�̐ݒ�
			pVtx[4].pos = D3DXVECTOR3(-CTIMER_WIDTH / 2, CTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(+CTIMER_WIDTH / 2, CTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-CTIMER_WIDTH / 2, -CTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(+CTIMER_WIDTH / 2, -CTIMER_HEIGHT / 2, 0.0f);

			break;
		}
		pVtx += 4 * nCntCTimer;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCTimer->Unlock();
}
//=========================================
//�L�b�`���^�C�}�[�̏����擾
//=========================================
CTIMER *GetCTimer()
{
	return g_aCTimer;
}