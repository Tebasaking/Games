//=============================================================================
//
// ���[�V�����L�����N�^�[3D�N���X(model3D.h)
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_model3D.h"
#include "motion.h"
#include "render.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CMotionModel3D * CMotionModel3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionModel3D *pMotionModel3D = nullptr;

	// �������̉��
	pMotionModel3D = new CMotionModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionModel3D != nullptr);

	// ���l�̏�����
	pMotionModel3D->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �C���X�^���X��Ԃ�
	return pMotionModel3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionModel3D::CMotionModel3D(int nPriority) : CObject(nPriority),
m_pMotion(nullptr),		// ���[�V�������
m_pos(D3DXVECTOR3()),										// �ʒu
m_posOld(D3DXVECTOR3()),									// �ߋ��ʒu
m_size(D3DXVECTOR3())										// �傫��
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionModel3D::~CMotionModel3D()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionModel3D::Init(const D3DXVECTOR3 &pos)
{
	// �ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �傫��

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionModel3D::Uninit()
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// �I�u�W�F�N�g2D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 3D�X�V���s��
//=============================================================================
void CMotionModel3D::Update()
{
	if (m_pMotion != nullptr)
	{// ���[�V�����ԍ��̐ݒ�
		m_pMotion->Update();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 3D�`����s��
//=============================================================================
void CMotionModel3D::Draw()
{
	if (this == nullptr)
	{
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld, mtxRot, mtxTrans, mtxScaling;

	// �`��̏I��
	pDevice->EndScene();

	D3DXVECTOR3 rot = GetRot();

	if (SUCCEEDED(pDevice->BeginScene()))
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);											// �s�񏉊����֐�

		if (CApplication::GetMode() == CApplication::MODE_TITLE)
		{// �^�C�g�������T�C�Y��K������
			m_size = GetSize();
			// �T�C�Y�̔��f
			D3DXMatrixScaling(&mtxScaling, m_size.x, m_size.y, m_size.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScaling);					// �s��|���Z�֐�
		}

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);			// �s���]�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);						// �s��|���Z�֐� 

		// �N�H�[�^�j�I���̔��f
		D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);						// �N�I�[�^�j�I���ɂ��s���]
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);						// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// �s��ړ��֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);					// �s��|���Z�֐�

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	}

	pDevice->EndScene();

	if (m_pMotion != nullptr)
	{// �p�[�c�̕`��ݒ�
		m_pMotion->SetParts(mtxWorld);
	}

	// �}�g���b�N�X�̐ݒ�
	SetMtxWorld(mtxWorld);
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̓ǂݍ��݂��s��
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(0);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(0);
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̓ǂݍ��݂��s���A�����Ŏw�肳�ꂽ���[�V�����ɐݒ肷��
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName, const int nNumMotion)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(nNumMotion);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(nNumMotion);
}
