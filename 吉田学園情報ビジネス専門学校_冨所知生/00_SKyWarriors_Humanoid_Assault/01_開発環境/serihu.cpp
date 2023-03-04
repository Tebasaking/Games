//========================================================
//スコア画面の処理
//========================================================
#include "input.h"
#include "serihu.h"

//======================================================
//コンストラクタ
//======================================================
CSerihu::CSerihu(int nPriority)
{
	//SetType(OBJTYPE_MODE);
}

//=========================================
//デストラクタ
//=========================================
CSerihu::~CSerihu()
{

}

//=========================================
//オブジェクトの初期化処理
//=========================================
HRESULT CSerihu::Init(const D3DXVECTOR3 &pos)
{
	CObject2D::Init(pos);

	//サイズの設定
	CObject2D::SetScale(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	return S_OK;
}

//=========================================
//オブジェクトの更新処理
//=========================================
void CSerihu::Update()
{
	if (m_type != STOP)
	{
		m_Cnt++;

		if (m_Cnt >= 120)
		{
			Uninit();
		}
	}
}

//=========================================
//オブジェクトの終了処理
//=========================================
void CSerihu::Uninit()
{
	//解放処理
	CObject2D::Uninit();
}

//=========================================
//オブジェクトの描画処理
//=========================================
void CSerihu::Draw()
{
	CObject2D::Draw();
}

//=========================================
//オブジェクトのクリエイト
//=========================================
CSerihu* CSerihu::Create(const TYPE type)
{
	int nNumCreate = m_nNumAll;

	CSerihu* pCSerihu = nullptr;

	pCSerihu = new CSerihu();

	if (pCSerihu != nullptr)
	{
		pCSerihu->Init(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pCSerihu->SetType(type);
	}

	return pCSerihu;
}

//========================================================
//スコアの設定処理
//========================================================
void CSerihu::SetType(TYPE type)
{
	m_type = type;
	int nRandom = rand() % 2 + 1;

	switch (type)
	{
	case NONE:
		break;

	case STOP:
		// テクスチャの設定
		CObject2D::SetTexture(CTexture::TEXTURE_STOP);
		break;

	case SHOUT_DOWN:
		if (nRandom == 1)
		{
			// テクスチャの設定
			CObject2D::SetTexture(CTexture::TEXTURE_SERIHU_GEKITUI_01);
		}
		else
		{
			// テクスチャの設定
			CObject2D::SetTexture(CTexture::TEXTURE_SERIHU_GEKITUI_02);
		}
		break;

	case TIME_LIMIT:
		// テクスチャの設定
		CObject2D::SetTexture(CTexture::TEXTURE_SERIHU_TIME_LIMIT_30);
		break;
	}
}
