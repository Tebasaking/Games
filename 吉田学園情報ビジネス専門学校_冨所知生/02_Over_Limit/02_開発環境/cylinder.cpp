//=========================================
//
//	�~���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "cylinder.h"
#include "wall.h"
#include "model.h"

//================================================================
//�O���[�o���ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 g_pTextureCylinderField = NULL;				//�~���̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCylinderField = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffCylinderField = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posCylinderField;									//�ʒu
D3DXVECTOR3 g_rotCylinderField;									//����
D3DXMATRIX g_mtxWorldCylinder;									//���[���h�}�g���b�N�X

#define CYLINDER_X_BLOCK (8)
#define CYLINDER_Z_BLOCK (2)
#define CYLINDER_SIZE (10.0f)

#define CYLINDER_VERTEX_NUM ((CYLINDER_X_BLOCK + 1) * (CYLINDER_Z_BLOCK + 1))
#define CYLINDER_INDEX_NUM  (((CYLINDER_X_BLOCK + 1) * 2) * ( CYLINDER_Z_BLOCK  *(CYLINDER_Z_BLOCK - 1)) * CYLINDER_Z_BLOCK * 2)
#define CYLINDER_PRIMITIVE_NUM (CYLINDER_X_BLOCK * CYLINDER_Z_BLOCK * 2 + 4 * (CYLINDER_Z_BLOCK  - 1))

int cLineVtx = (CYLINDER_X_BLOCK + 1);
int fRadius = 10;
//================================================================
//�~���̏�����
//================================================================
void InitCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CYLINDER_VERTEX_NUM,		//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,										//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCylinderField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * CYLINDER_INDEX_NUM,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pIdxBuffCylinderField,
		NULL);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

									//���_�o�b�t�@�����b�N
	g_pVtxBuffCylinderField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= CYLINDER_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= CYLINDER_X_BLOCK; nCntX++)
		{
			//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
			pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
			(sinf(nCntX * ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK)) * fRadius,				//x
			0.0f + (nCntZ * 10.0f),														//y
			cosf(nCntX  * ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK)) * fRadius);			//z

			//�e���_�̖@���̐ݒ�
			pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//�@���̐��K��
			D3DXVec3Normalize(&pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].nor, &pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].nor);

			//���_�J���[�̐ݒ�
			pVtx[nCntX + (CYLINDER_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCylinderField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffCylinderField->Lock(0, 0, (void**)&pIdx, 0);

	//�c�̒��_�̐�
	for (int nCntZ = 0; nCntZ < CYLINDER_Z_BLOCK; nCntZ++)
	{
		//�C���f�b�N�X
		int nLineTop = nCntZ * (cLineVtx * 2 + 2);

		//���̒��_�̐�
		for (int nCntX = 0; nCntX < cLineVtx; nCntX++)
		{//��̒i�̏���
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + cLineVtx * nCntZ);

			//���̒i�̏���
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + cLineVtx);
		}

		//�k�ރ|���S����O��Ɠ���ɂ��鏈��
		if (nCntZ < CYLINDER_Z_BLOCK)
		{
			pIdx[(cLineVtx * 2) + nLineTop] = (WORD)(CYLINDER_X_BLOCK + (cLineVtx)* nCntZ);
			pIdx[(cLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (cLineVtx)+(cLineVtx)* nCntZ);
		}
	}
	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffCylinderField->Unlock();
}
//================================================================
//�~���̔j��
//================================================================
void UninitCylinder(void)
{
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffCylinderField != NULL)
	{
		g_pIdxBuffCylinderField->Release();
		g_pIdxBuffCylinderField = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffCylinderField != NULL)
	{
		g_pVtxBuffCylinderField->Release();
		g_pVtxBuffCylinderField = NULL;
	}
}
//================================================================
//�~���̍X�V
//================================================================
void UpdateCylinder(void)
{
}

//================================================================
//�~���̕`��
//================================================================
void DrawCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldCylinder);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotCylinderField.y, g_rotCylinderField.x, g_rotCylinderField.z);

	D3DXMatrixMultiply(&g_mtxWorldCylinder, &g_mtxWorldCylinder, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posCylinderField.x, g_posCylinderField.y, g_posCylinderField.z);
	D3DXMatrixMultiply(&g_mtxWorldCylinder, &g_mtxWorldCylinder, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldCylinder);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCylinderField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffCylinderField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �~���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CYLINDER_VERTEX_NUM, 0, CYLINDER_PRIMITIVE_NUM);
}