//=========================================
//
//	���[�_�[�̏���(3D [�r���{�[�h])
//	Author:�y���m��
//
//=========================================
#include "application.h"
#include "calculation.h"
#include "texture.h"
#include "explosion.h"
#include "motion_model3D.h"
#include "Object2D.h"
#include "radar.h"
#include "camera_player.h"
#include "debug_proc.h"

//=========================================
//�R���X�g���N�^
//=========================================
CRadar::CRadar(int nPriority) : CBillboard(nPriority)
{
	SetObjectType(OBJECT_RADAR);
}

//=========================================
//�f�X�g���N�^
//=========================================
CRadar::~CRadar()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CRadar::Init(const D3DXVECTOR3 &pos)
{
	if (m_type != RADAR_PLAYER)
	{// �r���{�[�h��OFF�ɂ���
		SetBill(false);
	}

	CBillboard::Init(pos);
	m_pos = pos;

	if (CApplication::GetMode() == CApplication::MODE_GAME)
	{
		m_pBackGround = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f * 0.5f - 15.0f, SCREEN_HEIGHT - 150, 0.0f), 0);
		m_pBackGround->SetTexture(CTexture::TEXTURE_FRAME);
		m_pBackGround->SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.25f * 0.5f * 0.75f, SCREEN_HEIGHT * 0.5f * 0.5f * 0.75f, 0.0f));
		m_pBackGround->SetObjectType(OBJECT_RADAR);

		switch (m_type)
		{
		case RADAR_MAP:
			// �e�N�X�`���̐ݒ�
			CBillboard::SetTexture(CTexture::TEXTURE_RADAR_MAP);
			//�T�C�Y�̐ݒ�
			CBillboard::SetSize(D3DXVECTOR3(1000000.0f, 1000000.0f, 0.0f));
			// COLOR�ݒ�
			SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			break;

		case RADAR_PLAYER:
			// �e�N�X�`���̐ݒ�
			CBillboard::SetTexture(CTexture::TEXTURE_ENEMY_FLY);
			//�T�C�Y�̐ݒ�
			CBillboard::SetSize(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
			// COLOR�ݒ�
			CBillboard::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		case RADAR_ENEMY:
			// �e�N�X�`���̐ݒ�
			CBillboard::SetTexture(CTexture::TEXTURE_ENEMY_TANK);
			//�T�C�Y�̐ݒ�
			CBillboard::SetSize(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
			// COLOR�ݒ�
			CBillboard::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		case RADAR_MISSILE:
			// �e�N�X�`���̐ݒ�
			CBillboard::SetTexture(CTexture::TEXTURE_MISSILE_MARK);
			//�T�C�Y�̐ݒ�
			CBillboard::SetSize(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
			// COLOR�ݒ�
			CBillboard::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
	}

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CRadar::Update()
{
	D3DXCOLOR col = GetColor();

	if (m_type != RADAR_MAP)
	{
		// �ڕW�̍��W�ݒ�
		D3DXVECTOR3 TargetPos = m_pObject->GetPosition();

		// �I�u�W�F�N�g�̐ݒ�
		m_pos = D3DXVECTOR3(TargetPos.x, 1090.0f, TargetPos.z);

		// ���W�̐ݒ�
		SetPosition(m_pos);
	}

	SetColor(col);

	CBillboard::Update();
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CRadar::Uninit()
{
	CBillboard::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CRadar::Draw()
{
	CBillboard::Draw();
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CRadar* CRadar::Create(const D3DXVECTOR3 &pos, CObject *object, RADAR_TYPE type)
{
	CRadar* pCRadar = nullptr;

	pCRadar = new CRadar(LAYER_FIVE);

	if (pCRadar != nullptr)
	{
		pCRadar->SetType(type);
		pCRadar->Init(pos);
		pCRadar->SetObject(object);
	}

	return pCRadar;
}
