//=============================================================================
//
// �p�[�e�B�N���N���X(particle.h)
// Author : �������l
// �T�v : �p�[�e�B�N���������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <time.h>
#include "radar.h"
#include "particle.h"
#include "effect.h"
#include "render.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �X�R�A�𐶐�����
//=============================================================================
CParticle *CParticle::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CParticle *pParticle = nullptr;

	pParticle = new CParticle;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pParticle != nullptr);

	// ���l�̏�����
	pParticle->Init(D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �^�������̏�����
	srand((unsigned int)time(NULL));

	// �C���X�^���X��Ԃ�
	return pParticle;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	SetObjectType(OBJECT_EFFECT);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ߋ��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �傫��
	m_popRange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����͈�
	m_moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ�����
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_fSpeed = 0.0f;									// ���x
	m_nLife = 0;										// ����
	m_nMaxEffect = 0;									// �ʒu�t���[���o���G�t�F�N�g��
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CParticle::~CParticle()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CParticle::Init(const D3DXVECTOR3 &pos)
{
	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �傫���̐ݒ�
	m_size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);

	// �ʒu�t���[���o���G�t�F�N�g��
	m_nMaxEffect = 1;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CParticle::Uninit()
{
	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CParticle::Update()
{
	m_nLife--;

	SetEffect();

	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CParticle::Draw()
{

}

//=============================================================================
// �G�t�F�N�g�̐���
// Author : �������l
// �T�v : �G�t�F�N�g�̐���
//=============================================================================
void CParticle::SetEffect()
{
	// �ϐ��錾
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ�����
	float fSize = 0;								// �傫��
	float fSpeed = 0.0f;									// ���x
	int nEffectLife = 0;									// ����
	m_size = GetSize();
	m_pos = GetPosition();
	m_quaternion = GetQuaternion();

	for (int nCntEffect = 0; nCntEffect < m_nMaxEffect; nCntEffect++)
	{// ���l�̎Z�o
		pos.x = m_pos.x + (float)(-(int)(m_popRange.x * 0.5f) + rand() % ((int)(m_popRange.x) + 1));
		pos.y = m_pos.y + (float)(-(int)(m_popRange.y) + rand() % ((int)(m_popRange.y) + 1));
		pos.z = m_pos.z + (float)(-(int)(m_popRange.z * 0.5f) + rand() % ((int)(m_popRange.z) + 1));
		
		fSize = (float)(rand() % ((int)(sqrtf((m_size.x * m_size.x) + (m_size.y * m_size.y)) * 50.0f) + 1)) * 0.01f;
		
		moveVec.x = (((int)(m_moveVec.x * 100.0f) * 0.5f) - (rand() % ((int)(m_moveVec.x * 100.0f) + 1))) * 0.01f;
		moveVec.y = (((int)(m_moveVec.y * 100.0f) * 0.5f) - (rand() % ((int)(m_moveVec.y * 100.0f) + 1))) * 0.01f;
		moveVec.x = NormalizeRot(moveVec.x);
		moveVec.y = NormalizeRot(moveVec.y);
		nEffectLife = rand() % (m_nEffectLife + 1) + 1;
		fSpeed = FloatRandam(m_fSpeed,1.0f);

		CEffect *pEffect = CEffect::Create(pos,0,0,CTexture::TEXTURE_PARTIClE);
		pEffect->SetPosition(pos);
		pEffect->SetSize(D3DXVECTOR3(fSize, fSize, 0.0f));
		pEffect->SetMoveVec(moveVec);
		pEffect->SetLife(nEffectLife);
		pEffect->SetSpeed(fSpeed);
		pEffect->SetRenderMode(CEffect::MODE_ADD);
		pEffect->SetColor(m_color);
		pEffect->SetTex(CTexture::TEXTURE_PARTIClE);
		pEffect->SetQuaternion(m_quaternion);
	}
}

//---------------------------------------------------------------------------
// �����_�̃����_��
//---------------------------------------------------------------------------
float CParticle::FloatRandam(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}
