//========================================================
//�G�t�F�N�g�̏���
//========================================================
#include "effect.h"
#include "model.h"

//�}�N����`
#define MAX_EFFECT		(4096)	//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//��]
	D3DXCOLOR col;						//�F
	float fRadius;						//���a
	int nLife;							//����
	bool bUse;							//�g�p���Ă��邩�ǂ����̔���
	D3DXMATRIX  mtxWorld;				//���[���h�}�g���b�N�X
}Effect;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��

//============================
//�G�t�F�N�g�̏���������
//============================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureEffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);					//�E���ɍ��W���w��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//===========================
//�G�t�F�N�g�̏I������
//===========================
void UninitEffect(void)
{
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//���_�o�b�t�@��j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//===========================
//�G�t�F�N�g�̍X�V����
//===========================
void UpdateEffect(void)
{
	int nCntEffect;

	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius--;

			//�������s������
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//===========================
//�G�t�F�N�g�̕`�揈��
//===========================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

	//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);								//�e�N�X�`���̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); pDevice->SetTexture(0, g_pTextureEffect);

	////���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			
			//�J�����̋t�s���ݒ�
			g_aEffect[nCnt].mtxWorld._11 = mtxView._11;
			g_aEffect[nCnt].mtxWorld._12 = mtxView._21;
			g_aEffect[nCnt].mtxWorld._13 = mtxView._31;
			g_aEffect[nCnt].mtxWorld._21 = mtxView._12;
			g_aEffect[nCnt].mtxWorld._22 = mtxView._22;
			g_aEffect[nCnt].mtxWorld._23 = mtxView._32;
			g_aEffect[nCnt].mtxWorld._31 = mtxView._13;
			g_aEffect[nCnt].mtxWorld._32 = mtxView._23;
			g_aEffect[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCnt].pos.x, g_aEffect[nCnt].pos.y, g_aEffect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCnt].mtxWorld, &g_aEffect[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCnt].mtxWorld);

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

	//���C�g��L��������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�f�o�C�X�ݒ�̏�����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//===========================
//�G�t�F�N�g�̐ݒ菈��
//===========================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}