//=========================================
//
//	missile_alert_manager.h
//	Author:�y���m��
//
//=========================================
#ifndef _MISSILE_ALERT_MANAGER_H_		//���̃}�N����`������ĂȂ�������
#define _MISSILE_ALERT_MANAGER_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

class CMissileAlertManager : public CObject
{
public:
	CMissileAlertManager();			//�R���X�g���N�^
	virtual ~CMissileAlertManager();			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override { return S_OK; }
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override {}
	// �I������
	void Uninit(void) override { m_bAlert = false;  Release(); }

	void SetObject(CObject *Obj) { pObject = Obj; }
	void SetAlert(bool bAlt) { m_bAlert = bAlt; }
	bool GetAlert() { return m_bAlert; }

	static CMissileAlertManager *Create(CObject *Obj);

private:
	CObject				*pObject;			// �ڕW�̃I�u�W�F�N�g���̕ۑ���
	bool				m_bAlert;
};

#endif