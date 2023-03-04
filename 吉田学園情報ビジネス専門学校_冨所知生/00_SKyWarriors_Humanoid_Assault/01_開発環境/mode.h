//=========================================
//
// mode.h
// Author: �y���m��
//
//=========================================
#ifndef _MODE_H_
#define _MODE_H_

//=========================================
// �C���N���[�h
//=========================================
#include "object.h"

//=========================================
// �N���X
//=========================================
class CMode : public CObject
{
public:
	CMode();
	~CMode() override;

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override { return S_OK; }	//����������
	virtual void Uninit() override { Release(); }					//�I������
	virtual void Update() override {}					//�X�V����
	virtual void Draw() override {}						//�`�揈��

private:
	D3DXVECTOR3 m_pos;						//���W
	float m_scale;							// �g�嗦
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXVECTOR3 m_rot;
};

#endif