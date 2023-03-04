//**************************************************************************************************
//
// �J��������(camera.h)
// Auther�F�������l
// �T�v : �J�����̐ݒ菈��
//
//**************************************************************************************************
#ifndef _CAMERA_H_			// ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "object.h"

//=============================================================================
// �J�����N���X
// Author : �������l
// �T�v : �J�����ݒ���s���N���X
//=============================================================================
class CObject;
class CCamera
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
	enum VIEW_TYPE
	{
		TYPE_CLAIRVOYANCE = 0,		// �������e
		TYPE_PARALLEL,				// ���s���e
		MAX_VIEW_TYPE,				// �^�C�v�̍ő吔
	};

	enum EVENT
	{
		EVENT_NORMAL,
		EVENT_DEATH,
		EVENT_FLY,		// �C�x���g���̃J�����ݒ�
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CCamera();
	~CCamera();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	virtual HRESULT Init(D3DXVECTOR3 pos);							// ������
	virtual void Uninit(void);										// �I��
	virtual void Update(void);										// �X�V
	/*virtual*/ void Set();												// �ݒ�
	void Set2();												// �ݒ�
	void SetViewType(VIEW_TYPE type) { m_viewType = type; }			// �^�C�v�̐ݒ�
	void SetViewSize(DWORD X, DWORD Y, int fWidth, int fHeight);	// �r���[�|�[�g�̑傫���ݒ�
	void AddViewSize(DWORD X, DWORD Y, int fWidth, int fHeight);	// �r���[�|�[�g�̊g�k
	void SetEvent(EVENT event) { m_event = event; }

	// �I�u�W�F�N�g�̃��[�h�̐ݒ�
	void SetObjMode(CObject::Object_mode mode) { m_Objectmode = mode; }
	// ��]�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	// �J������h�炷
	void ShakeCamera(int ShakeFrame, float Magnitude);
	
	//--------------------------------------------------------------------
	// �Q�b�^�\
	//--------------------------------------------------------------------
	const D3DXVECTOR3 GetPosR() { return m_posR; }					// �����_�̎擾
	const D3DXVECTOR3 GetPosV() { return m_posV; }					// ���_�̎擾
	D3DXMATRIX GetView() { return m_mtxView; }						// �J�����̏��̎擾
	D3DXMATRIX GetProjection() { return m_mtxProj; }				// �J�����̏��̎擾
	D3DVIEWPORT9 GetViewport() { return m_viewport; }				//�r���[�|�[�g�̎擾
	CObject::Object_mode GetObjType() { return m_Objectmode; }
	const D3DXQUATERNION GetQuaternion() { return m_quaternion; }	// ���_�p�x�̎擾
	D3DXVECTOR3 GetRot() { return m_rot; }
	float GetDistance() { return m_fDistance; }

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void RPosRotate();			// ��]
	void VPosRotate();			// ��]

protected:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXQUATERNION		m_quaternion;		// �N�I�[�^�j�I��
	D3DXQUATERNION		m_Destquaternion;	// �N�I�[�^�j�I���̃f�X�g
	D3DXMATRIX			m_mtxProj;			// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			m_mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3			m_posV;				// ���_
	D3DXVECTOR3			m_posR;				// �����_
	D3DXVECTOR3			m_rotMove;			// �ړ�����
	D3DXVECTOR3			m_Dest;				// �}�E�X��Dest
	D3DXVECTOR3			m_rot;				// ��]�̐ݒ�
	VIEW_TYPE			m_viewType;			// ���e�̎��
	D3DVIEWPORT9		m_viewport;			// �r���[�|�[�g
	EVENT				m_event;			// �C�x���g�Ǘ�
	CObject::Object_mode m_Objectmode;		// �I�u�W�F�N�g�̃��[�h

	float				m_fDistance;		// ���_���璍���_�܂ł̋���

	bool				m_bWork;			// �J�������[�N���I�����������Ă��Ȃ���

	/* �h�� */
	int					m_nCntFrame;		// �h���t���[���J�E���g
	int					m_Magnitude;		// �h��

	int					nRotateType = -1;
};

#endif
