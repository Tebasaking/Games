//=========================================
//
//	effect.h
//	Author:�y���m��
//
//=========================================
#ifndef _EFFECT_H_		//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "billboard.h"

class CTexture;
class CEffect :public CBillboard
{
public:
	enum RENDER_MODE
	{
		MODE_NORMAL = 0,		// �ʏ�
		MODE_ADD,				// ���Z����
		MODE_SUB,				// ���Z����
		MAX_MODE,				// �v�Z���@�̍ő吔
	};

	CEffect();			//�R���X�g���N�^
	virtual ~CEffect() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CEffect* Create(const D3DXVECTOR3 &pos,int ANIM_SPEED, int ANIM_MAX, CTexture::TEXTURE tex);
	void SetMoveVec(const D3DXVECTOR3 moveVec) { m_moveVec = moveVec; }					// �ړ������̐ݒ�
	D3DXVECTOR3 GetMoveVec() { return m_moveVec; }										// �ړ������̎擾
	void SetSpeed(const float fSpeed) { m_fSpeed = fSpeed; }							// ���x�̐ݒ�
	void SetRenderMode(const RENDER_MODE renderMode) { m_renderMode = renderMode; }		// �����_�[�X�e�[�g�̌v�Z���@�̐ݒ�
	void SetLife(const int nLife) { m_nLife = nLife; }
	void SetTex(CTexture::TEXTURE tex) { m_tex = tex; }
	void DecreaseLife(void);

private:
	RENDER_MODE		m_renderMode;		// �����_�[�X�e�[�g�̌v�Z���@
	CTexture::TEXTURE m_tex;			// �e�N�X�`�����
	D3DXVECTOR3		m_move;				// �ړ���
	D3DXVECTOR3		m_moveVec;			// �ړ�����
	D3DXVECTOR3		m_subSize;			// �傫���̌�����
	D3DXVECTOR3		m_pos;				// ���W
	D3DXCOLOR		m_col;				// �F
	D3DXQUATERNION	m_quaternion;		// �N�H�[�^�j�I��

	int		m_size;						// �T�C�Y
	int		m_ANIM_SPEED;
	int		m_ANIM_MAX;
	int		nAnimCount;
	int		nAnimNum;
	int		m_nLife;					// ����
	float	m_RandAlfa;					// ���l��X(�����_��)���炷
	float	m_fSpeed;					// ���x
	float	m_fSubAlpha;				// �A���t�@�l�̌�����
};

#endif