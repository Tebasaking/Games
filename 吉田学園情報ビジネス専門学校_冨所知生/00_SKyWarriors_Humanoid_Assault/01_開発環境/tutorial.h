//=========================================
//
//	title.h
//	Author:�y���m��
//
//=========================================
#ifndef _TUTORIAL_H_		//���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

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
class CTutorial : public CMode
{
public:
	CTutorial();
	~CTutorial();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	//����������
	virtual void Uninit() override;						//�I������
	virtual void Update() override;						//�X�V����
	virtual void Draw() override {};					//�`�揈��

private:
	static CMesh		  *m_pMesh[3];
	static CScore *m_pScore;
	static CPlayerManager *m_pPlayerManager;			// �v���C���[�}�l�[�W���\
	static CEnemy_Manager *m_pEnemyManager;				// �G�l�~�[�}�l�[�W���\
	static CPlayerUI	*m_PlayerUI;					// �v���C���[��UI
	static CAlert *m_pAlert;							// �A���[�g
	
	CObject2D *pObject2D;
	int		m_Select;
	int		m_SelectCnt;
};

#endif	// _TITLE_H_