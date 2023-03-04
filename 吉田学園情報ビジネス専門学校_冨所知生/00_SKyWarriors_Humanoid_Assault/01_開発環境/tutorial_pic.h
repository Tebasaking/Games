//=========================================
//
//	training.h
//	Author:�y���m��
//
//=========================================
#ifndef _TUTORIAL_PIC_H_		//���̃}�N����`������ĂȂ�������
#define _TUTORIAL_PIC_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "mode.h"

//=========================================
// �N���X
//=========================================
class CPlayerManager;
class CEnemy_Manager;
class CPlayerUI;
class CScore;
class CAlert;
class CObject2D;
class CTutorial_Pic : public CMode
{
public:
	CTutorial_Pic();
	~CTutorial_Pic();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	//����������
	virtual void Uninit() override;						//�I������
	virtual void Update() override;						//�X�V����
	virtual void Draw() override {};					//�`�揈��

private:
	CObject2D *pObject2D[3];
	int		m_Select;
	int		m_SelectCnt;
};

#endif	// _TITLE_H_