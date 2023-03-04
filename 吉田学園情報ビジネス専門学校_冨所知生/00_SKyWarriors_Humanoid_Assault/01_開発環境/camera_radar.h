//**************************************************************************************************
//
// ���[�_�[��̃J��������(camera.h)
// Author : �������l
// Author : ���c�C�s
// Author : �y���m��
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************
#ifndef _CAMERA_RADAR_H_			// ���̃}�N����`������ĂȂ�������
#define _CAMERA_RADAR_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "camera.h"

//=============================================================================
// �J�����N���X
// Author : �������l
// Author : ���c�C�s
// Author : �y���m��
// �T�v : �J�����ݒ���s���N���X
//=============================================================================
class CCameraRadar : public CCamera
{
private:
	//--------------------------------------------------------------------
	// �萔��`
	//--------------------------------------------------------------------
	static const float CAMERA_NEAR;			// �j�A�̍ő�l
	static const float CAMERA_FUR;			// �t�@�[�̍ő�l

public:
	//=============================================================================
	// ���e���@�̃^�C�v�񋓌^
	// Author : �������l
	// �T�v : ���e���@�̎��
	//=============================================================================
	enum CAMERA_TYPE
	{
		TYPE_FREE,					// ���R�ɃJ�����𓮂�������
		TYPE_SHOULDER,				// ���z�����_���
		MAX_CAMERA_TYPE,			// �J�����^�C�v�̍ő吔
	};

	enum EVENT
	{
		EVENT_NORMAL,
		EVENT_FLY,					// �C�x���g���̃J�����ݒ�
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CCameraRadar();
	~CCameraRadar();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	virtual HRESULT Init(D3DXVECTOR3 pos);								// ������
	virtual void Uninit();												// �I��
	virtual void Update();												// �X�V

	// float�𗘗p�����J�����̐���(���\�������)
	bool Limit_Used_Mouse();
	// �N�H�[�^�j�I�����ɍ��W�ɕϊ����鏈��
	D3DXVECTOR3 QuaternionToPolar(double w, double x, double y, double z);
	// ���W�A�����N�H�[�^�j�I���ɕϊ�
	D3DXQUATERNION radian_to_quaternion(double radian);
	// �I�C���[�p���N�H�[�^�j�I���ɕϊ�
	D3DXQUATERNION fromEuler(float yaw, float pitch, float roll);
	// �N�H�[�^�j�I�������W�A���ɕϊ�
	double quaternion_to_radian(double qw, double qx, double qy, double qz);
	// �I�u�W�F�N�g�̃��[�h�̐ݒ�
	void SetObjMode(CObject::Object_mode mode) { m_Objectmode = mode; }
	// �N�H�[�^�j�I������]�s��ɕϊ�
	D3DXVECTOR3 DirectionVectorFromQuaternion(const D3DXQUATERNION& qRotation);
	
private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Rotate();				// ��]
	void MouseMove();			// �}�E�X�ړ�����]�ɑ��
	void JoyPadMove();			// �W���C�p�b�h�ړ�����]�ɑ��

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3			m_vecU;				// ������x�N�g��
	D3DXVECTOR3			m_VecGet;			// �}�E�X�̃x�N�g��
	D3DXVECTOR3			m_Dest;				// �}�E�X��Dest
	D3DXVECTOR3			m_axisVec;			// ��]�����̃x�N�g��
	CAMERA_TYPE			m_mode;				// �J�����̃��[�h

	float				m_fRotMove;			// �ړ�����
	float				m_MouseMove;		// ���S����ړ������}�E�X�̗�
	float				CAMERA_MOVE_SPEED = 0.5f;
	float				MOVE_SPEED = 5.0f;
	float				m_Gravity;			// �d��

	bool				m_bWork;			// �J�������[�N���I�����������Ă��Ȃ���
	bool				m_bUp;				// �㏸���Ă��邩���Ă��Ȃ���

	int					m_nCntFly;			// ��s
	int					m_nCntCameraWork;	// �J�������[�N�̏I���܂ł̎���
	int					m_nCntMoveSound;	// �ړ����̉�

	int					nRotateType = -1;
};

#endif
