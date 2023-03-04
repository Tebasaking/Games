//=========================================
//
//	�~�T�C���A���[�g�̏���
//	Author:�y���m��
//
//=========================================
#include "missile_alert.h"
#include "missile_alert_manager.h"
#include "camera.h"
#include "application.h"
#include "debug_proc.h"
#include "bullet3D.h"
#include "game.h"
#include "playerUI.h"
#include "sound.h"

D3DXVECTOR3 CAlert::m_TargetPos = {};
//=========================================
//�R���X�g���N�^
//=========================================
CAlert::CAlert()
{
	SetObjectType(OBJECT_ALERT);
}

//=========================================
//�f�X�g���N�^
//=========================================
CAlert::~CAlert()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CAlert::Init(const D3DXVECTOR3 &pos)
{
	m_bCheck = false;

	//����������
	CObject2D::Init(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f,0.0f));

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_UI_ALERT);

	//�T�C�Y�̐ݒ�
	CObject2D::SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// �^�C�v�ݒ�
	//SetObjectType(OBJECT_TARGET);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CAlert::Update()
{
	// �S�ẴA���[�g����A���[�g���N�����Ă�����̂����������AbCheck��true�ɂ���B
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CObject *object = CObject::GetObjectTop(nCnt);

		//�v���C���[�̍��W���擾
		while (object)
		{
			if (object != nullptr)
			{
				EObjType ObjType = object->GetObjectType();

				if (ObjType == OBJECT_ALERT_MANAGAER)
				{
					CMissileAlertManager *pAlert = dynamic_cast<CMissileAlertManager*> (object);

					if (pAlert->GetAlert())
					{
						m_bCheck = true;
						break;
					}
					else
					{
						m_bCheck = false;
					}
				}
			}
			object = object->GetObjectNext();
		}

		if (m_bCheck)
		{
			break;
		}
	}

	if (m_bCheck)
	{
		m_SECnt++;

		if (m_SECnt % 60 == 0)
		{
			CSound::PlaySound(CSound::SOUND_SE_LOCK_ON);
		}

		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	//CDebugProc::Print("missile�̍��W x %.1f y ,%.1f,z %.1f \n", GetTest().x, GetTest().y, GetTest().z);
	// �J�����̎��_
	//CDebugProc::Print("�^�[�Q�b�g�̃T�C�Y %f \n", m_Size);
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CAlert::Uninit()
{
	m_bCheck = false;

	// �I������
	CObject2D::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CAlert::Draw()
{
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
CAlert* CAlert::Create(const D3DXVECTOR3 &pos)
{
	CAlert* pCAlert = nullptr;

	pCAlert = new CAlert;

	if (pCAlert != nullptr)
	{
		pCAlert->Init(pos);
	}

	return pCAlert;
}