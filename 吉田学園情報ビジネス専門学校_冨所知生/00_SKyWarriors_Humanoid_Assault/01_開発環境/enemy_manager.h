//=========================================
//
//	enemy_manage.h
//	Author:�y���m��
//
//=========================================
#ifndef _ENEMY_MANAGE_H_		//���̃}�N����`������ĂȂ�������
#define _ENEMY_MANAGE_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include <vector>

#include "motion_model3D.h"

class CEnemy;
class CEnemy_Manager
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		int			type;
		int			time;
	}EnemyData;

	typedef struct
	{
		int m_Timer;		// �G�l�~�[�̐�����x�点��^�C�}�[
		int m_Amount;		// ���̃E�F�[�u���ɏo������G�l�~�[�̐�
		std::vector<EnemyData> m_EnemyData;
		std::vector<CEnemy*> m_EnemyList;
	}Wave;

	CEnemy_Manager();			//�R���X�g���N�^
	~CEnemy_Manager();			//�f�X�g���N�^

	// ����������
	HRESULT Init();
	// �X�V����
	void Update(void);
	// �`�揈��
	void Draw(void);
	// �I������
	void Uninit(void);
	// �N���G�C�g����
	static CEnemy_Manager *Create(void);
	// �t�@�C����ǂݍ��ޏ���
	void LoadFile();
	// �ǂݍ��񂾃E�F�[�u�̏������ɃG�l�~�[�𐶐�����
	void EnemyCreate(int Wave);
	// �E�F�[�u���̃G�l�~�[���S�ł�����
	void Extinction();
	// �E�F�[�u���̃G�l�~�[�����S��������
	void Death(CEnemy* pEnemy);

private:
	std::vector<Wave> m_Wave;
	int m_MaxWave;				// �E�F�[�u�̍ő吔
	int m_NowWave;				// ���݂̃E�F�[�u��
};

#endif