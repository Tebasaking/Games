//=========================================
//
//	explosion.h
//	Author:�y���m��
//
//=========================================
#ifndef _MISSILE_LOCUS_H_		//���̃}�N����`������ĂȂ�������
#define _MISSILE_LOCUS_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "billboard.h"

class CMissile_Locus :public CBillboard
{
public:
	CMissile_Locus();			//�R���X�g���N�^
	virtual ~CMissile_Locus() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CMissile_Locus* Create(const D3DXVECTOR3 &pos, CObject *object);

private:
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_pos;				// ���W
	D3DXCOLOR	m_col;				// �F
	int m_size;						// �T�C�Y
	D3DXQUATERNION m_quaternion;	// �N�H�[�^�j�I��

	static const int		ANIM_SPEED;
	static const int		ANIM_MAX;
	int						nAnimCount;
	int						nAnimNum;
	int						nAnimNumY;
	float					m_RandAlfa;		// ���l��X(�����_��)���炷
};

#endif