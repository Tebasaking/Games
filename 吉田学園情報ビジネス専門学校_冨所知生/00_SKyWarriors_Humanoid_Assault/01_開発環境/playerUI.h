//=========================================
//
//	player_ui.h
//	Author:�y���m��
//
//=========================================
#ifndef _PLAYER_UI_H_		//���̃}�N����`������ĂȂ�������
#define _PLAYER_UI_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "Object2D.h"

#define SPEED_DIGITS (3)
#define ALTITUDE_DIGITS (4)
#define MISSILE_DIGITS (2)
//=========================================
// �N���X
//=========================================
class CNumber;
class CObject2D;
class CSerihu;
class CPlayerUI : public CObject
{
	enum COLOR
	{
		RED = 0,
		GREEN,
	};
public:
	explicit CPlayerUI(int nPriority = LAYER_ONE);
	~CPlayerUI();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	// ����������
	virtual void Uninit() override;							// �I������
	virtual void Update() override;							// �X�V����
	virtual void Draw() override {};						// �`�揈��
	void Set();												// �����̐ݒ�
	void AlertCheck();
	void SetAlertColor(COLOR col);
	void SetAlert(bool Alert) { m_bAlert = Alert; }
	void SetStop(bool bSto) { m_bStop = bSto; }
	bool GetAlert() { return m_bAlert; }

private:
	CObject2D	*pObject2D[2];
	CSerihu		*pStop;										// �X�g�b�v��\�����镶��
	CNumber		*m_pSpeedNum[SPEED_DIGITS];					// �i���o�[1
	CNumber		*m_pAltitude[ALTITUDE_DIGITS];				// �i���o�[1
	CNumber		*m_pMissileNum[MISSILE_DIGITS];				// �~�T�C���i���o�[
	
	CObject2D	*m_pGageBox;								// �Q�[�WBOX
	CObject2D	*m_pGage;									// �Q�[�W

	COLOR		*m_ColorType;
	bool		m_bAlert;									// �A���[�g���g�p����Ă��邩���Ȃ���
	bool		m_bStop;									// �X�g�b�v���g�p����Ă��邩���Ȃ���
};

#endif	// _TITLE_H_