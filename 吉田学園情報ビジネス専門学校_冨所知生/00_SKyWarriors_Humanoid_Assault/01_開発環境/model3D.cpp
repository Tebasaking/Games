//=============================================================================
//
// 3D���f���N���X(model3D.h)
// Author : �y���m��
// �T�v : 3D���f���������s��
//
//=============================================================================
#include <stdio.h>
#include <assert.h>

#include "model3D.h"
#include "render.h"
#include "application.h"
#include "game.h"
#include "texture3D.h"
#include "light.h"
#include "camera.h"
#include "camera_player.h"
#include "camera_radar.h"
#include "camera_title.h"

//--------------------------------------------------------------------
// �ÓI�����o�ϐ���`
//--------------------------------------------------------------------
std::vector<CModel3D::MODEL_MATERIAL> CModel3D::m_material;		// �}�e���A�����
int CModel3D::m_nMaxModel = 0;									// ���f����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel3D::CModel3D()
{
	m_pParent = nullptr;										// �e���f���̏��
	m_mtxWorld = {};											// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �傫��
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				// �J���[
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);		// �N�H�[�^�j�I��
	m_nModelID = -1;											// ���f��ID
	m_bColor = false;											// �J���[���g�p����
	m_bShadow = true;											// �e�̎g�p��
	m_bLighting = true;											// ���C�g�̎g�p��

	pEffect = NULL;
	m_hmWVP = NULL;
	m_hmWIT = NULL;
	m_hvLightDir = NULL;
	m_hvCol = NULL;
	m_hvEyePos = NULL;
	m_hTechnique = NULL;
	m_hTexture = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel3D::~CModel3D()
{

}
//=============================================================================
// �C���X�^���X����
//=============================================================================
CModel3D * CModel3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CModel3D *pModel3D = nullptr;

	// �������̉��
	pModel3D = new CModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pModel3D != nullptr);

	// ���l�̏�����
	pModel3D->Init();

	// �C���X�^���X��Ԃ�
	return pModel3D;
}

//=============================================================================
// ���f�����̏�����
//=============================================================================
void CModel3D::InitModel()
{
	// �����_���[�̃Q�b�g
	CRender *pRender = CApplication::GetRender();

	// �e�N�X�`���|�C���^�̎擾
	CTexture3D *pTexture = CApplication::GetTexture3D();

	// �e�N�X�`�����̎擾
	CTexture3D::TEXTURE *pTextureData = pTexture->GetTextureData();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	// �t�@�C���ǂݍ���
	LoadModel("Data/FILE/data.txt");

	// �e�N�X�`���̎g�p���̃Q�b�g
	int nMaxTex = pTexture->GetMaxTexture();

	for (int nCntModel = 0; nCntModel < m_nMaxModel; nCntModel++)
	{// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&m_material[nCntModel].aFileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_material[nCntModel].pBuffer,
			NULL,
			&m_material[nCntModel].nNumMat,
			&m_material[nCntModel].pMesh);

		// �}�e���A���̃e�N�X�`�����̃������m��
		m_material[nCntModel].pNumTex.resize(m_material[nCntModel].nNumMat);

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_material[nCntModel].pBuffer->GetBufferPointer();

		memset(&m_material[nCntModel].pTexture[0], 0,sizeof(LPDIRECT3DTEXTURE9) * MAX_MATERIAL_TEXTURE_NUM);

		// �e���b�V���̃}�e���A�������擾���� 
		for (int nCntMat = 0; nCntMat < (int)m_material[nCntModel].nNumMat; nCntMat++)
		{
			// �}�e���A���̃e�N�X�`�����̏�����
			m_material[nCntModel].pNumTex[nCntMat] = -1;

			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pRender->GetDevice(),
					pMat[nCntMat].pTextureFilename,
					&m_material[nCntModel].pTexture[nCntMat]);
			}
		}

		// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
		int		nNumVtx;	// ���_��
		DWORD	sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE	*pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

		// ���_���̎擾
		nNumVtx = m_material[nCntModel].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF = D3DXGetFVFVertexSize(m_material[nCntModel].pMesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		m_material[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		// �ł��傫�Ȓ��_
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// ���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x < vtxMin.x)
			{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
				vtxMin.x = vtx.x;
			}
			if (vtx.y < vtxMin.y)
			{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
				vtxMin.y = vtx.y;
			}
			if (vtx.z < vtxMin.z)
			{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
				vtxMin.z = vtx.z;
			}

			if (vtx.x > vtxMax.x)
			{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
				vtxMax.x = vtx.x;
			}
			if (vtx.y > vtxMax.y)
			{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
				vtxMax.y = vtx.y;
			}
			if (vtx.z > vtxMax.z)
			{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
				vtxMax.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		// ���_�o�b�t�@�̃A�����b�N
		m_material[nCntModel].pMesh->UnlockVertexBuffer();

		// �傫���̐ݒ�
		m_material[nCntModel].size = vtxMax - vtxMin;
	}
}

//=============================================================================
// ���f�����̏I��
//=============================================================================
void CModel3D::UninitModel()
{
	for (int i = 0; i < (int)m_material.size(); i++)
	{
		if (m_material.at(i).pMesh != nullptr)
		{
			m_material.at(i).pMesh->Release();
			m_material.at(i).pMesh = nullptr;
		}

		if (m_material.at(i).pBuffer != nullptr)
		{
			m_material.at(i).pBuffer->Release();
			m_material.at(i).pBuffer = nullptr;
		}
	}

	m_material.clear();
}

//=============================================================================
// X�t�@�C���̓ǂݍ���
//=============================================================================
void CModel3D::LoadModel(const char *pFileName)
{
	// �ϐ��錾
	char aStr[128];
	int nCntModel = 0;

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(pFileName, "r");

	if (pFile != nullptr)
	{
		while (fscanf(pFile, "%s", &aStr[0]) != EOF)
		{// "EOF"��ǂݍ��ނ܂� 
			if (strncmp(&aStr[0], "#", 1) == 0)
			{// ���ǂݍ���
				fgets(&aStr[0], sizeof(aStr), pFile);
			}

			if (strstr(&aStr[0], "MAX_TYPE") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%d", &m_nMaxModel);
				m_material.resize(m_nMaxModel);
			}

			if (strstr(&aStr[0], "MODEL_FILENAME") != NULL)
			{
				fscanf(pFile, "%s", &aStr[0]);
				fscanf(pFile, "%s", &m_material[nCntModel].aFileName[0]);
				nCntModel++;
			}
		}
	}
	else
	{
		assert(false);
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModel3D::Init()
{
	// �����o�ϐ��̏�����
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �傫��
	m_nModelID = -1;										// ���f��ID

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �G�t�F�N�g�t�@�C���̎擾
	pEffect = CApplication::GetShader();

	m_hTechnique = pEffect->GetTechniqueByName("Diffuse");				//�G�t�F�N�g
	m_hTexture = pEffect->GetParameterByName(NULL, "Tex");				//�e�N�X�`��
	m_hmWVP = pEffect->GetParameterByName(NULL, "mWVP");				//���[�J��-�ˉe�ϊ��s��
	m_hmWIT = pEffect->GetParameterByName(NULL, "mWIT");				//���[�J��-���[���h�ϊ��s��
	m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");		//���C�g�̕���
	m_hvCol = pEffect->GetParameterByName(NULL, "vColor");				//���_�J���[
	m_hvEyePos = pEffect->GetParameterByName(NULL, "vEyePos");

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CModel3D::Uninit()
{

}

//=============================================================================
// �X�V
//=============================================================================
void CModel3D::Update()
{
	
}

//=============================================================================
// �`��
//=============================================================================
void CModel3D::Draw()
{
	if (m_nModelID >= 0
		&& m_nModelID < m_nMaxModel)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

		D3DMATRIX viewMatrix;
		D3DMATRIX projMatrix;

		pDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
		pDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);

		// �e�̃��[���h�}�g���b�N�X
		D3DXMATRIX mtxParent = {};

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

		// �N�H�[�^�j�I���̔��f
		D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);						// �N�I�[�^�j�I���ɂ��s���]
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

		if (m_pParent != nullptr)
		{	// �e�̃��[���h���W���擾
			mtxParent = m_pParent->GetMtxWorld();

			// �s��|���Z�֐�
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		pDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
		pDevice->SetTransform(D3DTS_PROJECTION, &projMatrix);

		// �}�e���A���`��
		DrawMaterial();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CModel3D::Draw(D3DXMATRIX mtxParent)
{
	if (m_nModelID >= 0
		&& m_nModelID < m_nMaxModel)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

		D3DMATRIX viewMatrix;
		D3DMATRIX projMatrix;

		pDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
		pDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);											// �s�񏉊����֐�

		// �T�C�Y�̔��f
		D3DXMatrixScaling(&mtxScaling, m_size.x, m_size.y, m_size.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);					// �s��|���Z�֐�

		// �N�H�[�^�j�I���̔��f
		D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);						// �N�I�[�^�j�I���ɂ��s���]
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// �s��|���Z�֐� 

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// �s��|���Z�֐�

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		//if (m_bShadow)
		//{// �e�̐���
		//	Shadow();
		//}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		pDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
		pDevice->SetTransform(D3DTS_PROJECTION, &projMatrix);

		// �}�e���A���`��
		DrawMaterial();
	}
}

//=============================================================================
// �}�e���A���`��
//=============================================================================
void CModel3D::DrawMaterial()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	CCamera *pCamera = nullptr;

	switch (CApplication::GetRender()->GetCheck())
	{
	case false:
		switch (CApplication::GetMode())
		{
		case CApplication::MODE_TITLE:
			pCamera = CApplication::GetTitleCamera();
			break;

		case CApplication::MODE_GAME:
			pCamera = CApplication::GetCamera();
			break;

		case CApplication::MODE_RESULT:
			pCamera = CApplication::GetTitleCamera();
			break;

		case CApplication::MODE_GAME_OVER:
			pCamera = CApplication::GetTitleCamera();
			break;

		case CApplication::MODE_TIME_OVER:
			pCamera = CApplication::GetTitleCamera();
			break;

		case CApplication::MODE_TUTORIAL:
			pCamera = CApplication::GetCamera();
			break;

		case CApplication::MODE_TUTORIAL_PIC:
			pCamera = CApplication::GetTitleCamera();
			break;
		}
		break;
	case true:
		pCamera = CApplication::GetRader();
		break;
	}

	D3DMATRIX viewMatrix = pCamera->GetView();
	D3DMATRIX projMatrix = pCamera->GetProjection();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	extern D3DLIGHT9 g_light;	// �J�������

	D3DXMATRIX m, mT, mR, mView, mProj;
	D3DXVECTOR4 v, light_pos;

	//==================================================================================
	if (pEffect != NULL)
	{
		// �e�N�X�`���|�C���^�̎擾
		CTexture3D *pTexture = CApplication::GetTexture3D();

		//-------------------------------------------------
		// �V�F�[�_�̐ݒ�
		//-------------------------------------------------
		pEffect->SetTechnique(m_hTechnique);
		pEffect->Begin(NULL, 0);
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		//pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

		D3DXMatrixTranslation(&m, 1.0f, 0.0f, 0.0f);

		D3DXMatrixRotationY(&mR, 0.0f);
		D3DXMatrixTranslation(&mT, 1.0f, 1.2f, 0.0f);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		// ���[�J��-�ˉe�ϊ��s��
		D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
		D3DXMatrixTranspose(&m, &m);
		pEffect->SetMatrix(m_hmWIT, &m);

		// ���[�J��-�ˉe�ϊ��s��
		m = m_mtxWorld * viewMatrix * projMatrix;
		pEffect->SetMatrix(m_hmWVP, &m);

		// ���C�g�̕���
		light_pos = D3DXVECTOR4(g_light.Direction.x, g_light.Direction.y, g_light.Direction.z, 0);

		D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
		D3DXVec4Transform(&v, &-light_pos, &m);

		D3DXVec3Normalize((D3DXVECTOR3 *)&v, (D3DXVECTOR3 *)&v);

		//�����̑傫��
		v.w = -0.8f;
		pEffect->SetVector(m_hvLightDir, &v);

		// ���_
		m = m_mtxWorld *viewMatrix;
		D3DXMatrixInverse(&m, NULL, &m);

		//����
		v = D3DXVECTOR4(0, 0, 0, 1);

		//�}�e���A���f�[�^�̃|�C���^���擾����
		pMat = (D3DXMATERIAL*)m_material[m_nModelID].pBuffer->GetBufferPointer();

		D3DMATERIAL9 *pMtrl = &pMat->MatD3D;

		D3DXVec4Transform(&v, &v, &m);

		//���_���V�F�[�_�[�ɓn��
		pEffect->SetVector(m_hvEyePos, &v);

		for (int nCntMat = 0; nCntMat < (int)m_material[m_nModelID].nNumMat; nCntMat++)
		{
			// ���f���̐F�̐ݒ�� 
			v = D3DXVECTOR4(
				1.0f,
				1.0f,
				1.0f,
				1.0f);

			if (m_material[m_nModelID].pTexture[nCntMat] != nullptr)
			{// �e�N�X�`���̓K��
				pTex0 = m_material[m_nModelID].pTexture[nCntMat];
			}

			pEffect->SetVector(m_hvCol, &v);

			// �e�N�X�`���̐ݒ�
			pEffect->SetTexture(m_hTexture, pTex0);

			pEffect->BeginPass(0);

			//���f���p�[�c�̕`��
			m_material[m_nModelID].pMesh->DrawSubset(nCntMat);
			pMtrl++;

			pEffect->EndPass();
		}

		pEffect->End();
	}

	//=========================================

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// ���C�g��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//==================================================================================
}

//=============================================================================
// �ʒu�̃Z�b�^�[
//=============================================================================
void CModel3D::SetPos(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = pos;
}

//=============================================================================
// �����̃Z�b�^�[
//=============================================================================
void CModel3D::SetRot(const D3DXVECTOR3 &rot)
{
	// �ʒu�̐ݒ�
	m_rot = rot;
}

//=============================================================================
// �傫���̃Z�b�^�[
//=============================================================================
void CModel3D::SetSize(const D3DXVECTOR3 & size)
{
	// �傫���̐ݒ�
	m_size = size;
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CModel3D::SetColor(const D3DXCOLOR color)
{
	// �F�̐ݒ�
	m_color = color;
	m_bColor = true;
}

//=============================================================================
// �e�̐���
//=============================================================================
void CModel3D::Shadow()
{
	// �ϐ��錾
	D3DXMATRIX		mtxShadow = {};													// �V���h�E�}�g���b�N�X
	D3DXPLANE		planeField = {};												// ���ʉ��p�ϐ�
	D3DXVECTOR4		vecLight = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);					// ���C�g�����̋t�x�N�g��
	D3DXVECTOR3		posShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// �e�̈ʒu
	D3DXVECTOR3		norShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// �e�̖@��
	extern D3DLIGHT9 g_light;	// �J�������

	D3DXVECTOR3		light = g_light.Direction;
	D3DXVECTOR3		lightVec = light * -1;		// ���C�g����

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);	// �s�񏉊����֐�

	// ���C�g�����̋t�x�N�g���̐ݒ�
	vecLight = D3DXVECTOR4(lightVec.x, lightVec.y, lightVec.z, 0.0f);

	// ���ʉ��p�ϐ��̐ݒ�
	D3DXPlaneFromPointNormal(&planeField, &posShadow, &norShadow);

	// �V���h�E�}�g���b�N�X�̐ݒ�
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// �s��|���Z�֐�
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// �V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	if (m_material[m_nModelID].pBuffer != nullptr)
	{// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_material[m_nModelID].pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_material[m_nModelID].nNumMat; nCntMat++)
		{// �}�e���A�����̐ݒ�
			D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

			// ������F�ɐݒ�
			matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&matD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);

			// ���f���p�[�c�̕`��
			m_material[m_nModelID].pMesh->DrawSubset(nCntMat);
		}
	}

	// �y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=========================================
// �p�x�̐��K������
// ���� : ���K���������p�x
//=========================================
float CModel3D::NormalizeRot(float fRot)
{
	if (fRot < -D3DX_PI)
	{
		fRot += D3DX_PI * 2;
	}
	else if (fRot > D3DX_PI)
	{
		fRot -= D3DX_PI * 2;
	}
	return fRot;
}

//=========================================
// �p�x�̏���ݒ�
// ���� : ������݂������p�x�A���E�p�x
//=========================================
float CModel3D::LimitedRot(float fRot, float fLimitRot)
{
	if (fRot < D3DX_PI * -fLimitRot)
	{
		fRot = D3DX_PI * -fLimitRot;
	}
	else if (fRot > D3DX_PI * fLimitRot)
	{
		fRot = D3DX_PI * fLimitRot;
	}
	return fRot;
}
