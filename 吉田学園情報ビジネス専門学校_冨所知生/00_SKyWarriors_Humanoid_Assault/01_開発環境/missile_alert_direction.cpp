//=========================================
//
//	�~�T�C���A���[�g�̏���
//	Author:�y���m��
//
//=========================================
#include "missile_alert_direction.h"
#include "camera.h"
#include "application.h"
#include "debug_proc.h"
#include "bullet3D.h"

//D3DXVECTOR3 CAlert_Direction::m_TargetPos = {};
//=========================================
//�R���X�g���N�^
//=========================================
CAlert_Direction::CAlert_Direction()
{

}

//=========================================
//�f�X�g���N�^
//=========================================
CAlert_Direction::~CAlert_Direction()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CAlert_Direction::Init(const D3DXVECTOR3 &pos)
{
	//����������
	CObject2D::Init(pos);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_ARROW);

	//�T�C�Y�̐ݒ�
	CObject2D::SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �^�C�v�ݒ�
	//SetObjectType(OBJECT_TARGET);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CAlert_Direction::Update()
{
	if (!m_bLockOn)
	{
		return;
	}

	D3DXVECTOR3 BulletPos;			// �G�l�~�[�̕ϊ��O���W
	D3DXVECTOR3 PlayerPos;			// �v���C���[�̍��W
	D3DXVECTOR3 ScreenPlayer;		// �v���C���[��SCREEN���W

	m_Size = 50.0f;

	//�v���C���[�̍��W���擾
	if (pObject != nullptr)
	{
		// �ڕW�̍��W���X�N���[�����W�ɕϊ�����
		BulletPos = pObject->GetPosition();
		m_TargetPos = CApplication::WorldToScreen(BulletPos);
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CObject *object = CObject::GetObjectTop(nCnt);

		//�v���C���[�̍��W���擾
		while (object)
		{
			if (object != nullptr)
			{
				EObjType ObjType = object->GetObjectType();

				if (ObjType == OBJECT_PLAYER)
				{
					PlayerPos = object->GetPosition();

					break;
				}
			}
			object = object->GetObjectNext();
		}
	}

	float length = D3DXVec3Length(&(BulletPos - PlayerPos));
	m_Size = 10.0f + ((1 / ((length) + 1)) * 100000.0);

	if (m_Size >= 70.0f)
	{
		m_Size = 70.0f;
	}

	CDebugProc::Print("%f\n",m_Size);

	//�T�C�Y�̐ݒ�
	CObject2D::SetScale(D3DXVECTOR3(m_Size, m_Size, 0.0f));

	// �A���[�g��X�����̎n�_
	float ALERT_SCREEN_WIDTH_BEGIN = 300.0f;

	// �A���[�g��X�����̏I�_
	float ALERT_SCREEN_WIDTH_END = SCREEN_WIDTH - 300.0f;

	// �A���[�g��Y�����̎n�_
	float ALERT_SCREEN_HEIGHT_BEGIN = 500;
	// �A���[�g��Y�����̏I�_
	float ALERT_SCREEN_HEIGHT_END = SCREEN_HEIGHT - 200.0f;

	//// �A���[�g�n�_����
	//if (m_TargetPos.x >= ALERT_SCREEN_WIDTH_END)
	//{
	//	m_TargetPos.x = ALERT_SCREEN_WIDTH_END - m_Size;
	//}
	//if (m_TargetPos.y <= ALERT_SCREEN_HEIGHT_BEGIN)
	//{
	//	m_TargetPos.y = ALERT_SCREEN_HEIGHT_BEGIN + m_Size;
	//}

	//// �I�_����
	//if (m_TargetPos.x <= ALERT_SCREEN_WIDTH_BEGIN)
	//{
	//	m_TargetPos.x = ALERT_SCREEN_WIDTH_BEGIN + m_Size;
	//}
	//if (m_TargetPos.y >= ALERT_SCREEN_HEIGHT_END)
	//{
	//	m_TargetPos.y = ALERT_SCREEN_HEIGHT_END - m_Size;
	//}

	ScreenPlayer = CApplication::WorldToScreen(PlayerPos);

	// TargetPos��PlayerPos����p�x�����߂�
	D3DXVECTOR3 rot = ScreenPlayer - m_TargetPos;
	rot.z = atan2f(rot.x, rot.y);
	rot = NormalizeRotXYZ(rot);

	m_TargetPos.x = ScreenPlayer.x + sinf(rot.z) * 100.0f;
	m_TargetPos.y = ScreenPlayer.y + cosf(rot.z) * 100.0f;

	/*D3DXVECTOR3 MoveRot = AtanRot(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),m_TargetPos);

	m_TargetPos = MtxPosRot(D3DXVECTOR3(0.0f,500.0f, 0.0f), MoveRot, D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f ,0.0f));
*/
	// �X�N���[�����W�ɐݒ肷��
	SetPosition(m_TargetPos);

	// TargetPos��PlayerPos����p�x�����߂�
	rot.y = rot.z;
	//rot = NormalizeRotXYZ(rot);

	SetRotation(rot);

	// ��O����
	CBullet3D *pBullet = (CBullet3D*)pObject;

	if (pBullet != nullptr)
	{
		if (pBullet->GetSpeed() >= 100)
		{
			SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CAlert_Direction::Uninit()
{
	// �I������
	CObject2D::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CAlert_Direction::Draw()
{
	if (!m_bLockOn)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// Z�e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// ���e�X�g���g�p����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	{
		// 2D�I�u�W�F�N�g�̕`�揈��
		CObject2D::Draw();
	}

	// Z�e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���e�X�g�̏I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CAlert_Direction* CAlert_Direction::Create(const D3DXVECTOR3 &pos, CObject *object)
{
	CAlert_Direction* pCAlert = nullptr;

	pCAlert = new CAlert_Direction;

	if (pCAlert != nullptr)
	{
		pCAlert->Init(pos);
	}

	// �^�[�Q�b�g��ݒ肷��I�u�W�F�N�g���擾
	pCAlert->SetObject(object);

	return pCAlert;
}