//=========================================
//
//	time_over.h
//	Author:�y���m��
//
//=========================================
#ifndef _GAME_OVER_H_		//���̃}�N����`������ĂȂ�������
#define _GAME_OVER_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "mode.h"

//=========================================
// �N���X
//=========================================
class CGameOver : public CMode
{
public:
	CGameOver();
	~CGameOver();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	//����������
	virtual void Uninit() override;							//�I������
	virtual void Update() override;							//�X�V����
	virtual void Draw() override {};						//�`�揈��
};

#endif	// _RESULT_H_