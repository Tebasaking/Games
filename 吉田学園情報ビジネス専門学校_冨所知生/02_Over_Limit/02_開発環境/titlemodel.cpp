//=========================================
//
//	���f���̓��o�͏���
//	Author : �y���m��
//
//=========================================
#include "main.h"
#include "titlemodel.h"

//�O���[�o���ϐ��錾
TITLEMODEL g_aTitleModel[MAX_TITLEMODEL];
static int s_nIdxShadow;							//�e�̔���
static int s_nIdxTitleModel;
static int s_TitleModelDistance;							//�v���C���[�ƃ��f���̋���
static int s_mathWidth;
static int s_mathHeight;
static int s_mathMIN = 1000000;
static int s_mathBox;
static int s_Submission;							//��o����Ƃ��Ƃ̋���
static int s_nCount;
//=====================================================
//���f���̏�����
//=====================================================
void InitTitleModel(void)
{
	for (int nCntTitleModel = 0; nCntTitleModel < MAX_TITLEMODEL; nCntTitleModel++)
	{
		g_aTitleModel[nCntTitleModel].bUse = false;										//�g�p���Ă��Ȃ�
		g_aTitleModel[nCntTitleModel].cook = false;
		g_aTitleModel[nCntTitleModel].bIsLanding = false;
		g_aTitleModel[nCntTitleModel].nNumMatTitleModel = 0;									//�}�e���A���̐��̏�����
		g_aTitleModel[nCntTitleModel].CookCount = 0;
		g_aTitleModel[nCntTitleModel].Type = 0;
		g_aTitleModel[nCntTitleModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̏����ݒ�
		g_aTitleModel[nCntTitleModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
		g_aTitleModel[nCntTitleModel].rotDestTitleModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̌����̏����ݒ�
		g_aTitleModel[nCntTitleModel].vtxMaxTitleModel = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		g_aTitleModel[nCntTitleModel].vtxMaxTitleModel = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	}
	s_nIdxTitleModel = 0;
	s_nIdxShadow = 0;
	s_mathWidth = 0;
	s_mathHeight = 0;
	s_mathMIN = 1000000;
	s_mathBox = 0;
	s_TitleModelDistance = 0;
}

//=========================================
//���f���̔j��
//=========================================
void UninitTitleModel(void)
{
	for (int nCntTitleModel = 0; nCntTitleModel < MAX_TITLEMODEL; nCntTitleModel++)
	{
		for (int i = 0; i < (int)g_aTitleModel[nCntTitleModel].nNumMatTitleModel; i++)
		{
			if (g_aTitleModel[nCntTitleModel].pTexture[i] != NULL)
			{// �e�N�X�`���̉��
				g_aTitleModel[nCntTitleModel].pTexture[i]->Release();
				g_aTitleModel[nCntTitleModel].pTexture[i] = NULL;
			}
		}
		//���b�V���̔j��
		if (g_aTitleModel[nCntTitleModel].pMeshTitleModel != NULL)
		{
			g_aTitleModel[nCntTitleModel].pMeshTitleModel->Release();
			g_aTitleModel[nCntTitleModel].pMeshTitleModel = NULL;
		}
		//�}�e���A���̔j��
		if (g_aTitleModel[nCntTitleModel].pBuffMatTitleModel != NULL)
		{
			g_aTitleModel[nCntTitleModel].pBuffMatTitleModel->Release();
			g_aTitleModel[nCntTitleModel].pBuffMatTitleModel = NULL;
		}
	}
}

//=========================================
//���f���̍X�V����
//=========================================
void UpdateTitleModel(void)
{
	//��𓮂���
	g_aTitleModel[1].rot.y += 0.003f;
}
//=========================================
//���f���̕`�揈��
//=========================================
void DrawTitleModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntTitleModel = 0; nCntTitleModel < MAX_TITLEMODEL; nCntTitleModel++)
	{
		if (g_aTitleModel[nCntTitleModel].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aTitleModel[nCntTitleModel].mtxWorldTitleModel);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aTitleModel[nCntTitleModel].rot.y, g_aTitleModel[nCntTitleModel].rot.x, g_aTitleModel[nCntTitleModel].rot.z);

			D3DXMatrixMultiply(&g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aTitleModel[nCntTitleModel].pos.x, g_aTitleModel[nCntTitleModel].pos.y, g_aTitleModel[nCntTitleModel].pos.z);
			D3DXMatrixMultiply(&g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &g_aTitleModel[nCntTitleModel].mtxWorldTitleModel, &mtxTrans);

			//���[���h�}�g���b�N�X���X�V
			pDevice->SetTransform(D3DTS_WORLD, &g_aTitleModel[nCntTitleModel].mtxWorldTitleModel);

			//���݂̃}�e���A����ێ�(�ޔ�)
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�̃|�C���^���擾����
			pMat = (D3DXMATERIAL*)g_aTitleModel[nCntTitleModel].pBuffMatTitleModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aTitleModel[nCntTitleModel].nNumMatTitleModel; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aTitleModel[nCntTitleModel].pTexture[nCntMat]);

				//���f���p�[�c�̕`��
				g_aTitleModel[nCntTitleModel].pMeshTitleModel->DrawSubset(nCntMat);
			}
			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================
//���f���̏��̎擾
//=========================================
TITLEMODEL* GetTitleModel()
{
	return &g_aTitleModel[0];
}

//=========================================
//���f���̐ݒu
//=========================================
void SetTitleModel(D3DXVECTOR3 pos, char TITLEMODEL_NAME[128], int nCnt, int nType)
{
	if (g_aTitleModel[nCnt].bUse == false)
	{
		g_aTitleModel[nCnt].pos = pos;
		g_aTitleModel[nCnt].bUse = true;
		g_aTitleModel[nCnt].Type = nType;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(TITLEMODEL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aTitleModel[nCnt].pBuffMatTitleModel,
			NULL,
			&g_aTitleModel[nCnt].nNumMatTitleModel,
			&g_aTitleModel[nCnt].pMeshTitleModel);

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_aTitleModel[nCnt].pBuffMatTitleModel->GetBufferPointer();

		// �e���b�V���̃}�e���A�������擾����
		for (int i = 0; i < (int)g_aTitleModel[nCnt].nNumMatTitleModel; i++)
		{
			g_aTitleModel[nCnt].pTexture[i] = NULL;

			if (pMat[i].pTextureFilename != NULL)
			{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
				D3DXCreateTextureFromFileA(pDevice,
					pMat[i].pTextureFilename,
					&g_aTitleModel[nCnt].pTexture[i]);
			}
		}

		int nNumVtx;			//���_��
		DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_aTitleModel[nCnt].pMeshTitleModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aTitleModel[nCnt].pMeshTitleModel->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aTitleModel[nCnt].pMeshTitleModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W���擾
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l/�ő�l���擾
			g_aTitleModel[nCnt].vtxMaxTitleModel.x = VertexMAXChange(vtx.x, g_aTitleModel[nCnt].vtxMaxTitleModel.x);
			g_aTitleModel[nCnt].vtxMaxTitleModel.y = VertexMAXChange(vtx.y, g_aTitleModel[nCnt].vtxMaxTitleModel.y);
			g_aTitleModel[nCnt].vtxMaxTitleModel.z = VertexMAXChange(vtx.z, g_aTitleModel[nCnt].vtxMaxTitleModel.z);

			g_aTitleModel[nCnt].vtxMinTitleModel.x = VertexMINChange(vtx.x, g_aTitleModel[nCnt].vtxMinTitleModel.x);
			g_aTitleModel[nCnt].vtxMinTitleModel.y = VertexMINChange(vtx.y, g_aTitleModel[nCnt].vtxMinTitleModel.y);
			g_aTitleModel[nCnt].vtxMinTitleModel.z = VertexMINChange(vtx.z, g_aTitleModel[nCnt].vtxMinTitleModel.z);

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}
		//���_�o�b�t�@�̃A�����b�N
		g_aTitleModel[nCnt].pMeshTitleModel->UnlockVertexBuffer();
	}
}