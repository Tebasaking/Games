//=========================================
//
//	�L�b�`���^�C�}�[�̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "kitchentimer.h"
#include "input.h"
#include "camera.h"
#include "kitchen.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureKTimer[MAX_KITCHENTIMER] = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKTimer = NULL;			//���_�o�b�t�@�ւ̃|�C���^
KTIMER g_aKTimer[MAX_KITCHENTIMER];							//�L�b�`���^�C�}�[�̍\����

//=====================================================
//�L�b�`���^�C�}�[�̏�����
//=====================================================
void InitKTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_KITCHENTIMER,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffKTimer,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/timer_contain.png",
		&g_pTextureKTimer[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/kitchentimer000.png",
		&g_pTextureKTimer[1]);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
	{
		g_aKTimer[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̏����ݒ�
		g_aKTimer[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
		g_aKTimer[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�F�̏����ݒ�
		g_aKTimer[nCnt].bUse = false;										//�g�p���Ă��邩���Ă��Ȃ���

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-KTIMER_WIDTH, KTIMER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+KTIMER_WIDTH, KTIMER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-KTIMER_WIDTH, -KTIMER_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+KTIMER_WIDTH, -KTIMER_HEIGHT, 0.0f);

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
	g_pVtxBuffKTimer->Unlock();
}

//=========================================
//�L�b�`���^�C�}�[�̔j��
//=========================================
void UninitKTimer(void)
{
	//���b�V���̔j��
	for (int i = 0; i < MAX_KITCHENTIMER; i++)
	{
		if (g_pTextureKTimer[i] != NULL)
		{					
			g_pTextureKTimer[i]->Release();
			g_pTextureKTimer[i] = NULL;
		}
	}
	//�}�e���A���̔j��
	if (g_pVtxBuffKTimer != NULL)
	{
		g_pVtxBuffKTimer->Release();
		g_pVtxBuffKTimer = NULL;
	}
}

//=========================================
//�L�b�`���^�C�}�[�̍X�V����
//=========================================
void UpdateKTimer(void)
{
	KITCHEN *pKitchen = GetKitchen();
	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	pKitchen += GetSelectKitchen();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
	{
		if (g_aKTimer[nCnt].bUse)
		{
			pVtx[4].pos = D3DXVECTOR3(-KTIMER_WIDTH, KTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(-KTIMER_WIDTH + (pKitchen->CookCount / 24), KTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-KTIMER_WIDTH, -KTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(-KTIMER_WIDTH + (pKitchen->CookCount / 24), -KTIMER_HEIGHT / 2, 0.0f);

			pVtx += 4 ;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffKTimer->Unlock();
}

//=========================================
//�L�b�`���^�C�}�[�̕`�揈��
//=========================================
void DrawKTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKTimer, 0, sizeof(VERTEX_3D));

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 132);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_KITCHENTIMER; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureKTimer[g_aKTimer[nCnt].state]);
		
		if (g_aKTimer[nCnt].bUse)
		{//�L�b�`���̏��̎擾
			KITCHEN *pKitchen = GetKitchen();

			int SelectKitchen = GetSelectKitchen();

			//��ԋ߂��L�b�`���̔ԍ��̓���
			pKitchen += SelectKitchen;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aKTimer[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 5.0f, 5.0f);
			D3DXMatrixMultiply(&g_aKTimer[nCnt].mtxWorld, &mtxTrans, &pKitchen->mtxWorldKitchen);

			//�J�����̋t�s���ݒ�
			g_aKTimer[nCnt].mtxWorld._11 = mtxView._11;
			g_aKTimer[nCnt].mtxWorld._12 = mtxView._21;
			g_aKTimer[nCnt].mtxWorld._13 = mtxView._31;
			g_aKTimer[nCnt].mtxWorld._31 = mtxView._13;
			g_aKTimer[nCnt].mtxWorld._32 = mtxView._23;
			g_aKTimer[nCnt].mtxWorld._33 = mtxView._33;

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aKTimer[nCnt].mtxWorld);
				
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
void SetKTimer(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntKTimer;

	for (nCntKTimer = 0; nCntKTimer < MAX_KITCHENTIMER; nCntKTimer++)
	{
		if (g_aKTimer[nCntKTimer].bUse == false)
		{
			g_aKTimer[nCntKTimer].pos = pos;
			g_aKTimer[nCntKTimer].bUse = true;

			break;
		}
		pVtx += 4 * nCntKTimer;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKTimer->Unlock();

	//�L�b�`���^�C�}�[�̃o�[��ݒu����
	SetKTimerBar(pos);
}
//=========================================
//�L�b�`���^�C�}�[�̃o�[�̐ݒu����
//=========================================
void SetKTimerBar(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffKTimer->Lock(0, 0, (void**)&pVtx, 0);

	int nCntKTimer;

	for (nCntKTimer = 0; nCntKTimer < MAX_KITCHENTIMER; nCntKTimer++)
	{
		if (g_aKTimer[nCntKTimer].bUse == false)
		{
			g_aKTimer[nCntKTimer].pos = pos;
			g_aKTimer[nCntKTimer].bUse = true;
			g_aKTimer[nCntKTimer].state = KTIMER_BAR;

			//���_���W�̐ݒ�
			pVtx[4].pos = D3DXVECTOR3(-KTIMER_WIDTH / 2, KTIMER_HEIGHT / 2, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(+KTIMER_WIDTH / 2, KTIMER_HEIGHT / 2, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-KTIMER_WIDTH / 2, -KTIMER_HEIGHT / 2, 0.0f);
			pVtx[7].pos = D3DXVECTOR3(+KTIMER_WIDTH / 2, -KTIMER_HEIGHT / 2, 0.0f);

			break;
		}
		pVtx += 4 * nCntKTimer;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKTimer->Unlock();
}
//=========================================
//�L�b�`���^�C�}�[�̏����擾
//=========================================
KTIMER *GetKTimer()
{
	return g_aKTimer;
}