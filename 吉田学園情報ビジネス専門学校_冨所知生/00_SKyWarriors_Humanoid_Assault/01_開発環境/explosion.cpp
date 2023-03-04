//=========================================
//
//	�����̏���(3D [�r���{�[�h])
//	Author:�y���m��
//
//=========================================
#include "explosion.h"
#include "application.h"
#include "texture.h"
#include "calculation.h"
#include "explosion.h"
#include "sound.h"

const int CExplosion::ANIM_SPEED = 10;
const int CExplosion::ANIM_MAX = 7;
//=========================================
//�R���X�g���N�^
//=========================================
CExplosion::CExplosion()
{
	nAnimCount = 0;
	nAnimNum = 0;
}

//=========================================
//�f�X�g���N�^
//=========================================
CExplosion::~CExplosion()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CExplosion::Init(const D3DXVECTOR3 &pos)
{
	CBillboard::Init(pos);

	// ���W
	m_pos = pos;

	//�T�C�Y�̐ݒ�
	CBillboard::SetSize(D3DXVECTOR3(150.0f,150.0f,0.0f));

	// �e�N�X�`���̐ݒ�
	CBillboard::SetTexture(CTexture::TEXTURE_EXPLOSION2);

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �̗͂̐ݒ�
	SetHP(100);

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CExplosion::Update()
{
	int nLife = GetHP();

	nLife = ManageHP(-1);

	SetPosition(m_pos);

	if (nLife <= 0)
	{
		CExplosion::Uninit();
	}

	int Size = (float)GetScale();

	nAnimCount++;

	CBillboard::SetAnim((float)nAnimNum, ANIM_MAX,1,1);

	// �A�j���[�V��������
	if (nAnimCount >= ANIM_SPEED)
	{
		nAnimNum++;
		nAnimCount = 0;

		if (nAnimNum >= ANIM_MAX)
		{
			nAnimNum = 0;
			CExplosion::Uninit();
		}
	}
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CExplosion::Uninit()
{
	CBillboard::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CExplosion::Draw()
{
	CBillboard::Draw();
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CExplosion* CExplosion::Create(const D3DXVECTOR3 &pos, const D3DXQUATERNION &quaternion)
{
	int nNumCreate = m_nNumAll;

	CExplosion* pExplosion = nullptr;

	pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		pExplosion->Init(pos);
		pExplosion->m_quaternion = quaternion;
		CSound::PlaySound(CSound::SOUND_SE_EXPLOSION);
	}

	return pExplosion;
}