//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "texture.h"

#include <assert.h>
//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X
	"Data\\TEXTURE\\UITEST.png",
	"Data\\TEXTURE\\bullet.png",	// �e
	"Data\\TEXTURE\\number001.png",						// �i���o�[
	"Data\\TEXTURE\\explosion000.png",
	"Data\\TEXTURE\\sky_down.jpg",
	"Data\\TEXTURE\\sea.jpg",
	"Data\\TEXTURE\\ground.jpg",
	"Data\\F16_Thuderbirds4.bmp",
	"Data\\TEXTURE\\targeting.png",
	"Data\\TEXTURE\\�����Ƃ�.jpg",
	"Data\\TEXTURE\\�肴���.jpg",
	"Data\\TEXTURE\\radarmap.png",
	"Data\\TEXTURE\\Machine.png",
	"Data\\TEXTURE\\enemy_tank.png",
	"Data\\TEXTURE\\enemy_Fly.png",
	"Data\\TEXTURE\\arrow.png",
	"Data\\TEXTURE\\sea000.jpg",
	"Data\\TEXTURE\\effect000.png",
	"Data\\TEXTURE\\smoke.png",
	"Data\\TEXTURE\\TITLE_LOGO.png",
	"Data\\TEXTURE\\TITLE_START.png",
	"Data\\TEXTURE\\TITLE_TUTORIAL.png",
	"Data\\TEXTURE\\TITLE_END.png",
	"Data\\TEXTURE\\Explosion001.png",
	"Data\\TEXTURE\\UI_ALT_SPEED.png",
	"Data\\TEXTURE\\UI_WEAPON.png",
	"Data\\TEXTURE\\GAGE_BOX.png",
	"Data\\TEXTURE\\GAGE.png",
	"Data\\TEXTURE\\UI_MISSILE_ALERT.png",
	"Data\\TEXTURE\\Ranking001.png",
	"Data\\TEXTURE\\GAME_OVER.png",
	"Data\\TEXTURE\\TIME_OVER.png",
	"Data\\TEXTURE\\tutorial_01.png",
	"Data\\TEXTURE\\tutorial_02.png",
	"Data\\TEXTURE\\tutorial_03.png",
	"Data\\TEXTURE\\STOP_PLAYER.png",
	"Data\\TEXTURE\\missile.png",
	"Data\\TEXTURE\\TUTORIAL_GAME.png",
	"Data\\TEXTURE\\GEKITUI_1.png",
	"Data\\TEXTURE\\GEKITUI_2.png",
	"Data\\TEXTURE\\TIME_LIMIT_30.png",
	"Data\\TEXTURE\\TUTORIAL_GAME_MOUSE.png",
	"Data\\TEXTURE\\tutorial_01_mouse.png",
	"Data\\TEXTURE\\UI_MISSION.png",
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() : s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
