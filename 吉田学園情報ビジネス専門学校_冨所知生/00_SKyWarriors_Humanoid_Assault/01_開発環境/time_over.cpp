//=========================================
// game.cpp
// Author: �y���m��
//=========================================
#include "application.h"
#include "time_over.h"
#include "player3D.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//=========================================
// �R���X�g���N�^
//=========================================
CTimeOver::CTimeOver()
{
}

//=========================================
// �f�X�g���N�^
//=========================================
CTimeOver::~CTimeOver()
{
}

//=========================================
// ������ 
//=========================================
HRESULT CTimeOver::Init(const D3DXVECTOR3 &pos)
{
	//�T�E���h����
	CSound::PlaySound(CSound::SOUND_LABEL_BGM_LOSE);

	// �I�u�W�F�N�g�̐���
	CObject2D *pObject = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0);

	// �I�u�W�F�N�g�̃T�C�Y�ݒ�
	pObject->SetScale(D3DXVECTOR3((float)SCREEN_HEIGHT, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

	// �I�u�W�F�N�g�̃e�N�X�`���ݒ�
	pObject->SetTexture(CTexture::TEXTURE_TIME_OVER);

	return S_OK;
}
//=========================================
// �X�V����
//=========================================
void CTimeOver::Update()
{
	CInput *pKeyboard = CInput::GetKey();

	// ���[�h�ύX
	if (pKeyboard->Trigger(DIK_RETURN) || pKeyboard->Trigger(JOYPAD_A))
	{
		//���[�h�̐ݒ�
		CFade::SetFade(CApplication::MODE_RESULT);
	}

}

//=========================================
// �I������
//=========================================
void CTimeOver::Uninit()
{
	Release();

	CSound::StopSound();
}