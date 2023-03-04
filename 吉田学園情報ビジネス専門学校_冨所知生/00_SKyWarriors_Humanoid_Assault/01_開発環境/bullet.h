//=========================================
//
//	bullet3D.h
//	Author:�y���m��
//
//=========================================
#ifndef _BULLET_H_		//���̃}�N����`������ĂȂ�������
#define _BULLET_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "billboard.h"
#include "camera_player.h"

class CCamera;

class CBullet :public CBillboard
{
public:
	CBullet();								// �R���X�g���N�^
	virtual ~CBullet() override;			// �f�X�g���N�^

	// ����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// ���b�N�I������
	D3DXVECTOR3 LockOn(D3DXMATRIX *mtxWorld);
	// �N���G�C�g����
	static CBullet* Create(const D3DXVECTOR3 &pos, const D3DXQUATERNION &quaternion, CObject *object);
	// �I�u�W�F�N�g�̐ݒ�
	void SetTargetObj(CObject *obj) { m_pTargetObj = obj; }

private:
	D3DXVECTOR3						m_pos;				// ���W
	D3DXVECTOR3						m_posOld;			// ��O�̍��W
	D3DXVECTOR3						m_move;				// �ړ���
	D3DXVECTOR3						m_TargetPos;		// �ڕW�̒l
	D3DXQUATERNION					m_quaternion;		// �N�H�[�^�j�I��
	CObject*						m_pTargetObj;		// �^�[�Q�b�g�̃I�u�W�F�N�g
	CCameraPlayer::CAMERA_TYPE		Camera_Type;		// �J�����̃^�C�v
};

#endif