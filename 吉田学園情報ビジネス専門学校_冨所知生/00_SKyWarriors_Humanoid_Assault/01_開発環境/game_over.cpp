//=========================================
// game.cpp
// Author: �y���m��
//=========================================
#include "application.h"
#include "game_over.h"
#include "player3D.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//=========================================
// �R���X�g���N�^
//=========================================
CGameOver::CGameOver()
{
}

//=========================================
// �f�X�g���N�^
//=========================================
CGameOver::~CGameOver()
{
}

//=========================================
// ������ 
//=========================================
HRESULT CGameOver::Init(const D3DXVECTOR3 &pos)
{
	// �I�u�W�F�N�g�̐���
	CObject2D *pObject = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0);

	// �I�u�W�F�N�g�̃T�C�Y�ݒ�
	pObject->SetScale(D3DXVECTOR3((float)SCREEN_HEIGHT, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

	// �I�u�W�F�N�g�̃e�N�X�`���ݒ�
	pObject->SetTexture(CTexture::TEXTURE_GAME_OVER);

	//�T�E���h����
	CSound::PlaySound(CSound::SOUND_LABEL_BGM_LOSE);

	return S_OK;
}

//=========================================
// �X�V����
//=========================================
void CGameOver::Update()
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
void CGameOver::Uninit()
{
	// BGM�̏I������
	CSound::StopSound();

	// �������
	Release();
}