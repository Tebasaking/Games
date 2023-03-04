//=========================================
//
//	explosion.h
//	Author:�y���m��
//
//=========================================
#ifndef _EXPLOSION_H_		//���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "billboard.h"

class CExplosion :public CBillboard
{
public:
	CExplosion();			//�R���X�g���N�^
	virtual ~CExplosion() override;			//�f�X�g���N�^

												//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CExplosion* Create(const D3DXVECTOR3 &pos, const D3DXQUATERNION &quaternion);

private:
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_pos;				// ���W
	int m_size;						// �T�C�Y
	D3DXQUATERNION m_quaternion;	// �N�H�[�^�j�I��
	static const int ANIM_SPEED;
	static const int ANIM_MAX;
	int nAnimCount;
	int nAnimNum;
};

#endif