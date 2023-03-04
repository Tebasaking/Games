//=========================================
//
//	�|���S���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "polygon.h"
#include "wall.h"
#include "model.h"

//================================================================
//�O���[�o���ϐ��錾
//================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPolygon;							//�ʒu
D3DXVECTOR3 g_rotPolygon;							//����
D3DXMATRIX g_mtxWorldPolygon;						//���[���h�}�g���b�N�X

//================================================================
//�|���S���̏�����
//================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,										//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
	pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//���_color�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPolygon->Unlock();
}
//================================================================
//�|���S���̔j��
//================================================================
void UninitPolygon(void)
{
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
//================================================================
//�|���S���̍X�V
//================================================================
void UpdatePolygon(void)
{
	//�|���S���̒��ɍS�����鏈��
	MODEL *pModel = GetModel();

	if (pModel->pos.x >= g_posPolygon.x + POLYGON_SIZE)
	{
		pModel->pos.x = g_posPolygon.x + POLYGON_SIZE;
	}

	else if (pModel->pos.x <= g_posPolygon.x - POLYGON_SIZE)
	{
		pModel->pos.x = g_posPolygon.x - POLYGON_SIZE;
	}

	if (pModel->pos.z >= g_posPolygon.z + POLYGON_SIZE)
	{
		pModel->pos.z = g_posPolygon.z + POLYGON_SIZE;
	}

	else if (pModel->pos.z <= g_posPolygon.z - POLYGON_SIZE)
	{
		pModel->pos.z = g_posPolygon.z - POLYGON_SIZE;
	}
}

//================================================================
//�|���S���̕`��
//================================================================
void DrawPolygon(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);

	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}