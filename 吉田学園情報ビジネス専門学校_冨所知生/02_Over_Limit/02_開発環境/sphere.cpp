//=========================================
//
//	���b�V���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "sphere.h"
#include "wall.h"
#include "model.h"
#include "wall.h"

//================================================================
//�O���[�o���ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 g_pTextureSphereField = NULL;				//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphereField = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffSphereField = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posSphereField;									//�ʒu
D3DXVECTOR3 g_rotSphereField;									//����
D3DXMATRIX g_mtxWorldSphere;									//���[���h�}�g���b�N�X

#define SPHERE_VERTEX_NUM ((SPHERE_X_BLOCK + 1) * (SPHERE_Z_BLOCK + 1))
#define SPHERE_INDEX_NUM  (((SPHERE_X_BLOCK + 1) * 2) * ( SPHERE_Z_BLOCK  * (SPHERE_Z_BLOCK - 1)) * SPHERE_Z_BLOCK * 2)
#define SPHERE_PRIMITIVE_NUM (SPHERE_X_BLOCK * SPHERE_Z_BLOCK * 2 + (4 * (SPHERE_Z_BLOCK  - 1)))

int sLineVtx = (SPHERE_X_BLOCK + 1);
static float sRadius = 10.0f;
//================================================================
//���b�V���̏�����
//================================================================
void InitSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_VERTEX_NUM,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphereField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * SPHERE_INDEX_NUM,			//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,													//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphereField,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/aiueo.jpg",
		&g_pTextureSphereField);

	VERTEX_3D* pVtx = NULL;			//���_���̎擾

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSphereField->Lock(0, 0, (void**)&pVtx, 0);

	//float fSphere = 0.0f;
	float RotZ = 0.0f;
	float Radius = 0.0f;
	//float Rot = ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK);

	for (int nCntZ = 0; nCntZ <= SPHERE_Z_BLOCK; nCntZ++)
	{
		RotZ = (D3DX_PI / SPHERE_Z_BLOCK) * nCntZ;
		Radius = sinf(RotZ) * 10.0f;

		for (int nCntX = 0; nCntX <= SPHERE_X_BLOCK; nCntX++)
		{
			//���_���W�̐ݒ�i���[���h���W�ł͂Ȃ����[�J�����W���w�肷��j
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].pos = D3DXVECTOR3
			(sinf(nCntX * ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK)) * Radius,				//x
			10.0f + cosf(RotZ) * 10.0f,													//y
			-cosf(nCntX  * ((D3DX_PI * 2.0f) / SPHERE_X_BLOCK)) * Radius);				//z

			//�e���_�̖@���̐ݒ�
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor = pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].pos;

			//�@���̐��K��
			D3DXVec3Normalize(&pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor, &pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].nor);

			//���_�J���[�̐ݒ�
			pVtx[nCntX + (SPHERE_X_BLOCK + 1) * nCntZ].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̐ݒ�
			pVtx[(nCntX + (SPHERE_X_BLOCK + 1) * nCntZ)].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSphereField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffSphereField->Lock(0, 0, (void**)&pIdx, 0);

	//�c�̒��_�̐�
	for (int nCntZ = 0; nCntZ < SPHERE_Z_BLOCK; nCntZ++)
	{
		//�C���f�b�N�X
		int nLineTop = nCntZ * (sLineVtx * 2 + 2);

		//���̒��_�̐�
		for (int nCntX = 0; nCntX < sLineVtx; nCntX++)
		{//��̒i�̏���
			pIdx[(nCntX * 2 + 1) + nLineTop] = (WORD)(nCntX + sLineVtx * nCntZ);

			//���̒i�̏���
			pIdx[nCntX * 2 + nLineTop] = (WORD)(pIdx[(nCntX * 2 + 1) + nLineTop] + sLineVtx);
		}

		//�k�ރ|���S����O��Ɠ���ɂ��鏈��
		if (nCntZ < SPHERE_Z_BLOCK)
		{
			pIdx[(sLineVtx * 2) + nLineTop] = (WORD)(SPHERE_X_BLOCK + (sLineVtx)* nCntZ);
			pIdx[(sLineVtx * 2) + nLineTop + 1] = (WORD)(2 * (sLineVtx)+(sLineVtx)* nCntZ);
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffSphereField->Unlock();
}
//================================================================
//���b�V���̔j��
//================================================================
void UninitSphere(void)
{
	//���b�V���t�B�[���h�̃e�N�X�`��
	if (g_pTextureSphereField != NULL)
	{
		g_pTextureSphereField->Release();
		g_pTextureSphereField = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSphereField != NULL)
	{
		g_pIdxBuffSphereField->Release();
		g_pIdxBuffSphereField = NULL;
	}
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffSphereField != NULL)
	{
		g_pVtxBuffSphereField->Release();
		g_pVtxBuffSphereField = NULL;
	}
}
//================================================================
//���b�V���̍X�V
//================================================================
void UpdateSphere(void)
{
}

//================================================================
//���b�V���̕`��
//================================================================
void DrawSphere(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldSphere);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotSphereField.y, g_rotSphereField.x, g_rotSphereField.z);

	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posSphereField.x, g_posSphereField.y, g_posSphereField.z);
	D3DXMatrixMultiply(&g_mtxWorldSphere, &g_mtxWorldSphere, &mtxTrans);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSphereField);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSphere);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSphereField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffSphereField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���b�V���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SPHERE_VERTEX_NUM, 0, SPHERE_PRIMITIVE_NUM);

	//���C�g��L��������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}