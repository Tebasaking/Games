////=========================================
////
////	3D�I�u�W�F�N�g�̏���
////	Author:�y���m��
////
////=========================================
//#include "object3D.h"
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
//CObject3D::CObject3D()
//{
//	m_pVtxBuff = nullptr;
//	m_texture = CTexture::TEXTURE_NONE;
//
//	m_pMeshModel = nullptr;
//	m_pBuffMatModel = nullptr;
//	m_nNumMatModel = 0;
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_quaternion = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
//	m_mtxWorldModel = {};
//
//	pEffect = NULL;
//}
//
////=========================================
////�f�X�g���N�^
////=========================================
//CObject3D::~CObject3D()
//{
//
//}
//
////=========================================
////�I�u�W�F�N�g�̏���������
////=========================================
//HRESULT CObject3D::Init(const D3DXVECTOR3 &pos)
//{
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	// �e�N�X�`������
//	D3DXCreateTextureFromFile(pDevice, ("data\\F16_Thuderbirds4.bmp"), &pTex0);
//
//	return S_OK;
//}
//
////=========================================
////�I�u�W�F�N�g�̍X�V����
////=========================================
//void CObject3D::Update()
//{
//}
//
////=========================================
////�I�u�W�F�N�g�̏I������
////=========================================
//void CObject3D::Uninit()
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
//
//	CObject::Release();
//}
//
////=========================================
////�I�u�W�F�N�g�̕`�揈��
////=========================================
//void CObject3D::Draw()
//{
//	PDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	// �v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
//	// ���݂̃}�e���A���ۑ��p
//	D3DMATERIAL9 matDef;
//	// �}�e���A���f�[�^�ւ̃|�C���^
//	D3DXMATERIAL *pMat;
//	D3DXVECTOR3 scale(5.0f, 5.0f, 5.0f);
//
//	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O�̐ݒ�
//
//	//// ���C�g�𖳌�
//	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	// ���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&m_mtxWorldModel);
//
//	// �s��g�k�֐�
//	//D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
//	//// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
//	//D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxScale);
//
//	// �����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);
//
//	// �ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);                // �s��ړ��֐�
//	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);          // �s��|���Z�֐�
//
//	//*****************************************
//	// �e�̕\��
//	//*****************************************
//	//�e�̏���
//	DrawShadow();
//
//	// ���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);
//
//	//DWORD d;
//	//pDevice->GetRenderState(D3DRS_AMBIENT, &d);
//	//pDevice->SetRenderState(D3DRS_AMBIENT, 0x88888888);
//
//	// ���݂̃}�e���A����ێ�
//	pDevice->GetMaterial(&matDef);
//
//	// �}�e���A���f�[�^�ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
//
//	for (int i = 0; i < (int)m_nNumMatModel; i++)
//	{
//		pMat[i].MatD3D.Ambient = pMat[i].MatD3D.Diffuse;
//
//			// ������F�ɐݒ�
////		pMat[i].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
////		pMat[i].MatD3D.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		//pMat[i].MatD3D.Power = 5.0f;
//
//		// �}�e���A���̐ݒ�
//		pDevice->SetMaterial(&pMat[i].MatD3D);
//
//		// �e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, pTex0);
//
//		// ���f���p�[�c�̕`��
//		m_pMeshModel->DrawSubset(i);
//	}
//
//	// �ۑ����Ă����}�e���A����߂�
//	pDevice->SetMaterial(&matDef);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, NULL);
//
//	// ���C�g�𖳌�
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�
//}
//
////=========================================
//// �I�u�W�F�N�g�̃N���G�C�g
//// ���� : �I�u�W�F�N�g�𐶐����������W
////=========================================
//CObject3D* CObject3D::Create(const D3DXVECTOR3 &pos)
//{
//	//int nNumCreate = m_nNumAll;
//
//	CObject3D* pObject3D = nullptr;
//
//	pObject3D = new CObject3D;
//
//	if (pObject3D != nullptr)
//	{
//		pObject3D->Init(pos);
//	}
//
//	return pObject3D;
//}
//
////=========================================
//// ���W�̐ݒ菈��
//// ���� : m_pos�ɑ�����������W�̒l
////=========================================
//void CObject3D::SetPosition(const D3DXVECTOR3& pos)
//{
//	m_pos = pos;
//}
//
////=========================================
//// ��]�̐ݒ�擾
//// ���� : m_rot�ɑ���������p�x�̒l
////=========================================
//void CObject3D::SetRot(const D3DXVECTOR3& rot)
//{
//	m_rot = rot;
//}
//
////=========================================
//// �e�N�X�`���̐ݒ�
//// ���� : �e�N�X�`���̃t�@�C�����̎w��
////=========================================
//void CObject3D::SetTexture(CTexture::TEXTURE texture)
//{
//	m_texture = texture;
//}
//
////=========================================
//// �T�C�Y�̐ݒ�
//// ���� : �T�C�Y�̎w��
////=========================================
//void CObject3D::SetSize(const float size)
//{
//	m_size = size;
//}
//
////=========================================
//// ���f���̐ݒ�
//// ���� : �t�@�C�����̓���
////=========================================
//void CObject3D::SetModel(const char* name)
//{
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();
//
//	//X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX(name,
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
////�N�H�[�^�j�I���̐ݒu
////=========================================
//void CObject3D::SetQuaternion(const D3DXQUATERNION quaternion)
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
//float CObject3D::NormalizRot(float fRot)
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
//float CObject3D::LimitedRot(float fRot, float fLimitRot)
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
//void CObject3D::DrawShadow()
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
//	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorldModel, &mtxShadow);
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