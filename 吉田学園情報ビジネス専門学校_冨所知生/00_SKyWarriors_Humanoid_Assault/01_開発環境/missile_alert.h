//=========================================
//
//	missile_alert.h
//	Author:�y���m��
//
//=========================================
#ifndef _ALERT_H_		//���̃}�N����`������ĂȂ�������
#define _ALERT_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"

class CAlert : public CObject2D
{
public:
	CAlert();			//�R���X�g���N�^
	virtual ~CAlert() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// �N���G�C�g����
	static CAlert* Create(const D3DXVECTOR3 &pos);
	// �^�[�Q�b�g��ݒ肵�����I�u�W�F�N�g����ۑ�
	void SetObject(CObject *object) { pObject = object; }

	// �I�u�W�F�N�g�̎擾
	CObject *GetTargetObject() { return pObject; }
	// �T�C�Y�̎擾
	float GetSize() { return m_Size; }
	// �A���[�g�̏�Ԃ��擾
	bool GetCheck() { return m_bCheck; }

private:
	float  m_Size;							// �T�C�Y
	static D3DXVECTOR3	m_TargetPos;		// �ڕW�̍��W
	D3DXVECTOR3			m_pos;				// ���݂̍��W
	CObject				*pObject;			// �ڕW�̃I�u�W�F�N�g���̕ۑ���
	bool				m_bCheck;			// �A���[�g�̏�Ԃ��Ǘ�
	int	m_SECnt;							// ���ʉ��̃J�E���g
};

#endif