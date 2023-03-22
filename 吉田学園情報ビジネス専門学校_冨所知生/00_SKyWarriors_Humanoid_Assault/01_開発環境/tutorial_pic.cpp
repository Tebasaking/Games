//==================================================
//
// tutorial_pic.cpp
// Author: 冨所知生
//
//==================================================
#include "application.h"
#include "tutorial_pic.h"
#include "player3D.h"
#include "enemy.h"
#include "fade.h"
#include "texture.h"
#include "meshfield.h"
#include "sphere.h"
#include "camera.h"
#include "title_model.h"
#include "input.h"
#include "missile_alert.h"
#include "player_manager.h"
#include "playerUI.h"
#include "enemy_manager.h"
#include "time.h"
#include "score.h"

//==================================================
// コンストラクタ
//==================================================
CTutorial_Pic::CTutorial_Pic()
{
}

//==================================================
// デストラクタ
//==================================================
CTutorial_Pic::~CTutorial_Pic()
{
}

//=========================================
// 初期化 
//=========================================
HRESULT CTutorial_Pic::Init(const D3DXVECTOR3 &pos)
{
	m_Select = 0;

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		pObject2D[nCnt] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 4);
		pObject2D[nCnt]->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	pObject2D[0]->SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	CInput *pKeyboard = CInput::GetKey();
	if (pKeyboard->GetAcceptJoyPadCount() != 0)
	{
		pObject2D[0]->SetTexture(CTexture::TEXTURE_TUTORIAL_000);
	}
	else
	{
		pObject2D[0]->SetTexture(CTexture::TEXTURE_TUTORIAL_000_MOUSE);
	}

	pObject2D[1]->SetTexture(CTexture::TEXTURE_TUTORIAL_001);
	pObject2D[2]->SetTexture(CTexture::TEXTURE_TUTORIAL_002);

	return S_OK;
}

//=========================================
// 更新処理
//=========================================
void CTutorial_Pic::Update()
{
	CInput *pKeyboard = CInput::GetKey();

	float X = SCREEN_WIDTH * 0.5f;
	float Y = SCREEN_HEIGHT * 0.5f;

	if (pKeyboard->Trigger(JOYPAD_A) || pKeyboard->Trigger(DIK_RETURN))
	{
		pObject2D[m_Select]->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_Select++;
		if (m_Select != 3)
		{
			pObject2D[m_Select]->SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		}
	}

	else if (m_Select == 3)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			pObject2D[nCnt]->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		//モードの設定
		CFade::SetFade(CApplication::MODE_TUTORIAL);
	}
}

//=========================================
// 終了処理
//=========================================
void CTutorial_Pic::Uninit()
{
	Release();
}