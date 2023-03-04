//=========================================
//
// �Z���t�̏���
// �⑫ : �Z���t�̉p�꒲�ׂ���Line���������ǂ킩��ɂ����̂�
//			�����������[�}����serihu.h,cpp�ł��G�G
// Auther�F�y���m��
//
//=========================================
#ifndef _SERIHU_H_		// ���̃}�N����`������ĂȂ�������
#define _SERIHU_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"

//=========================================
// �X�R�A�N���X���`
//=========================================
class CSerihu :public CObject2D
{
public:
	enum TYPE			//�t�F�[�h���
	{
		NONE,			// �i�V
		STOP,			// �u ���͈͊O���A�͈͓��ɖ߂�B �v
		SHOUT_DOWN,		// �u �G�@����@���āB �v
		TIME_LIMIT,		// �u ���I���܂ł���30�b�B�v
	};

	explicit CSerihu(int nPriority = LAYER_FIVE);	//�R���X�g���N�^
	virtual ~CSerihu() override;			//�f�X�g���N�^

	//����������
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CSerihu* Create(const TYPE type);

	//�X�R�A�̐ݒ�
	void SetType(TYPE type);

private:
	TYPE m_type;
	int m_Cnt;
};

#endif