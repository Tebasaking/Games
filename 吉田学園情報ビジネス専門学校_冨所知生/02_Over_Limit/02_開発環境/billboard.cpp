//=========================================
//
//	�r���{�[�h�̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "billboard.h"
#include "input.h"
#include "camera.h"
#include "wall.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBillboard = { NULL };				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Billboard g_aBillboard[MAX_BILLBOARD];							//�r���{�[�h�̍\����

//=====================================================
//�r���{�[�h�̏�����
//=====================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,															//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png",
		&g_pTextureBillboard);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_aBillboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̏����ݒ�
		g_aBillboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
		g_aBillboard[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�F�̏����ݒ�
		g_aBillboard[nCnt].bUse = false;										//�g�p���Ă��邩���Ă��Ȃ���
		g_aBillboard[nCnt].size = 0.0f;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_SIZE, BILLBOARD_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+BILLBOARD_SIZE, BILLBOARD_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_SIZE, -BILLBOARD_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+BILLBOARD_SIZE, -BILLBOARD_SIZE, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=========================================
//�r���{�[�h�̔j��
//=========================================
void UninitBillboard(void)
{
	//���b�V���̔j��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//�}�e���A���̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=========================================
//�r���{�[�h�̍X�V����
//=========================================
void UpdateBillboard(void)
{

}

//=========================================
//�r���{�[�h�̕`�揈��
//=========================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 132);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_aBillboard[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_aBillboard[nCnt].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCnt].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCnt].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCnt].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCnt].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCnt].pos.x, g_aBillboard[nCnt].pos.y, g_aBillboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCnt].mtxWorld, &g_aBillboard[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCnt].mtxWorld);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��00
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
//�r���{�[�h�̏��̎擾
//=========================================
Billboard* GetBillboard()
{
	return g_aBillboard;
}

//=========================================
//�r���{�[�h�̐ݒu����
//=========================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	int nCntBillboard;

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;
			g_aBillboard[nCntBillboard].rot = rot;
			g_aBillboard[nCntBillboard].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}