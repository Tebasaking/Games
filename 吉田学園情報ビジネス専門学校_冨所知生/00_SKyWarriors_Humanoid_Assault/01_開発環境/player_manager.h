//=========================================
//
//	player_manager.h
//	Author:�y���m��
//
//=========================================
#ifndef _PLAYER_MANAGE_H_		//���̃}�N����`������ĂȂ�������
#define _PLAYER_MANAGE_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "player3D.h"

class CPlayer3D;
class CPlayerManager
{
public:
	enum PLAYER_MODE
	{
		MODE_FLY = 0,
		MODE_ROBOT,
		MODE_MAX
	};

	CPlayerManager();			//�R���X�g���N�^
	virtual ~CPlayerManager();			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos);
	// �X�V����
	void Update(void);
	// �`�揈��
	void Draw(void);
	// �I������
	void Uninit(void);
	// ���[�h�̎擾
	static PLAYER_MODE GetMode() { return m_mode; }
	static CPlayer3D* GetPlayer() { return m_pFly; }
	static CPlayer3D* GetRobot() { return m_pRobot; }
	// �N���G�C�g����
	static CPlayerManager* Create(const D3DXVECTOR3 &pos);

private:
	static CPlayer3D* m_pFly;				// ��s�`�Ԃ̏���
	static CPlayer3D* m_pRobot;				// ���{�b�g�`�Ԃ̏���
	static PLAYER_MODE m_mode;				// �v���C���[�̏�Ԃ��Ǘ�����

	static bool m_bTransform;				// �ό`
};

#endif