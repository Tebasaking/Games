//=========================================
//
//	radar.h
//	Author:�y���m��
//
//=========================================
#ifndef _RADAR_H_		//���̃}�N����`������ĂȂ�������
#define _RADAR_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "billboard.h"
#include "camera_player.h"

class CObject2D;
class CCamera;
class CRadar :public CBillboard
{
public:
	enum RADAR_TYPE
	{
		RADAR_MAP,
		RADAR_PLAYER,
		RADAR_ENEMY,
		RADAR_MISSILE,
		RADAR_FRAME
	};

	explicit CRadar(int nPriority = LAYER_FIVE);			// �R���X�g���N�^
	virtual ~CRadar() override;								// �f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//���b�N�I������
	D3DXVECTOR3 LockOn(D3DXMATRIX *mtxWorld);
	//�N���G�C�g����
	static CRadar* Create(const D3DXVECTOR3 &pos, CObject *object, RADAR_TYPE type);

	// �ǔ�����I�u�W�F�N�g�̐ݒ�
	void SetObject(CObject *pObj) { m_pObject = pObj; }
	// �^�C�v�̐ݒ�
	void SetType(RADAR_TYPE type) { m_type = type; }
	// �^�C�v�̃Q�b�^�[
	RADAR_TYPE GetType() { return m_type; }

private:
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_posOld;			// ��O�̍��W
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXQUATERNION m_quaternion;	// �N�H�[�^�j�I��
	CObject *m_pObject;
	CCameraPlayer::CAMERA_TYPE Camera_Type;
	RADAR_TYPE m_type;				// ���[�_�[�̃^�C�v
	CObject2D *m_pBackGround;		// ���[�_�[�̔w�i
};

#endif