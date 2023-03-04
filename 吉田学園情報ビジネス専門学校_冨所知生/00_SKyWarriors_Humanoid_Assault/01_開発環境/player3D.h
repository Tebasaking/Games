//=========================================
//
//	player3D.h
//	Author:�y���m��
//
//=========================================
#ifndef _PLAYER_H_		//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`
#define MAX_PARTS (1)

#include "object3D.h"
#include "model.h"
#include "motion_model3D.h"

class CModel3D;
class CRadar;

class CPlayer3D : public CMotionModel3D
{
public:
	enum PLAYER_MODE
	{
		MODE_FLY = 0,
		MODE_ROBOT,
		MODE_MAX
	};

	enum PLAYER_STATE
	{
		NORMAL_STATE = 0,
		DEATH_STATE,
		MAX_STATE
	};
	
	explicit CPlayer3D(int nPriority = CObject::LAYER_ONE);	//�R���X�g���N�^
	virtual ~CPlayer3D() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// �N���G�C�g����
	static CPlayer3D* Create(const D3DXVECTOR3 &pos);
	// �v���C���[�̃��[�h�̐ݒ�
	void SetMode(PLAYER_MODE mode) { m_mode = mode; }
	// �v���C���[�̖��G����
	void SetInvincible() { m_bInvincible = true; }
	
	// ���G�J�E���g
	void InvincibleCheck();
	// ���b�N�I������
	void LockOn(void);
	// ��]����
	void Rotate(void);
	// �e�̔��ˏ���
	void Bullet(D3DXVECTOR3 pos);
	// �n�ʂƂ̓����蔻��
	void GroundCollison();
	// ���S�̏���
	void Death();

	// �X�V����(��s)
	void UpdateFly(void);
	// �X�V����(�l�^)
	void UpdateRob(void);

	//=========================================
	// �Q�b�^�[
	//=========================================
	bool GetCollision() { return m_bCollision; }		// �n�ʂɓ������Ă��邩�������Ă��Ȃ���

	//=========================================
	// ��s��Ԃł����g��Ȃ�����
	//=========================================
	// �p�����䏈��
	void Attitude(void);

	//=========================================
	// �l�^��Ԃł����g��Ȃ�����
	//=========================================
	// �ߐڍU������
	void Slash(void);
	// �W�����v����
	void Jump(void);
	// �ړ�����
	void Move(void);
	// �e�̉��Z����
	void AddBullet() { m_BulletHave += 2; }

	// BulletDelay�̎擾����
	int GetBulletDelay() { return m_BulletDelay;}
	int GetBulletHave() { return m_BulletHave; }
	bool GetInvincible() { return m_bInvincible; }

	const D3DXQUATERNION& GetQuaternion() const { return m_quaternion; }

private:
	float	m_scale;									// �傫��
	float	m_MoveAmount;								// �ړ���
	bool	m_bCollision;								// �����蔻��
	bool	m_bJump;									// �W�����v�����W�����v������Ȃ���
	bool	m_bMove;									// �ړ����Ă��邩���Ă��Ȃ���
	bool	m_bMove_Motion_Check;						// �ړ����[�V�������g���Ă��邩���Ȃ���
	bool	m_bMotion;									// ���[�V�������g���Ă��邩
	bool	m_bInvincible;								// �v���C���[�̖��G����

	D3DXVECTOR3 m_size;									// �g�嗦

	CModel3D*				m_apModel[MAX_PARTS];		// ���f���̍ő吔
	CModel3D*				m_pRobot;					// ���{�b�g�̃��f���ǂݍ���
	D3DXMATRIX				m_WorldMtx;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_MouseMove;				// �}�E�X�̈ړ�����
	D3DXVECTOR3				m_changeRot;				// �ϊ������p�x�̒l
	PLAYER_MODE				m_mode;						// ���[�h
	PLAYER_STATE			m_state;					// �v���C���[�̏��
	CRadar*					m_Radar;					// ���[�_�[
	CObject*				m_Nearest_object;			// �ł��߂��I�u�W�F�N�g
	int						m_BulletHave;				// �o���b�g�������Ă��鐔
	int						m_MotionCnt;				// ���[�V�����J�E���g
	int						m_nNumHandParts;			// ��̃p�[�c�ԍ�
	int						m_StepCnt;					// �����̃J�E���g
	int						m_BulletDelay;				// �o���b�g�̃J�E���g
	int						m_InvincibleCnt;			// ���G�J�E���g
	int						m_GameOverCnt;				// �Q�[���I�[�o�[�̃J�E���g
};

#endif