//=========================================
//
//	object.h
//	Author:�y���m��
//
//
//=========================================
#ifndef _OBJECT_H_		//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`
#define MAX_OBJECT (10000)

#include "main.h"

class CObject
{
public:
	//�I�u�W�F�N�g�̎��
	enum EObjType
	{
		OBJECT_NONE,		// �����^�C�v
		OBJECT_PLAYER,		// �v���C���[
		OBJECT_ENEMY,		// �G�l�~�[
		OBJECT_BULLET,		// �e�̎��
		OBJECT_RADAR,		// ���[�_�[�̃I�u�W�F�N�g
		OBJECT_MESH,		// ���b�V���t�B�[���h
		OBJECT_TARGET,		// �^�[�Q�b�g
		OBJECT_EMPTY,		// �ݒ肳��Ă��Ȃ�
		OBJECT_FADE,
		OBJECT_ALERT,		// �A���[�g
		OBJECT_EFFECT,		// �G�t�F�N�g
		OBJECT_ALERT_MANAGAER,	// �A���[�g�̃}�l�[�W���\��p�A�}�����炦
//		OBJECT_BILLBOARD,	// �r���{�[�h
		OBJECT_MAX
	};

	enum Priority
	{
		LAYER_ONE,
		LAYER_TWO,
		LAYER_THREE,
		LAYER_FOUR,
		LAYER_FIVE,
		LAYER_MAX
	};

	enum Object_mode
	{
		NONE_MODE = -1,
		NORMAL_MODE = 0,
		TITLE_MODE,
		RADAR_MODE,
		MAX_MODE
	};

	explicit CObject(int nPriority = LAYER_ONE);			//�R���X�g���N�^
	virtual ~CObject();			//�f�X�g���N�^

	virtual HRESULT Init(const D3DXVECTOR3 &pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0; 

	static void UpdateAll();
	static void DrawAll(Object_mode mode);
	static void UninitAll();

	// �p�x�̐��K��
	D3DXVECTOR3 NormalizeRotXYZ(D3DXVECTOR3 Rot);
	float NormalizeRot(float fRot);

	// �N�H�[�^�j�I���̐ݒ�
	void SetQuaternion(const D3DXQUATERNION quaternion) { m_quaternion = quaternion; }

	const D3DXVECTOR3& GetPosition() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const float& GetScale() const { return m_scale; }
	const D3DXVECTOR3& GetSize() const { return m_size; }

	// �Q�b�^�[
	CObject	*GetObjectinfo() { return this; }
	int		GetNumber() { return m_Number; }
	int		GetHP() { return m_HP; }
	bool	GetTargeting() { return m_Targeting; }
	bool	GetCollision() { return m_Collision; }
	static  CObject *GetObjectTop(int nPriority) { return m_pTop[nPriority]; }
	static  CObject *GetObjectType(CObject::EObjType type);
	CObject *GetObjectNext() { return m_pNext; }
	EObjType GetObjectType() { return m_type; }

	// �Z�b�^�[
	void SetHP(int HP) { m_HP = HP; }
	void SetPosition(const D3DXVECTOR3& pos);
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetObjectType(EObjType type) { m_type = type; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetCollision(bool bCollision) { m_Collision = bCollision; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXQUATERNION& GetQuaternion() { return m_quaternion; }

	D3DXVECTOR3 GetPosOld() { return m_posOld; }

	// �}�g���b�N�X
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }				// ���[���h�}�g���b�N�X�̃Z�b�^�[
	D3DXMATRIX *GetMtxWorld() { return &m_mtxWorld; }								// ���[���h�}�g���b�N�X�̃Q�b�^�[

	void Release();
	void DFlagDelete();

	// 2�_����p�x�����߂�
	D3DXVECTOR3 AtanRot(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
	int ManageHP(int Value);

	// ���� : ���炷���W�̑傫���A�N�H�[�^�j�I���A�ڕW���W
	D3DXVECTOR3 MtxPos(D3DXVECTOR3 pos, D3DXQUATERNION qua, D3DXVECTOR3 TargetPos);
	// ���� : ���炷���W�̑傫���A�p�x�A�ڕW���W
	D3DXVECTOR3 MtxPosRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 TargetPos);
	// ���� : ���W�A�Â����W�A�ڕW���W�A�T�C�Y�A�ڕW�T�C�Y�A�����Ԃ����Ԃ��Ȃ���
	bool Collision(CObject *Target, bool bExtrude);
	// ����: �ڕW�̍��W �A ��̒��S �A �͈�(�p�x) �A���� , ����(�p�x)
	bool SearchEye(D3DXVECTOR3 Vec1, D3DXVECTOR3 Vec2, float rangeRadian, float length, float directionDegree);

protected:
	static int	m_nNumObject;
	static int m_nNumAll;
	int m_nID;
	int m_Number;								// ���Ԗڂ̃I�u�W�F�N�g��(�ԍ��J�E���g�͊e����)

private:
	bool m_Targeting;							// �^�[�Q�b�g�̑ΏۂɂȂ��Ă��邩���Ȃ���
	bool m_DeathFlag;							// ���S�t���O
	bool bCollision;							// �����蔻��
	int m_Priority;								// �v���C�I���e�B
	static CObject *m_pTop[LAYER_MAX];			// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCurrent[LAYER_MAX];		// ����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;							// �����̎��̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;							// �����̈�O�̃I�u�W�F�N�g�ւ̃|�C���^
	EObjType m_type;
	D3DXVECTOR3 m_pos;							// ���W�ݒ�
	D3DXVECTOR3 m_size;							// �傫���ݒ�
	D3DXVECTOR3 m_rot;							// ��]�ݒ�
	D3DXVECTOR3 m_posOld;						// �Â����W
	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXQUATERNION		m_quaternion;			//�N�H�[�^�j�I��
	Object_mode m_objmode;						// �I�u�W�F�N�g�̕`�惂�[�h
	float		m_scale;						// �g�嗦�ݒ�
	int			m_HP;							// �̗�
	bool		m_Collision;					// �����蔻��
};

#endif