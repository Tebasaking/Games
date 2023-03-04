//=========================================
//
//	�v���C���[�̏���
//	Author:�y���m��
//
//=========================================
#include "missile_alert_manager.h"
#include "application.h"
#include "bullet3D.h"

//=========================================
//�R���X�g���N�^
//=========================================
CMissileAlertManager::CMissileAlertManager()
{
	SetObjectType(OBJECT_ALERT_MANAGAER);
}

//=========================================
//�f�X�g���N�^
//=========================================
CMissileAlertManager::~CMissileAlertManager()
{
}

//=========================================
// �X�V����
//=========================================
void CMissileAlertManager::Update()
{
	// ��O����
	CBullet3D *pBullet = (CBullet3D*)pObject;

	if (pBullet != nullptr)
	{
		if (pBullet->GetAlert())
		{
			m_bAlert = false;
		}
		else
		{
			m_bAlert = true;
		}
	}
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CMissileAlertManager* CMissileAlertManager::Create(CObject *Obj)
{
	CMissileAlertManager* pAlertManager = nullptr;

	pAlertManager = new CMissileAlertManager;

	if (pAlertManager != nullptr)
	{
		pAlertManager->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));
		pAlertManager->SetObject(Obj);
	}

	return pAlertManager;
}