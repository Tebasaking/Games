//=========================================
//
//	target.h
//	Author:�y���m��
//
//=========================================
#ifndef _TARGET_H_		//���̃}�N����`������ĂȂ�������
#define _TARGET_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"

class CTarget : public CObject2D
{
public:
	CTarget();			//�R���X�g���N�^
	virtual ~CTarget() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// �N���G�C�g����
	static CTarget* Create(const D3DXVECTOR3 &pos, CObject *object);
	// �ڕW�̍��W�̎擾
	static D3DXVECTOR3 GetTargetPos(void) { return m_TargetPos; }
	// �^�[�Q�b�g��ݒ肵�����I�u�W�F�N�g����ۑ�
	void SetObject(CObject *object) { pObject = object; }

	// �ԍ������鏈��
	void SetNumber(int number) { m_Number = number; }
	// �I�u�W�F�N�g�̎擾
	CObject *GetTargetObject() { return pObject; }
	// �T�C�Y�̎擾
	float GetSize() { return m_Size; }

private:
	float  m_Size;						// �T�C�Y
	static D3DXVECTOR3 m_TargetPos;		// �ڕW�̍��W
	CObject *pObject;					// �ڕW�̃I�u�W�F�N�g���̕ۑ���
};

#endif