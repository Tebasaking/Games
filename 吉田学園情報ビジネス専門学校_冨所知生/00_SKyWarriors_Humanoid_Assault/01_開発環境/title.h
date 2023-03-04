//=========================================
//
//	title.h
//	Author:�y���m��
//
//=========================================
#ifndef _TITLE_H_		//���̃}�N����`������ĂȂ�������
#define _TITLE_H_		//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "mode.h"

//=========================================
// �N���X
//=========================================
class CObject2D;
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle();

	virtual HRESULT Init(const D3DXVECTOR3 &pos) override;	//����������
	virtual void Uninit() override;						//�I������
	virtual void Update() override;						//�X�V����
	virtual void Draw() override {};					//�`�揈��

private:
	static CMesh		  *m_pMesh[3];
	CObject2D *pObject2D[4];
	int		m_Select;
	bool	m_bSelect;
	int		m_SelectCnt;
	bool	m_bFade;
};

#endif	// _TITLE_H_