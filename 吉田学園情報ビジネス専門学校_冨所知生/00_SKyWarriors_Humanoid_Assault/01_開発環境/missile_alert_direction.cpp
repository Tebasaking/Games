//=========================================
//
//	ミサイルアラートの処理
//	Author:冨所知生
//
//=========================================
#include "missile_alert_direction.h"
#include "camera.h"
#include "application.h"
#include "debug_proc.h"
#include "bullet3D.h"

//D3DXVECTOR3 CAlert_Direction::m_TargetPos = {};
//=========================================
//コンストラクタ
//=========================================
CAlert_Direction::CAlert_Direction()
{

}

//=========================================
//デストラクタ
//=========================================
CAlert_Direction::~CAlert_Direction()
{

}

//=========================================
//オブジェクトの初期化処理
//=========================================
HRESULT CAlert_Direction::Init(const D3DXVECTOR3 &pos)
{
	//初期化処理
	CObject2D::Init(pos);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_ARROW);

	//サイズの設定
	CObject2D::SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// タイプ設定
	//SetObjectType(OBJECT_TARGET);

	return S_OK;
}

//=========================================
//オブジェクトの更新処理
//=========================================
void CAlert_Direction::Update()
{
	if (!m_bLockOn)
	{
		return;
	}

	D3DXVECTOR3 BulletPos;			// エネミーの変換前座標
	D3DXVECTOR3 PlayerPos;			// プレイヤーの座標
	D3DXVECTOR3 ScreenPlayer;		// プレイヤーのSCREEN座標

	m_Size = 50.0f;

	//プレイヤーの座標を取得
	if (pObject != nullptr)
	{
		// 目標の座標をスクリーン座標に変換する
		BulletPos = pObject->GetPosition();
		m_TargetPos = CApplication::WorldToScreen(BulletPos);
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CObject *object = CObject::GetObjectTop(nCnt);

		//プレイヤーの座標を取得
		while (object)
		{
			if (object != nullptr)
			{
				EObjType ObjType = object->GetObjectType();

				if (ObjType == OBJECT_PLAYER)
				{
					PlayerPos = object->GetPosition();

					break;
				}
			}
			object = object->GetObjectNext();
		}
	}

	float length = D3DXVec3Length(&(BulletPos - PlayerPos));
	m_Size = 10.0f + ((1 / ((length) + 1)) * 100000.0);

	if (m_Size >= 70.0f)
	{
		m_Size = 70.0f;
	}

	CDebugProc::Print("%f\n",m_Size);

	//サイズの設定
	CObject2D::SetScale(D3DXVECTOR3(m_Size, m_Size, 0.0f));

	// アラートのX制限の始点
	float ALERT_SCREEN_WIDTH_BEGIN = 300.0f;

	// アラートのX制限の終点
	float ALERT_SCREEN_WIDTH_END = SCREEN_WIDTH - 300.0f;

	// アラートのY制限の始点
	float ALERT_SCREEN_HEIGHT_BEGIN = 500;
	// アラートのY制限の終点
	float ALERT_SCREEN_HEIGHT_END = SCREEN_HEIGHT - 200.0f;

	//// アラート始点制限
	//if (m_TargetPos.x >= ALERT_SCREEN_WIDTH_END)
	//{
	//	m_TargetPos.x = ALERT_SCREEN_WIDTH_END - m_Size;
	//}
	//if (m_TargetPos.y <= ALERT_SCREEN_HEIGHT_BEGIN)
	//{
	//	m_TargetPos.y = ALERT_SCREEN_HEIGHT_BEGIN + m_Size;
	//}

	//// 終点制限
	//if (m_TargetPos.x <= ALERT_SCREEN_WIDTH_BEGIN)
	//{
	//	m_TargetPos.x = ALERT_SCREEN_WIDTH_BEGIN + m_Size;
	//}
	//if (m_TargetPos.y >= ALERT_SCREEN_HEIGHT_END)
	//{
	//	m_TargetPos.y = ALERT_SCREEN_HEIGHT_END - m_Size;
	//}

	ScreenPlayer = CApplication::WorldToScreen(PlayerPos);

	// TargetPosとPlayerPosから角度を求める
	D3DXVECTOR3 rot = ScreenPlayer - m_TargetPos;
	rot.z = atan2f(rot.x, rot.y);
	rot = NormalizeRotXYZ(rot);

	m_TargetPos.x = ScreenPlayer.x + sinf(rot.z) * 100.0f;
	m_TargetPos.y = ScreenPlayer.y + cosf(rot.z) * 100.0f;

	/*D3DXVECTOR3 MoveRot = AtanRot(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),m_TargetPos);

	m_TargetPos = MtxPosRot(D3DXVECTOR3(0.0f,500.0f, 0.0f), MoveRot, D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f ,0.0f));
*/
	// スクリーン座標に設定する
	SetPosition(m_TargetPos);

	// TargetPosとPlayerPosから角度を求める
	rot.y = rot.z;
	//rot = NormalizeRotXYZ(rot);

	SetRotation(rot);

	// 例外処理
	CBullet3D *pBullet = (CBullet3D*)pObject;

	if (pBullet != nullptr)
	{
		if (pBullet->GetSpeed() >= 100)
		{
			SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
}

//=========================================
//オブジェクトの終了処理
//=========================================
void CAlert_Direction::Uninit()
{
	// 終了処理
	CObject2D::Uninit();
}

//=========================================
//オブジェクトの描画処理
//=========================================
void CAlert_Direction::Draw()
{
	if (!m_bLockOn)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRender()->GetDevice();

	// Zテストを使用する
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	{
		// 2Dオブジェクトの描画処理
		CObject2D::Draw();
	}

	// Zテストの終了
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=========================================
//オブジェクトのクリエイト
//=========================================
CAlert_Direction* CAlert_Direction::Create(const D3DXVECTOR3 &pos, CObject *object)
{
	CAlert_Direction* pCAlert = nullptr;

	pCAlert = new CAlert_Direction;

	if (pCAlert != nullptr)
	{
		pCAlert->Init(pos);
	}

	// ターゲットを設定するオブジェクトを取得
	pCAlert->SetObject(object);

	return pCAlert;
}