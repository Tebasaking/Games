//=========================================
//
//	missile_alert.h
//	Author:冨所知生
//
//=========================================
#ifndef _ALERT_DIRECTION_H_		//このマクロ定義がされてなかったら
#define _ALERT_DIRECTION_H_		//２重インクルード防止のマクロ定義

#include "object2D.h"

class CAlert_Direction : public CObject2D
{
public:
	CAlert_Direction();			//コンストラクタ
	virtual ~CAlert_Direction() override;			//デストラクタ

										//初期化処理
	HRESULT Init(const D3DXVECTOR3 &pos) override;
	// 更新処理
	void Update(void) override;
	// 描画処理
	void Draw(void) override;
	// 終了処理
	void Uninit(void) override;
	// クリエイト処理
	static CAlert_Direction* Create(const D3DXVECTOR3 &pos, CObject *object);
	// ターゲットを設定したいオブジェクト情報を保存
	void SetObject(CObject *object) { pObject = object; }

	// オブジェクトの取得
	CObject *GetTargetObject() { return pObject; }
	// サイズの取得
	float GetSize() { return m_Size; }
	void SetLockOn(bool LockOn) { m_bLockOn = LockOn; }

private:
	bool				m_bLockOn;			// 追尾しているかしていないかを設定する
	float  m_Size;							// サイズ
	D3DXVECTOR3	m_TargetPos;		// 目標の座標
	D3DXVECTOR3			m_pos;				// 現在の座標
	CObject				*pObject;			// 目標のオブジェクト情報の保存先
};

#endif