//=========================================
//
//	�I�u�W�F�N�g�̏���
//	Author:�y���m��
//
//=========================================
#include "object.h"
#include "camera.h"
#include "camera_player.h"
#include "camera_radar.h"
#include "camera_title.h"
#include "application.h"
#include <assert.h>

int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[LAYER_MAX] = { nullptr };
CObject *CObject::m_pCurrent[LAYER_MAX] = { nullptr };

//=========================================
//�R���X�g���N�^
//=========================================
CObject::CObject(int nPriority /*= LAYER_ONE*/)/*:	
m_pNext(nullptr),
m_pPrev(nullptr)*/
{
	// �I�u�W�F�N�g��ʏ탂�[�h�ɂ���
	m_objmode = MAX_MODE;

	//�擪�|�C���^�[������U���Ă��Ȃ���
	if (m_pTop[nPriority] == nullptr)
	{
		//�擪�̃|�C���^�[������U��
		m_pTop[nPriority] = this;
	}
	else
	{
		//��O�̃|�C���^�[�̏���Current�ɓ����
		m_pPrev = m_pCurrent[nPriority];
		m_pCurrent[nPriority]->m_pNext = this;
	}

	//�J�����g�Ɍ��݂̃|�C���^�[�������
	m_pCurrent[nPriority] = this;
	//���S�t���O��false�ɂ���
	m_DeathFlag = false;

 	m_Priority = nPriority;
}

//=========================================
//�f�X�g���N�^
//=========================================
CObject::~CObject()
{

}

//=========================================
//�S�Ă̍X�V����
//=========================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			{
				CObject *pBox = m_pTop[nCnt];

				while (pBox != nullptr)
				{
					CObject *pObjectNext = pBox->m_pNext;

					if (!pBox->m_DeathFlag)
					{
						// �X�V����
						pBox->Update();
					}
					pBox = pObjectNext;
				}
			}

			{
				CObject *pBox = m_pTop[nCnt];

				while (pBox != nullptr)
				{
					CObject *pObjectNext = pBox->m_pNext;

					if (pBox->m_DeathFlag)
					{
						pBox->DFlagDelete();
					}

					pBox = pObjectNext;
				}
			}
		}
	}
}

//=========================================
//�S�Ă̕`�揈��
//=========================================
void CObject::DrawAll(Object_mode mode)
{
	// �J�������A�v���P�[�V��������擾
	CCamera *pCamera = nullptr;

	switch (mode)
	{
	case NORMAL_MODE:
		// �J�������A�v���P�[�V��������擾
		pCamera = CApplication::GetCamera();
		// �J�����̐ݒ�
		pCamera->Set();
		break;

	case RADAR_MODE:
		// ���[�_�[�p�J�������A�v���P�[�V��������擾
		pCamera = CApplication::GetRader();
		// �J�����̐ݒ�
		pCamera->Set2();
		break;

	case TITLE_MODE:
		// �^�C�g���p�J�������A�v���P�[�V��������擾
		pCamera = CApplication::GetTitleCamera();
		// �J�����̐ݒ�
		pCamera->Set();
		break;

	default:
		break;
	}


	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject *pBox = m_pTop[nCnt];

			while (pBox != nullptr)
			{
				if (pBox->m_type != OBJECT_RADAR && (pCamera->GetObjType() == NORMAL_MODE || pCamera->GetObjType() == TITLE_MODE))
				{
					//�`�揈��
					pBox->Draw();
				}
				else if (pBox->m_type == OBJECT_RADAR && pCamera->GetObjType() == RADAR_MODE)
				{// ���[�_�[�̕`��
					pBox->Draw();
				}
				pBox = pBox->m_pNext;
			}
		}
	}
}

//=========================================
//�S�Ă̔j������
//=========================================
void CObject::UninitAll()
{
	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
	/*	if (m_pTop[nCnt] != nullptr)
		{*/
			CObject *pDeleteBox = m_pTop[nCnt];

			while (pDeleteBox != nullptr)
			{
				CObject *pSaveBox = pDeleteBox->m_pNext;

				if (!pDeleteBox->m_DeathFlag)
				{
					pDeleteBox->Uninit();
				}

				pDeleteBox = pSaveBox;
			}
		//}
	}

	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		/*if (m_pTop[nCnt] != nullptr)
		{*/
			CObject *pBox = m_pTop[nCnt];

			while (pBox != nullptr)
			{
				CObject *pObjectNext = pBox->m_pNext;

				if (pBox->m_DeathFlag)
				{
					pBox->DFlagDelete();
				}
				else
				{
					assert(false);
				}

				pBox = pObjectNext;
			}

			m_pTop[nCnt] = nullptr;
			m_pCurrent[nCnt] = nullptr;
		//}
	}
}

//=========================================
// �������
//=========================================
void CObject::Release()
{
	if (!m_DeathFlag)
	{
		m_DeathFlag = true;
	}
}

//=========================================
// ���S�t���O���������鏈��
//=========================================
void CObject::DFlagDelete()
{
	//�擪�̃|�C���^�[��������擪�Ɏ��̃|�C���^�[����
	if (m_pTop[m_Priority] == this)
	{
		m_pTop[m_Priority] = m_pTop[m_Priority]->m_pNext;
	}
	//�Ō�̃|�C���^�[���������O�̃|�C���^�[����
	else if (m_pCurrent[m_Priority] == this)
	{
		m_pCurrent[m_Priority] = m_pCurrent[m_Priority]->m_pPrev;
	}
	// ���Ԃ̃|�C���^�[�������玟�̃|�C���^�[�Ɉ�O���A��O�̃|�C���^�[�Ɏ��̃|�C���^�[���B
	if (m_pPrev != nullptr)
	{// �O�̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g�Ɏ����̎��̃I�u�W�F�N�g��ݒ�
		m_pPrev->m_pNext = m_pNext;
	}
	if (m_pNext != nullptr)
	{// �����̎��̃I�u�W�F�N�g�Ɏ����̑O�̃I�u�W�F�N�g��ݒ�
		m_pNext->m_pPrev = m_pPrev;
	}

	delete this;
}

//==================================================================================
// ����̓����蔻��
// ����: �ڕW�̍��W �A ��̒��S �A �͈�(�p�x) �A���� , ����(�p�x)
//==================================================================================
bool CObject::SearchEye(D3DXVECTOR3 Vec1, D3DXVECTOR3 Vec2, float rangeRadian, float length, float FanRadian)
{
	D3DXVECTOR3 Vec1To2xz = Vec1 - Vec2;
	Vec1To2xz.y = 0.0f;

	// �x�N�g���̒����̎Z�o
	float vec_length = sqrtf((Vec1To2xz.x * Vec1To2xz.x) + (Vec1To2xz.z * Vec1To2xz.z));

	// �x�N�g���Ɛ�̒����̔�r
	if (length < vec_length)
	{
		// �������Ă��Ȃ�
		return false;
	}

	//��̕����x�N�g�������߂�
	D3DXVECTOR3 Fan_dir = D3DXVECTOR3(cosf(FanRadian + D3DX_PI * 0.5f), 0.0f, sinf(FanRadian - D3DX_PI * 0.5f));

	Vec1To2xz /= vec_length;

	// ���όv�Z
	float dot = Vec1To2xz.x * Fan_dir.x + Vec1To2xz.z * Fan_dir.z;

	// ��͈̔͂�cos�ɂ���
	float fan_cos = cosf(/*D3DXToRadian(*/rangeRadian / 4.0f/*)*/);

	if (dot > 0)
	{
		if (fan_cos > dot)
		{
			// �������ĂȂ�
			return false;
		}
	}

	////=========================================
	////xy�̌v�Z
	////=========================================
	//D3DXVECTOR3 Vec1To2xy = { Vec1.x - Vec2.x,Vec1.y - Vec2.y , 0.0f };

	//// �x�N�g���̒����̎Z�o
	//vec_length = sqrtf((Vec1To2xy.x * Vec1To2xy.x) + (Vec1To2xy.y * Vec1To2xy.y));

	//// �x�N�g���Ɛ�̒����̔�r
	//if (length < vec_length)
	//{
	//	// �������Ă��Ȃ�
	//	return false;
	//}

	////��̕����x�N�g�������߂�
	//direction_rad = ((FanDegree) * (D3DX_PI / 180.0f));
	//fan_dir = D3DXVECTOR3(cosf(direction_rad), sinf(direction_rad), 0.0f);

	//D3DXVec3Normalize(&Vec1To2xy, &Vec1To2xy);

	//// ���όv�Z
	//dot = Vec1To2xy.x * fan_dir.x + Vec1To2xy.y * fan_dir.y;

	//// ��͈̔͂�cos�ɂ���
	//fan_cos = cosf((rangeDegree / 2.0f) * (D3DX_PI / 180.0f));

	//if (fan_cos > dot)
	//{
	//	// �������ĂȂ�
	//	return false;
	//}

	return true;
}

//=========================================
// ���W�̐ݒ�
//=========================================
void CObject::SetPosition(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//=========================================
// HP���Ǘ�����
//=========================================
int CObject::ManageHP(int Value)
{
	m_HP += Value;

	return m_HP;
}

//===========================================================================
// �I�u�W�F�N�g�̓����蔻��
// ���� : �^�[�Q�b�g�̃I�u�W�F�N�g���A�����Ԃ����Ԃ��Ȃ���
//===========================================================================
bool CObject::Collision(CObject *Target, bool bExtrude)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posOld = GetPosOld();
	D3DXVECTOR3 size = GetSize();
	
	D3DXVECTOR3 posTarget = Target->GetPosition();
	D3DXVECTOR3 SizeTarget = Target->GetSize();

	D3DXVECTOR3 posDiss = pos - posTarget;
	float fDistance = sqrtf((posDiss.y * posDiss.y) + (posDiss.x * posDiss.x) + (posDiss.z * posDiss.z));

	if (fDistance >= 50.0f)
	{
		return false;
	}

	// ��������
	if ((pos.z - size.z) < (posTarget.z + SizeTarget.z)
		&& (pos.z + size.z) > (posTarget.z - SizeTarget.z)
		&& (pos.x - size.x) < (posTarget.x + SizeTarget.x)
		&& (pos.x + size.x) > (posTarget.x - SizeTarget.x)
		&& (pos.y - size.y) < (posTarget.y + SizeTarget.y)
		&& (pos.y + size.y) > (posTarget.y - SizeTarget.y))
	{
		bCollision = true;
	}

	// ���܂�Ă��܂��͂��ȃY������������l
	float fCollision = 1.0f;

	if ((pos.z - size.z) < (posTarget.z + SizeTarget.z)
		&& (pos.z + size.z) > (posTarget.z - SizeTarget.z)
		&& (pos.x - size.x) < (posTarget.x + SizeTarget.x)
		&& (pos.x + size.x) > (posTarget.x - SizeTarget.x))
	{// ���f�����ɂ���(XZ��)
		if ((posOld.y + size.y) <= (posTarget.y - SizeTarget.y)
			&& (pos.y + size.y) > (posTarget.y - SizeTarget.y))
		{
			if (bExtrude)
			{
				pos.y = posTarget.y - SizeTarget.y - size.y - fCollision;
			}
		}
		if ((posOld.y - size.y) >= (posTarget.y + SizeTarget.y)
			&& (pos.y - size.y) < (posTarget.y + SizeTarget.y))
		{
			if (bExtrude)
			{
				pos.y = posTarget.y + SizeTarget.y + size.y + fCollision;
			}
		}
	}

	if ((pos.y - size.y) < (posTarget.y + SizeTarget.y)
		&& (pos.y + size.y) > (posTarget.y - SizeTarget.y))
	{
		if ((pos.z - size.z) < (posTarget.z + SizeTarget.z)
			&& (pos.z + size.z) > (posTarget.z - SizeTarget.z))
		{// ���f�����ɂ���(Z��)
			if ((posOld.x + size.z) <= (posTarget.x - SizeTarget.x)
				&& (pos.x + size.z) > (posTarget.x - SizeTarget.x))
			{
				if (bExtrude)
				{
					pos.x = posTarget.x - SizeTarget.x - size.z - fCollision;
				}
			}
			if ((posOld.x - size.z) >= (posTarget.x + SizeTarget.x)
				&& (pos.x - size.z) < (posTarget.x + SizeTarget.x))
			{
				if (bExtrude)
				{
					pos.x = posTarget.x + SizeTarget.x + size.z + fCollision;
				}
			}
		}
		if ((pos.x - size.x) < (posTarget.x + SizeTarget.x)
			&& (pos.x + size.x) > (posTarget.x - SizeTarget.x))
		{// ���f�����ɂ���(X��)
			if ((posOld.z + size.z) <= (posTarget.z - SizeTarget.z)
				&& (pos.z + size.z) > (posTarget.z - SizeTarget.z))
			{
				if (bExtrude)
				{
					pos.z = posTarget.z - SizeTarget.z - size.z - fCollision;
				}
			}
			if ((posOld.z - size.z) >= (posTarget.z + SizeTarget.z)
				&& (pos.z - size.z) < (posTarget.z + SizeTarget.z))
			{
				if (bExtrude)
				{
					pos.z = posTarget.z + SizeTarget.z + size.z + fCollision;
				}
			}
		}
	}

	SetPosition(pos);

	return bCollision;
}

//=========================================
// 2�_����p�x�����߂�
//=========================================
D3DXVECTOR3 CObject::AtanRot(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 distance = pos1 - pos2;
	D3DXVECTOR3 AtanRot = {};

	// �O�����œG�̕������o��
	AtanRot.z = sqrtf((distance.x * distance.x) + (distance.z * distance.z));
	AtanRot.y = atan2f(distance.x, distance.z);
	AtanRot.x = atan2f(AtanRot.z, distance.y);

	return AtanRot;
}

//=========================================
// �p�x�̐��K������
// ���� : ���K���������p�x
//=========================================
D3DXVECTOR3 CObject::NormalizeRotXYZ(D3DXVECTOR3 Rot)
{
	D3DXVECTOR3 NormRot;

	NormRot.x = NormalizeRot(Rot.x);
	NormRot.y = NormalizeRot(Rot.y);
	NormRot.z = NormalizeRot(Rot.z);

	return NormRot;
}

float CObject::NormalizeRot(float fRot)
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

//===========================================================
// �s��ϊ����鏈��
// �T�v : �󂯎����pos��mtx�ōs��v�Z���鏈��
// ��Ȏg�p : ���W���󂯎������
// ���� : ���炷���W�̑傫���A�N�H�[�^�j�I���A�ڕW���W
//============================================================
D3DXVECTOR3 CObject::MtxPos(D3DXVECTOR3 pos, D3DXQUATERNION qua, D3DXVECTOR3 TargetPos)
{
	// ���������ĕK�v�H���[���h�}�g���b�N�X
	D3DXMATRIX WorldMtx;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxBullet, mtxTrans, mtxQua;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMtx);

	// �e�̍��W������������
	D3DXMatrixTranslation(&mtxBullet, pos.x, pos.y, pos.z);			// �s��ړ��֐�
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &mtxBullet);			// �s��|���Z�֐�

																	// �N�H�[�^�j�I��(��])�̔��f
	D3DXMatrixRotationQuaternion(&mtxQua, &qua);					// �N�I�[�^�j�I���ɂ��s���]
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &mtxQua);				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

																	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, TargetPos.x, TargetPos.y, TargetPos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &mtxTrans);							// �s��|���Z�֐�

																					// �s�񂩂���W�����o��
	D3DXVECTOR3 MtxPos = D3DXVECTOR3(WorldMtx._41, WorldMtx._42, WorldMtx._43);

	return MtxPos;
}

//===========================================================
// �s��ϊ����鏈��
// �T�v : �󂯎����pos��mtx�ōs��v�Z���鏈��
// ��Ȏg�p : ���W���󂯎������
// ���� : ���炷���W�̑傫���ARot�A�ڕW���W
//============================================================
D3DXVECTOR3 CObject::MtxPosRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 TargetPos)
{
	// ���������ĕK�v�H���[���h�}�g���b�N�X
	D3DXMATRIX WorldMtx;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxBullet, mtxTrans, mtxRot;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMtx);

	// �e�̍��W������������
	D3DXMatrixTranslation(&mtxBullet, pos.x, pos.y, pos.z);			// �s��ړ��֐�
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &mtxBullet);			// �s��|���Z�֐�

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);			// �s���]�֐�
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &mtxRot);						// �s��|���Z�֐� 

																	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, TargetPos.x, TargetPos.y, TargetPos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&WorldMtx, &WorldMtx, &mtxTrans);							// �s��|���Z�֐�

																					// �s�񂩂���W�����o��
	D3DXVECTOR3 MtxPos = D3DXVECTOR3(WorldMtx._41, WorldMtx._42, WorldMtx._43);

	return MtxPos;
}