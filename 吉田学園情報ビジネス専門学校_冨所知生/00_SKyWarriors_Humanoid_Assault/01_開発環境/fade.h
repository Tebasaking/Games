//=============================================================================
//
// �t�F�[�h����
// Author:����]��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "object2D.h"


//�O���錾
class CMode;

//�t�F�[�h�N���X
class CFade : public CObject2D
{
public:
	enum FADE			//�t�F�[�h���
	{
		FADE_NONE = 0,	//�������ĂȂ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MAX
	};

	explicit CFade(int nPriority = LAYER_FIVE);	//�R���X�g���N�^
	~CFade();									//�f�X�g���N�^

	void Init(CApplication::MODE modeNext);		//�t�F�[�h�̏�����
	void Uninit(void) override;					//�t�F�[�h�̏I��
	void Update(void) override;					//�t�F�[�h�̍X�V
	void Draw(void) override;					//�t�F�[�h�̕`��

	static void SetFade(CApplication::MODE modeNext);	//�t�F�[�h�̐ݒ�
	static FADE GetFade() { return m_pFade; }

	static CFade *Create(CApplication::MODE modeNext);

private:
	static CApplication::MODE m_ModeNext;	//���̉��(���[�h)
	static FADE m_pFade;					//�t�F�[�h�̏��
	static D3DXCOLOR m_Color;				//�J���[
};
#endif