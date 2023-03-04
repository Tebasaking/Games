//=========================================
//
//	player3D.h
//	Author:�y���m��
//
//=========================================
#ifndef _ENEMY3D_H_		//���̃}�N����`������ĂȂ�������
#define _ENEMY3D_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#define MAX_PARTS (1)

#include "object.h"

#include "motion_model3D.h"

class CModel3D;
class CTarget;
class CRadar;
class CEnemy :public CMotionModel3D
{
public:
	//�I�u�W�F�N�g�̎��
	enum EnemyState
	{
		ENEMY_IDOL,			// �G�l�~�[�̑ҋ@���
		ENEMY_CAUTION,		// �G�l�~�[���x�����Ă���
		ENEMY_WARNNING,		// �G�l�~�[���v���C���[�𔭌��������
		ENEMY_DEATH,
		//����������ԂƂ�����肽�����Ǘ]�T������΁B
	};

	// �G�l�~�[�̎��
	enum EnemyType
	{
		ENEMY_FLY,			// ��ɂ���G
		ENEMY_GROUND,		// ���ɂ���G
		ENEMY_TUTORIAL,		// TUTORIAL�p�G�l�~�[
		ENEMY_MAX
	};

	CEnemy();			//�R���X�g���N�^
	virtual ~CEnemy() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//���S����
	void Death(void);
	//�G�l�~�[���m�̓����蔻��
	void EnemyCollision(void);
	// �^�[�Q�b�g�̐F��ݒ肷��
	void TargetSetColor(D3DXCOLOR col);
	//�N���G�C�g����
	static CEnemy* Create(const D3DXVECTOR3 &pos,const EnemyType &type,const int &Wave);

	//�ԍ��ݒ菈��
	void SetNumber(int Number) { m_Number = Number; }
	//�ԍ��擾����
	int GetNumber() { return m_Number; }
	// �E�F�[�u���̎擾
	int GetWave() { return m_Wave; }

	// �E�F�[�u���̐ݒ�
	void SetWave(int wave) { m_Wave = wave; }

	// �X�e�[�g�̐ݒ�
	void SetState(EnemyState state) { m_state = state; }
	// �^�C�v�̐ݒ�ƃ^�C�v�ɉ��������[�V�����̐ݒ�
	void SetType(EnemyType type);
	// �e�̔���
	void Bullet(CObject *obj);
	// �v���C���[�����̋����ɗ������ɔ��肷�鏈��
	void Search();

	CModel3D *GetModel() { return m_apModel[0]; }

private:
	CTarget*				m_Target;					// ���g�ɂ���^�[�Q�b�g
	CRadar*					m_Radar;					// ���[�_�[
	float					m_scale;					// �傫��
	bool					m_bColision;				// �������Ă��邩�ǂ���

	int						m_AttackCount;				// �U���Ԋu
	int						m_Wave;						// ���g���������Ă���E�F�[�u��
	int						m_CntWar;					// �������ĉ��܂ł̎���

	EnemyType				m_type;						// �^�C�v�̐ݒ�
	CModel3D*				m_apModel[MAX_PARTS];		// ���f���̍ő吔
	EnemyState				m_state;					// ���
	D3DXMATRIX				m_WorldMtx;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_size;						// �T�C�Y�ݒ�
	D3DXVECTOR3				m_PlayerPos;				// �v���C���[�̍��W
	D3DXVECTOR3				m_posOld;
	D3DXVECTOR3				m_DestMove;					// �f�X�g
	D3DXVECTOR3				m_move;						// ���[�u
};

#endif