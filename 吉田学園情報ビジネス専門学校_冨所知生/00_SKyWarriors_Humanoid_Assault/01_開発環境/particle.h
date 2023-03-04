//=============================================================================
//
// �p�[�e�B�N���N���X(particle.h)
// Author : �������l
// �T�v : �p�[�e�B�N���������s��
//
//=============================================================================
#ifndef _PARTICLE_H_		// ���̃}�N����`������ĂȂ�������
#define _PARTICLE_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=============================================================================
// �p�[�e�B�N���N���X
// Author : �������l
// �T�v : �p�[�e�B�N���������s���N���X
//=============================================================================
class CParticle : public CObject
{
private:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------

public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CParticle *Create();		// �p�[�e�B�N���̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CParticle(int nPriority = CObject::LAYER_TWO);
	~CParticle() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(const D3DXVECTOR3 &pos) override;														// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��

	void SetColor(const D3DXCOLOR &col) { m_color = col; }							// �F�̐ݒ�			
	// �����͈͂̐ݒ�
	void SetPopRange(const D3DXVECTOR3 popRange) { m_popRange = popRange; }	
	void SetMoveVec(const D3DXVECTOR3 moveVec) { m_moveVec = moveVec; }				// �ړ������̐ݒ�
	void SetSpeed(const float fSpeed) { m_fSpeed = fSpeed; }						// ���x�̐ݒ�
	// �G�t�F�N�g�̎����̐ݒ�
	void SetEffectLife(const int nEffectLife) { m_nEffectLife = nEffectLife; }
	// �����̐ݒ�
	void SetLife(const int nLife) { m_nLife = nLife; }
	// �ʒu�t���[���o���G�t�F�N�g���̃Z�b�^�[
	void SetMaxEffect(const int nMaxEffect) { m_nMaxEffect = nMaxEffect; }		

	float FloatRandam(float fMax, float fMin);

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void SetEffect();

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_posOld;			// �ߋ��̈ʒu
	D3DXVECTOR3			m_rot;				// ����
	D3DXVECTOR3			m_popRange;			// �����͈�
	D3DXVECTOR3			m_size;				// �傫��
	D3DXVECTOR3			m_moveVec;			// �ړ�����
	D3DXCOLOR			m_color;			// �F
	D3DXQUATERNION		m_quaternion;		// �N�H�[�^�j�I��
	float				m_fSpeed;			// ���x
	int					m_nEffectLife;		// �G�t�F�N�g�̎���
	int					m_nLife;			// ����
	int					m_nMaxEffect;		// �ʒu�t���[���o���G�t�F�N�g��
};

#endif


