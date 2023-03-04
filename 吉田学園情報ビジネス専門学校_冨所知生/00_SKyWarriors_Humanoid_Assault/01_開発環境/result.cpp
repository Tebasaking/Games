//=========================================
// game.cpp
// Author: �y���m��
//=========================================
#include "application.h"
#include "result.h"
#include "player3D.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//=========================================
// �R���X�g���N�^
//=========================================
CResult::CResult()
{
}

//=========================================
// �f�X�g���N�^
//=========================================
CResult::~CResult()
{
}

//=========================================
// ������ 
//=========================================
HRESULT CResult::Init(const D3DXVECTOR3 &pos)
{
	// �I�u�W�F�N�g�̐���
	CObject2D *pObject = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0);

	// �I�u�W�F�N�g�̃T�C�Y�ݒ�
	pObject->SetScale(D3DXVECTOR3((float)SCREEN_HEIGHT,(float)SCREEN_HEIGHT * 0.5f,0.0f));

	// �I�u�W�F�N�g�̃e�N�X�`���ݒ�
	pObject->SetTexture(CTexture::TEXTURE_RANKING);

	//�����L���O����
	m_pRanking = CRanking::Create();

	//�T�E���h����
	CSound::PlaySound(CSound::SOUND_LABEL_BGM_RANKING);

	return S_OK;
}
//=========================================
// �X�V����
//=========================================
void CResult::Update()
{
	CInput *pKeyboard = CInput::GetKey();

	// ���[�h�ύX
	if (pKeyboard->Trigger(DIK_RETURN) || pKeyboard->Trigger(JOYPAD_A))
	{
		//���[�h�̐ݒ�
		CFade::SetFade(CApplication::MODE_TITLE);
	}
	//---------------------
	// �����L���O�̍X�V
	//---------------------
	if (m_pRanking != nullptr)
	{//�����L���O��null����Ȃ��Ȃ� 
	 //�X�V
		m_pRanking->Update();
	}

}

//=========================================
// �I������
//=========================================
void CResult::Uninit()
{
	//---------------------
	// �����L���O�I��
	//---------------------
	if (m_pRanking != nullptr)
	{
		//�I��
		m_pRanking->Uninit();

		//����
		delete m_pRanking;
		m_pRanking = nullptr;
	}

	// �T�E���h�̏I��
	CSound::StopSound();

	Release();
}