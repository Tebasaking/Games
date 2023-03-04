//=========================================
//
//	game.h
//	Author:�y���m��
//
//=========================================
#ifndef _GAME_H_		//���̃}�N����`������ĂȂ�������
#define _GAME_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "mode.h"
#include <vector>

class CPlayer3D;
class CMesh;
class CPlayerManager;
class CEnemy;
class CRadar;
class CScore;
class CEnemy_Manager;
class CAlert;
class CPlayerUI;
//=========================================
// �N���X
//=========================================
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	//����������
	virtual void Uninit() override;							//�I������
	virtual void Update() override;							//�X�V����
	virtual void Draw() override {};						//�`�揈��

	void EnemyManage();
	void DeleteEnemy(CEnemy* pEnemy);

	static CMesh *GetGround() { return m_pMesh[1]; }
	static CEnemy_Manager *GetEM() { return m_pEnemyManager; }
	static CPlayerManager *GetPM() { return m_pPlayerManager; }
	static CAlert *GetAlert() { return m_pAlert; }
	static CPlayerUI *GetPUI() { return m_PlayerUI; }
	static bool GetFinish() { return m_bFinish; }
	static void Finish() { m_bFinish = true; }
	static void Finish2() { m_bFinish_2 = true; }
	static CScore *GetScore() { return m_pScore; }
	static void Add(int Score);

private:
	static CMesh		  *m_pMesh[3];
	static CPlayerManager *m_pPlayerManager;
	static CEnemy_Manager *m_pEnemyManager;
	static CPlayerUI	*m_PlayerUI;					// �v���C���[��UI
	static CScore *m_pScore;
	static CAlert *m_pAlert;							// �A���[�g
	static bool m_bFinish;
	static bool m_bFinish_2;
	CRadar*				  m_pRadar;
};

#endif	// _GAME_H_