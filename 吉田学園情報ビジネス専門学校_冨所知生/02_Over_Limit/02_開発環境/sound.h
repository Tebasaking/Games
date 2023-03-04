//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��
	SOUND_LABEL_BGM001,			// �Q�[�����
	SOUND_LABEL_BGM002,			// ���U���g(����)
	SOUND_LABEL_BGM003,			// �Q�[���I�[�o�[(�s�k)
	SOUND_LABEL_BGM_BOSS,		//�{�X���BGM
	SOUND_LABEL_PAGE,			//�`���[�g���A���̃y�[�W���߂�������
	SOUND_LABEL_BELL,			//�Q�[�����n�߂���
	SOUND_LABEL_SELECT,			//�^�C�g���őI�����Ă���̂����炵�����̉�
	SOUND_LABEL_CUTTING,		//����؂鏈��
	SOUND_LABEL_HOT,			//���M��
	SOUND_LABEL_OPEN,			//�����J���鉹
	SOUND_LABEL_HOTOVER,		//�ł��t����
	SOUND_LABEL_WHISTLE,		//�z�C�b�X���̉�
	SOUND_LABEL_REGI,		//�{�X���|��鉹
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
#pragma once
