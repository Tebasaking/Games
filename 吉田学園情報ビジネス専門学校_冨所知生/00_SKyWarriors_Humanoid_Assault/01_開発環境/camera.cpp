//**************************************************************************************************
//
// �J��������(camera.h)
// Auther�F�������l
// Author : ���c�C�l
// Author : �y���m��
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "camera.h"
#include "application.h"
#include "calculation.h"
#include "debug_proc.h"
#include "utility.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const float CCamera::CAMERA_NEAR = 30.0f;		// �j�A
const float CCamera::CAMERA_FUR = 50000.0f;	// �t�@�[

//=============================================================================
// �R���X�g���N�^
// Author	: �������l
// �T�v		: �C���X�^���X�������ɍs������
//=============================================================================
CCamera::CCamera() :
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),					// ���_
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),					// �����_
	m_rotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),			 	// �ړ�����
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_quaternion(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f)),	// �N�I�[�^�j�I��
	m_viewType(TYPE_CLAIRVOYANCE),							// ���e���@�̎��
	m_event(EVENT_NORMAL),
	m_Dest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fDistance(0.0f),										// ���_���璍���_�܂ł̋���
	m_Destquaternion(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
{
	m_mtxProj = {};		// �v���W�F�N�V�����}�g���b�N�X
	m_mtxView = {};		// �r���[�}�g���b�N�X
	m_Objectmode = CObject::Object_mode::NONE_MODE;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�ƒ����_�̊Ԃ̋������Z�o����
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 pos)
{
	m_posV = pos;

	// ���_�ƒ����_�̋���
	D3DXVECTOR3 posDiss = m_posR - m_posV;
	m_fDistance = sqrtf((posDiss.y * posDiss.y) + (posDiss.x * posDiss.x) + (posDiss.z * posDiss.z));

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �I��
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V
//=============================================================================
void CCamera::Update(void)
{
	if (m_event == EVENT_NORMAL)
	{
		D3DXVECTOR3 Result = m_Dest - m_rotMove;
		m_rotMove += Result * 0.25f;
	}

	m_quaternion += (m_Destquaternion - m_quaternion) * 0.1f;
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);

	/*CDebugProc::Print("�J�����̍��W : (%f,%f,%f) \n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("�J�����̉�] : (%f,%f,%f,%f) \n", m_quaternion.x, m_quaternion.y, m_quaternion.z, m_quaternion.w);*/
}

//=============================================================================
// �J�����̐ݒ�
// Author : �y���m��
// �T�v : �r���[�}�g���b�N�X�̐ݒ�
//=============================================================================
void CCamera::Set()
{
	// �h��J�E���^�[�����炷
	m_nCntFrame--;

	if (m_nCntFrame >= 0)
	{
		D3DXVECTOR3 adjustPos = {};

		adjustPos.x = FloatRandom(m_Magnitude, -m_Magnitude);
		adjustPos.y = FloatRandom(m_Magnitude, -m_Magnitude);
		adjustPos.z = FloatRandom(m_Magnitude, -m_Magnitude);

		m_posV += adjustPos;
		m_posR += adjustPos;
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);			// �s�񏉊����֐�

	D3DXMATRIX mtxRot, mtxTrans;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_posV.x, m_posV.y, m_posV.z);	// �s��ړ��֐�
	D3DXMatrixInverse(&mtxTrans, NULL, &mtxTrans);					// �t�s��Ɍv�Z
	D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxTrans);			// �s��|���Z�֐�

	// �����̔��f
	D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);	// �N�I�[�^�j�I���ɂ��s���]
	D3DXMatrixInverse(&mtxRot, NULL, &mtxRot);				// �t�s��Ɍv�Z
	D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxRot);	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �r���[�|�[�g�̓K��
	pDevice->SetViewport(&m_viewport);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProj);			// �s�񏉊����֐�

	switch (m_viewType)
	{
	case TYPE_CLAIRVOYANCE:
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(�������e)
		D3DXMatrixPerspectiveFovLH(&m_mtxProj,				// �v���W�F�N�V�����}�g���b�N�X
			D3DXToRadian(60.0f),							// ����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// �A�X�y�N�g��
			CAMERA_NEAR,									// �j�A
			CAMERA_FUR);									// �t�@�[
		break;

	case TYPE_PARALLEL:
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		D3DXMatrixOrthoLH(&m_mtxProj,						// �v���W�F�N�V�����}�g���b�N�X
			(float)SCREEN_WIDTH * 5,						// ��
			(float)SCREEN_WIDTH * 5,						// ����
			CAMERA_NEAR,									// �j�A
			CAMERA_FUR);									// �t�@�[
		break;

	default:
		assert(false);
		break;
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//=============================================================================
// �J�����̐ݒ�
// Author : �y���m��
// �T�v : �r���[�}�g���b�N�X�̐ݒ�
//=============================================================================
void CCamera::Set2()
{
	//// �h��J�E���^�[�����炷
	//m_nCntFrame--;

	//if (m_nCntFrame >= 0)
	//{
	//	D3DXVECTOR3 adjustPos = {};

	//	adjustPos.x = FloatRandom(m_Magnitude, -m_Magnitude);
	//	adjustPos.y = FloatRandom(m_Magnitude, -m_Magnitude);
	//	adjustPos.z = FloatRandom(m_Magnitude, -m_Magnitude);

	//	m_posV += adjustPos;
	//	m_posR += adjustPos;
	//}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);			// �s�񏉊����֐�

	D3DXVECTOR3 vecUp(0.0f, 0.0f, 1.0f);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &vecUp);

	D3DXMATRIX mtxRot, mtxTrans;

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxRot);						// �s��|���Z�֐� 

	//	// �ʒu�𔽉f
	//	D3DXMatrixTranslation(&mtxTrans, m_posV.x, m_posV.y, m_posV.z);	// �s��ړ��֐�
	////	D3DXMatrixInverse(&mtxTrans, NULL, &mtxTrans);					// �t�s��Ɍv�Z
	//	D3DXMatrixMultiply(&m_mtxView, &m_mtxView, &mtxTrans);			// �s��|���Z�֐�

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �r���[�|�[�g�̓K��
	pDevice->SetViewport(&m_viewport);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProj);			// �s�񏉊����֐�

	switch (m_viewType)
	{
	case TYPE_CLAIRVOYANCE:
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(�������e)
		D3DXMatrixPerspectiveFovLH(&m_mtxProj,				// �v���W�F�N�V�����}�g���b�N�X
			D3DXToRadian(60.0f),							// ����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// �A�X�y�N�g��
			CAMERA_NEAR,									// �j�A
			CAMERA_FUR);									// �t�@�[
		break;
	case TYPE_PARALLEL:
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		D3DXMatrixOrthoLH(&m_mtxProj,						// �v���W�F�N�V�����}�g���b�N�X
			(float)SCREEN_WIDTH * 10,						// ��
			(float)SCREEN_WIDTH * 10,						// ����
			CAMERA_NEAR,									// �j�A
			CAMERA_FUR);									// �t�@�[
		break;
	default:
		assert(false);
		break;
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//==================================================
// �r���[�|�[�g�̑傫���ݒ�
// Author : �y���m��
// ���� : ��ʍ���̍��WX,Y�A���A����
//==================================================
void CCamera::SetViewSize(DWORD X, DWORD Y, int fWidth, int fHeight)
{
	//��������
	m_viewport.X = X;				//�r���[�|�[�g�̍���X���W
	m_viewport.Y = Y;				//�r���[�|�[�g�̍���Y���W
	m_viewport.Width = fWidth;		//�r���[�|�[�g�̕�
	m_viewport.Height = fHeight;	//�r���[�|�[�g�̍���
}

//==================================================
// �r���[�|�[�g�̊g�k
// Author : �y���m��
// ���� : �J�n�ʒuX�A�J�n�ʒuY�A���A����
//==================================================
void CCamera::AddViewSize(DWORD X, DWORD Y, int fWidth, int fHeight)
{
	//------------------------------
	// ���̉��Z
	//------------------------------
	if (m_viewport.Width < SCREEN_WIDTH - 1.0f)
	{//�����X�N���[�����Ȃ�
	 //���̉��Z
		m_viewport.Width += fWidth;

		if (m_viewport.X > 0)
		{//�r���[�|�[�g�̍��オ��ʂ̍�����傫���Ȃ�
			m_viewport.X += X;	//�r���[�|�[�g�̍�����W���ړ�
		}
	}

	//------------------------------
	// �����̉��Z
	//------------------------------
	if (m_viewport.Height < SCREEN_HEIGHT - 1.0f)
	{//�����X�N���[�����Ȃ�
	 //�����̉��Z
		m_viewport.Height += fHeight;

		if (m_viewport.Y > 0)
		{//�r���[�|�[�g�̍��オ��ʂ̍�����傫���Ȃ�
			m_viewport.Y += Y;	//�r���[�|�[�g�̍�����W���ړ�
		}
	}
}

//=========================================
// �J������h�炷����
// Author : �y���m��
//=========================================
void CCamera::ShakeCamera(int ShakeFrame, float Magnitude)
{
	m_nCntFrame = ShakeFrame;
	m_Magnitude = Magnitude;
}

//=============================================================================
// �����_�̉�]
// Author : �������l
// Author : YudaKaito
// �T�v : 
//=============================================================================
void CCamera::RPosRotate()
{
	m_posR = WorldCastVtx(D3DXVECTOR3(0.0f, 0.0f, m_fDistance), m_posV, m_quaternion);
}

//=============================================================================
// ���_�̉�]
// Author : �������l
// Author : YudaKaito
// �T�v : 
//=============================================================================
void CCamera::VPosRotate()
{
	m_posV = WorldCastVtx(D3DXVECTOR3(0.0f, 0.0f, -m_fDistance), m_posR, m_quaternion);
}
