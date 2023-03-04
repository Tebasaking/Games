//=========================================
//
//	�o���b�g�̏���(3D [�r���{�[�h])
//	Author:�y���m��
//
//=========================================
#include "bullet.h"
#include "application.h"
#include "calculation.h"
#include "texture.h"
#include "explosion.h"
#include "motion_model3D.h"
#include "camera.h"

//=========================================
//�R���X�g���N�^
//=========================================
CBullet::CBullet()
{
}

//=========================================
//�f�X�g���N�^
//=========================================
CBullet::~CBullet()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CBullet::Init(const D3DXVECTOR3 &pos)
{
	CBillboard::Init(pos);
	m_pos = pos;

	//�T�C�Y�̐ݒ�
	CBillboard::SetSize(D3DXVECTOR3(10.0f,10.0f,0.0f));

	// �e�N�X�`���̐ݒ�
	CBillboard::SetTexture(CTexture::TEXTURE_FIRE);

	// ���C�t�ݒ�
	SetHP(100);

	Camera_Type = CApplication::GetCamera()->GetMode();

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CBullet::Update()
{
	// �Â����W�ɕۑ�����
	m_posOld = m_pos;

	// ���C�t�̏��̎擾
	int nLife = GetHP();

	// ���C�t�̌���
	nLife = ManageHP(-1);

	// ���W�̐ݒ�
	SetPosition(m_pos);

	if (nLife <= 0)
	{
		CBullet::Uninit();
	}

	float Size = GetScale();

	CObject *object = m_pTargetObj;

	if (m_pTargetObj != nullptr)
	{
		D3DXVECTOR3 posTarget = object->GetPosition();
		D3DXMATRIX	*TargetMatrix = object->GetMtxWorld();
		D3DXVECTOR3 SizeTarget = object->GetSize();

		switch (Camera_Type)
		{
		case CCameraPlayer::TYPE_FREE:
			// �e�̈ړ�
			m_pos = WorldCastVtx(D3DXVECTOR3(0.0f, 0.0f, 50.0f), m_pos, m_quaternion);
			break;

		case CCameraPlayer::TYPE_SHOULDER:
			// �e�̈ړ�
			m_TargetPos = object->GetPosition();
			m_pos += LockOn(TargetMatrix);
			break;
		}

		// �����蔻��
		bool bCollision = Collision(object,false);

		if (bCollision)
		{
			// �e�̏I��
			CBullet::Uninit();
			CExplosion::Create(m_pos, m_quaternion);
			object->ManageHP(-1);
		}
	}
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CBullet::Uninit()
{
	CBillboard::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CBullet::Draw()
{
	CBillboard::Draw();
}

//=========================================
// ���b�N�I���̏���
//=========================================
D3DXVECTOR3 CBullet::LockOn(D3DXMATRIX *mtxWorld)
{
	//���̎擾
	D3DXMATRIX *mtx = GetMtxWorld();
	D3DXVECTOR3 BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&BulletPos, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), mtx);
	D3DXVECTOR3 posTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&posTarget, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), mtxWorld);

	// �G�̂������
	D3DXVECTOR3 sub = D3DXVECTOR3(0.0f, 0.0f, 0.f);
	D3DXVECTOR3 distance = posTarget - BulletPos;

	// �O�����œG�̕������o��
	float fDistanceXZ = sqrtf((distance.x * distance.x) + (distance.z * distance.z));
	float fFellowRotY = atan2f(distance.x, distance.z);
	float fFellowRotX = atan2f(fDistanceXZ, distance.y);

	sub.z = sinf(fFellowRotX) * cosf(fFellowRotY) * 100.0f;
	sub.x = sinf(fFellowRotX) * sinf(fFellowRotY) * 100.0f;
	sub.y = cosf(atan2f(distance.y, distance.y))  * 100.0f;

	return sub;
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CBullet* CBullet::Create(const D3DXVECTOR3 &pos, const D3DXQUATERNION &quaternion, CObject *object)
{
	CBullet* pCBullet = nullptr;

	pCBullet = new CBullet;

	if (pCBullet != nullptr)
	{
		pCBullet->Init(pos);
		pCBullet->m_quaternion = quaternion;
		pCBullet->SetTargetObj(object);
	}

	return pCBullet;
}