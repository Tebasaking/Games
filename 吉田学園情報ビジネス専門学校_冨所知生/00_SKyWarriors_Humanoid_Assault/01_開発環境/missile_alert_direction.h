//=========================================
//
//	missile_alert.h
//	Author:�y���m��
//
//=========================================
#ifndef _ALERT_DIRECTION_H_		//���̃}�N����`������ĂȂ�������
#define _ALERT_DIRECTION_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"

class CAlert_Direction : public CObject2D
{
public:
	CAlert_Direction();			//�R���X�g���N�^
	virtual ~CAlert_Direction() override;			//�f�X�g���N�^

										//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// �N���G�C�g����
	static CAlert_Direction* Create(const D3DXVECTOR3 &pos, CObject *object);
	// �^�[�Q�b�g��ݒ肵�����I�u�W�F�N�g����ۑ�
	void SetObject(CObject *object) { pObject = object; }

	// �I�u�W�F�N�g�̎擾
	CObject *GetTargetObject() { return pObject; }
	// �T�C�Y�̎擾
	float GetSize() { return m_Size; }
	void SetLockOn(bool LockOn) { m_bLockOn = LockOn; }

private:
	bool				m_bLockOn;			// �ǔ����Ă��邩���Ă��Ȃ�����ݒ肷��
	float  m_Size;							// �T�C�Y
	D3DXVECTOR3	m_TargetPos;		// �ڕW�̍��W
	D3DXVECTOR3			m_pos;				// ���݂̍��W
	CObject				*pObject;			// �ڕW�̃I�u�W�F�N�g���̕ۑ���
};

#endif