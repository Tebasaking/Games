//=========================================
//
//	game.h
//	Author:�y���m��
//
//=========================================
#ifndef _RESULT_H_		//���̃}�N����`������ĂȂ�������
#define _RESULT_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "mode.h"

class CRanking;
//=========================================
// �N���X
//=========================================
class CResult : public CMode
{
public:
	CResult();
	~CResult();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	//����������
	virtual void Uninit() override;						//�I������
	virtual void Update() override;						//�X�V����
	virtual void Draw() override {};					//�`�揈��

	CRanking* m_pRanking;
};

#endif	// _RESULT_H_