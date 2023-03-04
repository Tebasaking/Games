//**************************************************************************************************
//
// ���R�J��������(camera.h)
// Auther�F�������l
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************
#ifndef _CAMERA_PLAYER_H_			// ���̃}�N����`������ĂȂ�������
#define _CAMERA_PLAYER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "camera.h"

//=============================================================================
// �J�����N���X
// Author : �������l
// �T�v : �J�����ݒ���s���N���X
//=============================================================================
class CCameraPlayer : public CCamera
{
public:
	enum CAMERA_TYPE
	{
		TYPE_FREE,					// ���R�ɃJ�����𓮂�������
		TYPE_SHOULDER,				// ���z�����_���
		MAX_CAMERA_TYPE,			// �J�����^�C�v�̍ő吔
	};

public:
	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CCameraPlayer();
	~CCameraPlayer();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;							// ������
	void Uninit(void) override;										// �I��
	void Update(void) override;										// �X�V
	void Up(void);													// ��ɏ㏸����
	void SetUp(bool check) { m_bUp = check; }
	void SetDeathGround() { m_bDeathGround = true; }

	// float�𗘗p�����J�����̐���(���\�������)
	bool Limit_Used_Mouse();
	// �ݒ肵���ڕW�n�_�Ɏ��_���ړ������鏈��
	void CameraWork(D3DXQUATERNION que);
	
	//--------------------------------------------------------------------
	// �Q�b�^�\
	//--------------------------------------------------------------------
	const D3DXVECTOR3 GetVec() { return m_VecGet;}					// �}�E�X�x�N�g���̎擾
	CAMERA_TYPE GetMode() { return m_mode; }						// �J�����̃��[�h���̎擾
	float GetMoveSpeed() { return MOVE_SPEED; }
	float GetMoveSpeedMax() { return MOVE_SPEED_MAX; }
	float GetMoveSpeedMin() { return MOVE_SPEED_MIN; }

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Rotate();			// ��]
	void FreeMove();		// �ʏ�ړ�
	void ShoulderMove();	// ���z�����̈ړ� 
	void MouseMove();		// �}�E�X�ړ�����]�ɑ��
	void JoyPadMove();		// �W���C�p�b�h�ړ�����]�ɑ��
	void FlightEvent();		// �t���C�g�C�x���g
	void Death();			// ���S�C�x���g�̊J�n

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3			m_rotMove;			// �ړ�����
	D3DXVECTOR3			m_VecGet;			// �}�E�X�̃x�N�g��
	D3DXVECTOR3			m_Dest;				// �}�E�X��Dest
	D3DXVECTOR3			DefPos;		
	D3DXVECTOR3			m_axisVec;			// ��]�����̃x�N�g��
	CAMERA_TYPE			m_mode;				// �J�����̃��[�h

	float				m_fRotMove;			// �ړ�����
	float				m_MouseMove;		// ���S����ړ������}�E�X�̗�
	float				CAMERA_MOVE_SPEED = 0.5f;
	float				MOVE_SPEED = 5.0f;
	float				m_Gravity;			// �d��

	int					m_nCntFly;			// ��s
	int					m_nCntMoveSound;	// �ړ����̉�
	int					m_nCntCameraWork;	// �J�������[�N�̏I���܂ł̎���

	bool				m_bUp;				// �㏸���Ă��邩���Ă��Ȃ���
	bool				m_bDeathGround;		// ���S�Փ�

	int					MOVE_SPEED_MAX;
	int					MOVE_SPEED_MIN;
};

#endif
