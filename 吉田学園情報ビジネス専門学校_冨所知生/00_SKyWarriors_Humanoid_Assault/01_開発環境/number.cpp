//========================================================
//�X�R�A��ʂ̏���
//========================================================
#include "number.h"
#include "input.h"
#include "score.h"

#define MAX_NUMBER (8)			//�X�R�A�Ɏg������

//======================================================
//�R���X�g���N�^
//======================================================
CNumber::CNumber(int nPriority)
{
	//SetType(OBJTYPE_MODE);
}

//=========================================
//�f�X�g���N�^
//=========================================
CNumber::~CNumber()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CNumber::Init(const D3DXVECTOR3 &pos)
{
	CObject2D::Init(pos);

	//�T�C�Y�̐ݒ�
	CObject2D::SetScale(D3DXVECTOR3(50.0f,50.0f,0.0f));

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CNumber::Update()
{
	//D3DXVECTOR3 pos;
	//pos = GetPosition();
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CNumber::Uninit()
{
	//�������
	CObject2D::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CNumber* CNumber::Create(const D3DXVECTOR3 &pos)
{
	int nNumCreate = m_nNumAll;

	CNumber* pCNumber = nullptr;

	pCNumber = new CNumber();

	if (pCNumber != nullptr)
	{
		pCNumber->Init(pos);
	}

	return pCNumber;
}

//========================================================
//�X�R�A�̐ݒ菈��
//========================================================
void CNumber::Set(int nDigits)
{
	SetAnim(nDigits,12);
}
