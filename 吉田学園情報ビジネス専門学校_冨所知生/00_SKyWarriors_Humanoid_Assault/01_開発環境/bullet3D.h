//=========================================
//
//	bullet3D.h
//	Author:�y���m��
//
//=========================================
#ifndef _BULLET3D_H_		//���̃}�N����`������ĂȂ�������
#define _BULLET3D_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object3D.h"
#include "object.h"
#include "model.h"
#include "missile_alert.h"

class CModel3D;
class CObject;
class CMissileAlertManager;
class CRadar;
class CAlert_Direction;
class CBullet3D : public CObject
{
public:
	enum MISSILE_STATE
	{
		IDOL_STATE = 0,		// �ʏ�
		LOCK_ON_STATE,		// ���b�N�I��
		MAX_STATE,			// �v�Z���@�̍ő吔
	};

	CBullet3D();							//�R���X�g���N�^
	virtual ~CBullet3D() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// �X�V����
	void Update(void) override;
	// �`�揈��
	void Draw(void) override;
	// �I������
	void Uninit(void) override;
	// �e�̐���
	void BulletMove(void);
	// ���b�N�I������
	D3DXVECTOR3 LockOn();
	// �Ǐ]����
	void Follow();

	// �T���J�E���g�̖ڕW��ݒ�
	void SetSearchValue(int val) { m_SearchValue = val; }
	// �p�x�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_ShooterRot = rot; }
	void SetQue(D3DXQUATERNION que) { m_quaternion = que; }
	void SetAngleLimit(float Limit) { m_fAngleLimit = Limit; }
	// �~�T�C���̑��x�̎擾
	float GetSpeed() { return m_MissileSpeed; }

	// �N�H�[�^�j�I�����I�C���[�p�ɕϊ�����
	D3DXVECTOR3 QuaternionChange();

	// �A���[�g��L���ɂ��邩�ǂ������擾
	bool GetAlert() { return m_bAlert; }

	// �N���G�C�g����
	// ���� : ���炷���W�̑傫���A�N�H�[�^�j�I���A�ڕW�I�u�W�F�N�g���A�ˎ�I�u�W�F�N�g���A�U���̃^�C�~���O���J�E���g����ڕW�l
	static CBullet3D* Create(const D3DXVECTOR3 &pos, const D3DXQUATERNION &quaternion, CObject *object, CObject *Shooter,int val,float Limit);

private:
	CMissileAlertManager*	m_pAlert;					// �~�T�C���A���[�g
	CModel3D*				m_pModel;					// ���f���̍ő吔
	CObject*				m_TargetObj;				// �^�[�Q�b�g�I�u�W�F�N�g
	CObject*				m_pShooter;					// �V���[�^�[
	CRadar*					m_pRadar;					// ���[�_�[
	CAlert_Direction*		m_pDirection;				// �A���[�g�̕��p
	D3DXQUATERNION			m_quaternion;				// �N�H�[�^�j�I��
	D3DXVECTOR3				m_Rot;						// �I�C���[�p
	D3DXVECTOR3				m_pos;						// ���W
	D3DXVECTOR3				m_TargetPos;				// �^�[�Q�b�g�̍��W
	D3DXVECTOR3				m_posOld;					// �Â����W
	D3DXVECTOR3				m_posTarget;				// �ڕW�̍��W
	D3DXVECTOR3				m_ShooterRot;				// �ˎ�̊p�x
	D3DXVECTOR3				m_FllowRot;					// �ǔ����Ă������
	D3DXVECTOR3				m_move;						// �i�s������ۑ�����
	D3DXMATRIX				m_WorldMtx;					// ���[���h�}�g���b�N�X
	MISSILE_STATE			m_state;					// �X�e�[�g
	float					m_length;					// �e�ƖڕW�l�̋���
	float					m_MissileSpeed;				// �~�T�C���̑��x
	float					m_fAngleLimit;				// ����̌��E�l
	int						m_FrontMoveCnt;				// �^��������ԃJ�E���g
	int						m_SearchCnt;				// �T���J�E���g
	int						m_SearchValue;				// �T���J�E���g�̖ڕW�l
	int						m_MissileCnt;				// �~�T�C���J�E���g
	int						m_LocusCnt;					// ������\������J�E���g

	bool					m_bAlert;					// �A���[�g
};

#endif