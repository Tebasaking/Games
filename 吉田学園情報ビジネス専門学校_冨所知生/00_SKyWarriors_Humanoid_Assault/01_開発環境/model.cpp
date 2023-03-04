////=========================================
////
////	3D�I�u�W�F�N�g�̏���
////	Author:�y���m��
////
////=========================================
//#include "model.h"
//#include "application.h"
//#include "inputkeyboard.h"
//#include "texture.h"
//#include "camera.h"
//#include "input.h"
//#include "light.h"
//#define POLYGON_SIZE (400.0f)
//
////=========================================
////�R���X�g���N�^
////=========================================
//CModel::CModel()
//{
//	m_pVtxBuff = nullptr;
//	m_texture = CTexture::TEXTURE_NONE;
//	m_pParents = nullptr;
//	m_filename = {};
//
//	m_pMeshModel = nullptr;
//	m_pBuffMatModel = nullptr;
//	m_nNumMatModel = 0;
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
//	m_mtx = {};
//	vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
//	vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
//
//	pEffect = NULL;
//	m_hmWVP = NULL;
//	m_hmWIT = NULL;
//	m_hvLightDir = NULL;
//	m_hvCol = NULL;
//	m_hvEyePos = NULL;
//	m_hTechnique = NULL;
//	m_hTexture = NULL;
//}
//
////=========================================
////�f�X�g���N�^
////=========================================
//CModel::~CModel()
//{
//
//}
//
////=========================================
////�I�u�W�F�N�g�̏���������
////=========================================
//HRESULT CModel::Init(const D3DXVECTOR3 &pos)
//{
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//	
//	D3DXCreateTextureFromFile(pDevice, ("Data\\F16_Thuderbirds4.bmp"), &pTex0);
//
//	D3DXCreateEffectFromFile(
//		pDevice, "Effect.fx", NULL, NULL,
//		0, NULL, &pEffect, nullptr);
//
//	m_hTechnique = pEffect->GetTechniqueByName("Diffuse");				//�G�t�F�N�g
//	m_hTexture = pEffect->GetParameterByName(NULL, "Tex");				//�e�N�X�`��
//	m_hmWVP = pEffect->GetParameterByName(NULL, "mWVP");				//���[�J��-�ˉe�ϊ��s��
//	m_hmWIT = pEffect->GetParameterByName(NULL, "mWIT");				//���[�J��-���[���h�ϊ��s��
//	m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");		//���C�g�̕���
//	m_hvCol = pEffect->GetParameterByName(NULL, "vColor");				//���_�J���[
//	m_hvEyePos = pEffect->GetParameterByName(NULL, "vEyePos");
//	m_pos = pos;
//
//	return S_OK;
//}
//
////=========================================
////�I�u�W�F�N�g�̍X�V����
////=========================================
//void CModel::Update()
//{
//}
//
////=========================================
////�I�u�W�F�N�g�̏I������
////=========================================
//void CModel::Uninit()
//{
//	//���b�V���̔j��
//	if (m_pMeshModel != NULL)
//	{
//		m_pMeshModel->Release();
//		m_pMeshModel = NULL;
//	}
//
//	//�}�e���A���̔j��
//	if (m_pBuffMatModel != NULL)
//	{
//		m_pBuffMatModel->Release();
//		m_pBuffMatModel = NULL;
//	}
//}

////=========================================
////�I�u�W�F�N�g�̕`�揈��
////=========================================
//void CModel::Draw()
//{
//	PDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	// �v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
//	D3DXMATRIX mtxParents;
//
//	// ���C�g�𖳌�
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&m_mtx);
//
//	// �����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
//	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxRot);
//
//	// �ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);                // �s��ړ��֐�
//	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxTrans);								// �s��|���Z�֐�
//
//	if (m_pParents != nullptr)
//	{
//		mtxParents = m_pParents->GetMtxWorld();
//		// �s��|���Z�֐�
//		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxParents);
//	}
//	//else
//	//{
//	//	// ���[���h�}�g���b�N�X�̐ݒ�
//	//	pDevice->GetTransform(D3DTS_WORLD, &mtxParents);
//	//}
//
//	// �`��̏I��
//	pDevice->EndScene();
//}
//
//void CModel::Draw(D3DXMATRIX mtxParent)
//{
//	PDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
//
//	// ���݂̃}�e���A���ۑ��p
//	D3DMATERIAL9 matDef;
//	// �}�e���A���f�[�^�ւ̃|�C���^
//	D3DXMATERIAL *pMat;
//	D3DXVECTOR3 scale(5.0f, 5.0f, 5.0f);
//
//	extern D3DLIGHT9 g_light;	// �J�������
//
//	D3DXMATRIX m, mT, mR, mView, mProj;
//	D3DXVECTOR4 v, light_pos;
//
//
//	//---------------------------------------------------------
//	// �`��
//	//---------------------------------------------------------
//	if (SUCCEEDED(pDevice->BeginScene()))
//	{
//		CCamera *pCamera = CApplication::GetCamera();
//
//		D3DMATRIX viewMatrix = pCamera->GetView();
//		D3DMATRIX projMatrix = pCamera->GetProjection();
//
//		// ���[���h�s��
//		D3DXMatrixIdentity(&m_mtx);
//
//		//�傫���̐ݒ�
//		D3DXMatrixScaling(&mtxScale, m_scale, m_scale, m_scale);   // �s��g�k�֐�
//		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxScale);          // �s��|���Z�֐�
//
//																// �����̔��f
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);		// �s���]�֐�
//		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxRot);		// �s��|���Z�֐� 
//
//															// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
//		D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);				// �N�I�[�^�j�I���ɂ��s���]
//		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxRot);    // �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
//
//														//�ʒu�𔽉f
//		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
//		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxTrans);
//
//		// �s��|���Z�֐�
//		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxParent);
//
//		//�s��̐ݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &m_mtx);
//		pDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
//		pDevice->SetTransform(D3DTS_PROJECTION, &projMatrix);
//
//		if (pEffect != NULL)
//		{
//			//-------------------------------------------------
//			// �V�F�[�_�̐ݒ�
//			//-------------------------------------------------
//			pEffect->SetTechnique(m_hTechnique);
//			pEffect->Begin(NULL, 0);
//			pEffect->BeginPass(0);
//			pDevice->SetFVF(FVF_VERTEX_3D);
//
//			//pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
//			//pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
//
//			D3DXMatrixTranslation(&m, 1.0f, 0.0f, 0.0f);
//
//			D3DXMatrixRotationY(&mR, 0.0f);
//			D3DXMatrixTranslation(&mT, 1.0f, 1.2f, 0.0f);
//
//			//�ʒu�𔽉f
//			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
//
//			// ���[�J��-�ˉe�ϊ��s��
//			D3DXMatrixInverse(&m, NULL, &m_mtx);
//			D3DXMatrixTranspose(&m, &m);
//			pEffect->SetMatrix(m_hmWIT, &m);
//
//			// ���[�J��-�ˉe�ϊ��s��
//			m = m_mtx * viewMatrix * projMatrix;
//			pEffect->SetMatrix(m_hmWVP, &m);
//
//			// ���C�g�̕���
//			light_pos = D3DXVECTOR4(g_light.Direction.x, g_light.Direction.y, g_light.Direction.z, 0);
//
//			D3DXMatrixInverse(&m, NULL, &m_mtx);
//			D3DXVec4Transform(&v, &light_pos, &m);
//
//			D3DXVec3Normalize((D3DXVECTOR3 *)&v, (D3DXVECTOR3 *)&v);
//
//			//�����̑傫��
//			v.w = -0.8f;
//			pEffect->SetVector(m_hvLightDir, &v);
//
//			// ���_
//			m = m_mtx *viewMatrix;
//			D3DXMatrixInverse(&m, NULL, &m);
//
//			//����
//			v = D3DXVECTOR4(0, 0, 0, 1);
//
//			//�}�e���A���f�[�^�̃|�C���^���擾����
//			pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
//
//			D3DMATERIAL9 *pMtrl = &pMat->MatD3D;
//
//			D3DXVec4Transform(&v, &v, &m);
//
//			//���_���V�F�[�_�[�ɓn��
//			pEffect->SetVector(m_hvEyePos, &v);
//
//			for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
//			{
//				//�J���[�̌��ɑ΂��锽�˓I�Ȃ�̐ݒ�(����)
//				v = D3DXVECTOR4(
//					pMtrl->Diffuse.r,
//					pMtrl->Diffuse.g,
//					pMtrl->Diffuse.b,
//					1.0f);
//
//				// �e�N�X�`���̐ݒ�
//				pEffect->SetTexture(m_hTexture, pTex0);
//
//				pEffect->SetVector(m_hvCol, &v);
//
//				//���f���p�[�c�̕`��
//				m_pMeshModel->DrawSubset(nCntMat);
//				pMtrl++;
//			}
//
//			pEffect->EndPass();
//			pEffect->End();
//		}
//
//		// �`��̏I��
//		pDevice->EndScene();
//
//		////*****************************************
//		//// �e�̕\��
//		////*****************************************
//		////�e�̏���
//		//DrawShadow();
//	}
//}
//
////=========================================
//// ���W�̐ݒ菈��
//// ���� : m_pos�ɑ�����������W�̒l
////=========================================
//void CModel::SetPosition(const D3DXVECTOR3& pos)
//{ 
//	m_pos = pos;
//}
//
////=========================================
//// ��]�̐ݒ�擾
//// ���� : m_rot�ɑ���������p�x�̒l
////=========================================
//void CModel::SetRot(const D3DXVECTOR3& rot)
//{
//	m_rot = rot;
//}
////=========================================
//// �T�C�Y�̐ݒ�
//// ���� : �T�C�Y�̎w��
////=========================================
//void CModel::SetScale(const float size)
//{
//	m_scale = size;
//}
//
////=========================================
//// ���f���̐ݒ�
//// ���� : �t�@�C�����̓���
////=========================================
//void CModel::SetModel(const char* name)
//{
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	m_filename = name;
//
//	//X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX(m_filename,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMatModel,
//		NULL,
//		&m_nNumMatModel,
//		&m_pMeshModel);
//}
//
////=========================================
//// ���f���̑傫���̎Z�o
////=========================================
//D3DXVECTOR3 CModel::GetModelSize()
//{
//	// �f�o�C�X�ւ̃|�C���^�̎擾
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//		//X�t�@�C���̓ǂݍ���
//		D3DXLoadMeshFromX(m_filename,
//			D3DXMESH_SYSTEMMEM,
//			pDevice,
//			NULL,
//			&m_pBuffMatModel,
//			NULL,
//			&m_nNumMatModel,
//			&m_pMeshModel);
//
//		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
//		D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
//
//		int nNumVtx;		// ���_��
//		DWORD pSizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
//		BYTE *pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
//
//		// ���_���̎擾
//		nNumVtx = m_pMeshModel->GetNumVertices();
//
//		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
//		pSizeFVF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());
//
//		// ���_�o�b�t�@�̃��b�N
//		m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//		{
//			// ���_���W�̑��
//			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//			// ��r(�ŏ��l�����߂�)x
//			if (vtx.x < vtxMin.x)
//			{
//				vtxMin.x = vtx.x;
//			}
//			// ��r(�ŏ��l�����߂�)y
//			if (vtx.y < vtxMin.y)
//			{
//				vtxMin.y = vtx.y;
//			}
//			// ��r(�ŏ��l�����߂�)z
//			if (vtx.z < vtxMin.z)
//			{
//				vtxMin.z = vtx.z;
//			}
//
//			// ��r(�ő�l�����߂�)x
//			if (vtx.x > vtxMax.x)
//			{
//				vtxMax.x = vtx.x;
//			}
//			// ��r(�ő�l�����߂�)y
//			if (vtx.y > vtxMax.y)
//			{
//				vtxMax.y = vtx.y;
//			}
//			// ��r(�ő�l�����߂�)z
//			if (vtx.z > vtxMax.z)
//			{
//				vtxMax.z = vtx.z;
//			}
//
//			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//			pVtxBuff += pSizeFVF;
//		}
//
//		// �T�C�Y�̌v�Z
//		m_size = vtxMax - vtxMin;
//
//		// ���_�o�b�t�@�̃A�����b�N
//		m_pMeshModel->UnlockVertexBuffer();
//
//		return m_size;
//}
//
////=========================================
////�N�H�[�^�j�I���̐ݒu
////=========================================
//void CModel::SetQuaternion(const D3DXQUATERNION quaternion)
//{
//	// �N�I�[�^�j�I����K�p
//	m_quaternion = quaternion;
//
//	// �N�I�[�^�j�I���̃m�[�}���C�Y
//	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);
//}
//
////=========================================
//// �p�x�̐��K������
//// ���� : ���K���������p�x
////=========================================
//float CModel::NormalizRot(float fRot)
//{
//	if (fRot < -D3DX_PI)
//	{
//		fRot += D3DX_PI * 2;
//	}
//	else if (fRot > D3DX_PI)
//	{
//		fRot -= D3DX_PI * 2;
//	}
//	return fRot;
//}
//
////=========================================
//// �p�x�̏���ݒ�
//// ���� : ������݂������p�x�A���E�p�x
////=========================================
//float CModel::LimitedRot(float fRot, float fLimitRot)
//{
//	if (fRot < D3DX_PI * -fLimitRot)
//	{
//		fRot = D3DX_PI * -fLimitRot;
//	}
//	else if (fRot > D3DX_PI * fLimitRot)
//	{
//		fRot = D3DX_PI * fLimitRot;
//	}
//	return fRot;
//}
//
////=========================================
//// �e�̕`�揈��
//// �T�v : Draw�ōs�����e�̏���
////=========================================
//void CModel::DrawShadow()
//{
//	extern D3DLIGHT9 g_light;	// �J�������
//
//	PDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	// ���݂̃}�e���A���ۑ��p
//	D3DMATERIAL9 matDef;
//
//	// �}�e���A���f�[�^�ւ̃|�C���^
//	D3DXMATERIAL *pMat;
//
//	// �ϐ��錾
//	D3DXMATRIX		mtxShadow = {};										// �V���h�E�}�g���b�N�X
//	D3DXPLANE		planeField = {};									// ���ʉ��p�ϐ�
//	D3DXVECTOR4		vecLight = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);		// ���C�g�����̋t�x�N�g��
//	D3DXVECTOR3		posShadow = D3DXVECTOR3(0.0f, -13.0f, 0.0f);			// �e�̈ʒu
//	D3DXVECTOR3		norShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// �e�̖@��
//	D3DXVECTOR3		light = g_light.Direction;
//	D3DXVECTOR3		lightVec = light * -1;								// ���C�g����
//
//	// �V���h�E�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&mtxShadow);    // �s�񏉊����֐�
//
//	// ���C�g�����̋t�x�N�g���̐ݒ�
//	vecLight = D3DXVECTOR4(lightVec.x, lightVec.y, lightVec.z, 0.0f);
//
//	// ���ʉ��p�ϐ��̐ݒ�
//	D3DXPlaneFromPointNormal(&planeField, &posShadow, &norShadow);
//
//	// �V���h�E�}�g���b�N�X�̐ݒ�
//	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);
//
//	// �s��|���Z�֐�
//	D3DXMatrixMultiply(&mtxShadow, &m_mtx, &mtxShadow);
//
//	// �V���h�E�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);
//
//	// ���݂̃}�e���A����ێ�
//	pDevice->GetMaterial(&matDef);
//
//	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
//	{
//		//�}�e���A���f�[�^�̃|�C���^���擾����
//		pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
//
//		// �}�e���A�����̐ݒ�
//		D3DMATERIAL9  matD3D = pMat->MatD3D;
//
//		// ������F�ɐݒ�
//		matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
//		matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
//
//		// �}�e���A���̐ݒ�
//		pDevice->SetMaterial(&matD3D);
//
//		// �e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, nullptr);
//
//		// ���f���p�[�c�̕`��
//		m_pMeshModel->DrawSubset(nCntMat);
//	}
//
//	// �ێ����Ă����}�e���A����߂�
//	pDevice->SetMaterial(&matDef);
//}