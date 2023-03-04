//=========================================
//
//	title_model.h
//	Author:�y���m��
//
//=========================================
#ifndef _TITLE_MODEL_H_		//���̃}�N����`������ĂȂ�������
#define _TITLE_MODEL_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#define MAX_PARTS (1)

#include "object.h"

#include "motion_model3D.h"

class CModel3D;
class CTitleModel :public CMotionModel3D
{
public:
	// �G�l�~�[�̎��
	enum ModelType
	{
		ENEMY_FLY,			// ��ɂ���G
		ENEMY_GROUND,		// ���ɂ���G
		ENEMY_MAX
	};

	explicit CTitleModel(int nPriority = CObject::LAYER_FIVE);			//�R���X�g���N�^
	virtual ~CTitleModel() override;			//�f�X�g���N�^

										//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CTitleModel* Create(const D3DXVECTOR3 &pos, const ModelType &type);

	// �^�C�v�̐ݒ�ƃ^�C�v�ɉ��������[�V�����̐ݒ�
	void SetType(ModelType type);

	CModel3D *GetModel() { return m_apModel[0]; }

private:
	float					m_scale;					// �傫��
	bool					m_bColision;				// �������Ă��邩�ǂ���

	int						m_AttackCount;				// �U���Ԋu
	int						m_Wave;						// ���g���������Ă���E�F�[�u��
	int						m_CntWar;					// �������ĉ��܂ł̎���

	ModelType				m_type;						// �^�C�v�̐ݒ�
	CModel3D*				m_apModel[MAX_PARTS];		// ���f���̍ő吔
	D3DXMATRIX				m_WorldMtx;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_PlayerPos;				// �v���C���[�̍��W
	D3DXVECTOR3				m_posOld;
	D3DXVECTOR3				m_DestMove;					// �f�X�g
};

#endif