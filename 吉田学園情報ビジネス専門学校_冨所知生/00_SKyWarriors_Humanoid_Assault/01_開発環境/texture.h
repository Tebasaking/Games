//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_TEST = 0,			// �e�X�g�Ɏg�p����摜������Ƃ�
		TEXTURE_FIRE,				// ���摜1
		TEXTURE_NUMBER,				// ���摜2
		TEXTURE_EXPLOSION,			// �����摜
		TEXTURE_SKY,				// ��
		TEXTURE_SEA,				// �C
		TEXTURE_GROUND,				// ��
		TEXTURE_THUNDER,			// �퓬�@�̃e�N�X�`��
		TEXTURE_TARGET,				// �^�[�Q�b�g
		TEXTURE_TITLE,				// �^�C�g��
		TEXTURE_RESULT,				// ���U���g
		TEXTURE_RADAR_MAP,			// ���[�_�[�}�b�v
		TEXTURE_FRAME,				// ���[�_�[�̃t���[��
		TEXTURE_ENEMY_TANK,			// �^���N
		TEXTURE_ENEMY_FLY,			// �퓬�@
		TEXTURE_ARROW,				// ���
		TEXTURE_WAVE,				// �g
		TEXTURE_PARTIClE,			// �p�[�e�B�N��
		TEXTURE_SMOKE,				// ��
		TEXTURE_TITLE_LOGO,			// �^�C�g�����S
		TEXTURE_TITLE_START,		// �X�^�[�g
		TEXTURE_TITLE_TUTORIAL,		// �`���[�g���A��
		TEXTURE_TITLE_END,			// �G���h
		TEXTURE_EXPLOSION2,			// �����e�N�X�`������2
		TEXTURE_UI_SPEED_AND_ALT,	// �v���C���[��UI�X�s�[�h�ƍ��x
		TEXTURE_UI_WEAPON,			// �v���C���[�̕���UI
		TEXTURE_GAGE_BOX,			// �����[�h�̃Q�[�W�̔�
		TEXTURE_GAGE,				// �����[�h�̃Q�[�W
		TEXTURE_UI_ALERT,			// �~�T�C���̃A���[�g
		TEXTURE_RANKING,			// �����L���O�̉摜
		TEXTURE_GAME_OVER,			// �Q�[���I�[�o�[�̉摜
		TEXTURE_TIME_OVER,			// �^�C���I�[�o�[�̉摜
		TEXTURE_TUTORIAL_000,		// TUTORIAL001
		TEXTURE_TUTORIAL_001,		// TUTORIAL002
		TEXTURE_TUTORIAL_002,		// TUTORIAL003
		TEXTURE_STOP,				// �X�g�b�v
		TEXTURE_MISSILE_MARK,		// �~�T�C���̃}�[�N
		TEXTURE_TUTORIAL_GAME,
		TEXTURE_SERIHU_GEKITUI_01,	// ���ăZ���t01
		TEXTURE_SERIHU_GEKITUI_02,	// ���ăZ���t02
		TEXTURE_SERIHU_TIME_LIMIT_30,// �c��30�b�̃^�C�����~�b�g
		TEXTURE_MAX,
		TEXTURE_NONE,	// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
