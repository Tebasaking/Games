//=============================================================================
//
// �t�F�[�h����
// Author:�y���m��
//
//=============================================================================
#include "application.h"
#include "fade.h"
#include "mode.h"
#include "render.h"

//�ÓI�����o�ϐ�
CApplication::MODE CFade::m_ModeNext = {};	//���̉��(���[�h)
CFade::FADE CFade::m_pFade = {};			//�t�F�[�h�̏��	
D3DXCOLOR CFade::m_Color = {};				//�J���[
//======================================================
//�R���X�g���N�^
//======================================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CFade::~CFade()
{
}

//======================================================
//����������
//======================================================
void CFade::Init(CApplication::MODE modeNext)
{
	CObject2D::Init(D3DXVECTOR3(0.0f,0.0f,0.0f));
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetScale(D3DXVECTOR3(1980.0f,1980.0f,0.0f));
	SetColor(m_Color);

	//������
	m_pFade = FADE_IN;		//�t�F�[�h�C����Ԃ�
	m_ModeNext = modeNext;
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

//======================================================
//�I������
//======================================================
void CFade::Uninit(void)
{
	//�������
 	CObject2D::Uninit();
}

//======================================================
//����������
//======================================================
void CFade::Update(void)
{
	CObject2D::Update();

	if (m_pFade != FADE_NONE)
	{
		if (m_pFade == FADE_IN)
		{//�t�F�[�h�C�����
			m_Color.a -= 0.07f;		//�|���S���𓧖��ɂ��Ă���

			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				m_pFade = FADE_NONE;		//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_pFade == FADE_OUT)
		{ //�t�F�[�h�A�E�g���
			m_Color.a += 0.07f;		//�|���S����s�����ɂ��Ă���

			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				m_pFade = FADE_IN;		//�t�F�[�h�C����Ԃ�

				//���[�h�ݒ�(���̉�ʂɈڍs)
				CApplication::SetNextMode(m_ModeNext);
			}
		}
		SetColor(m_Color);
	}
}

//======================================================
//����������
//======================================================
void CFade::SetFade(CApplication::MODE modeNext)
{
	if (m_pFade == FADE_OUT)
	{
		return;
	}

	m_pFade = FADE_OUT;								//�t�F�[�h�A�E�g��Ԃ�
	m_ModeNext = modeNext;							//���̉��(���[�h)��ݒ�
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���
}

//======================================================
//����������
//======================================================
CFade * CFade::Create(CApplication::MODE modeNext)
{
	//���I�m��
	CFade *pFade = new CFade;

	if (pFade != nullptr)
	{
		//������
		pFade->Init(modeNext);
	}

	return pFade;
}

//=========================================
// �`�揈��
//=========================================
void CFade::Draw(void)
{
	CObject2D::Draw();
}