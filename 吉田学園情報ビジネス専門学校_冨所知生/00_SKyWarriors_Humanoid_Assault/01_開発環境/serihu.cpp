//========================================================
//�X�R�A��ʂ̏���
//========================================================
#include "input.h"
#include "serihu.h"

//======================================================
//�R���X�g���N�^
//======================================================
CSerihu::CSerihu(int nPriority)
{
	//SetType(OBJTYPE_MODE);
}

//=========================================
//�f�X�g���N�^
//=========================================
CSerihu::~CSerihu()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CSerihu::Init(const D3DXVECTOR3 &pos)
{
	CObject2D::Init(pos);

	//�T�C�Y�̐ݒ�
	CObject2D::SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CSerihu::Update()
{
	if (m_type != STOP)
	{
		m_Cnt++;

		if (m_Cnt >= 120)
		{
			Uninit();
		}
	}
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CSerihu::Uninit()
{
	//�������
	CObject2D::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CSerihu::Draw()
{
	CObject2D::Draw();
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CSerihu* CSerihu::Create(const TYPE type)
{
	int nNumCreate = m_nNumAll;

	CSerihu* pCSerihu = nullptr;

	pCSerihu = new CSerihu();

	if (pCSerihu != nullptr)
	{
		pCSerihu->Init(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pCSerihu->SetType(type);
	}

	return pCSerihu;
}

//========================================================
//�X�R�A�̐ݒ菈��
//========================================================
void CSerihu::SetType(TYPE type)
{
	m_type = type;
	int nRandom = rand() % 2 + 1;

	switch (type)
	{
	case NONE:
		break;

	case STOP:
		// �e�N�X�`���̐ݒ�
		CObject2D::SetTexture(CTexture::TEXTURE_STOP);
		break;

	case SHOUT_DOWN:
		if (nRandom == 1)
		{
			// �e�N�X�`���̐ݒ�
			CObject2D::SetTexture(CTexture::TEXTURE_SERIHU_GEKITUI_01);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			CObject2D::SetTexture(CTexture::TEXTURE_SERIHU_GEKITUI_02);
		}
		break;

	case TIME_LIMIT:
		// �e�N�X�`���̐ݒ�
		CObject2D::SetTexture(CTexture::TEXTURE_SERIHU_TIME_LIMIT_30);
		break;
	}
}
