//=========================================
//
//	object.h
//	Author:冨所知生
//
//
//=========================================
#ifndef _OBJECT_H_		//このマクロ定義がされてなかったら
#define _OBJECT_H_		//２重インクルード防止のマクロ定義
#define MAX_OBJECT (10000)

#include "main.h"

class CObject
{
public:
	//オブジェクトの種類
	enum EObjType
	{
		OBJECT_NONE,		// 初期タイプ
		OBJECT_PLAYER,		// プレイヤー
		OBJECT_ENEMY,		// エネミー
		OBJECT_BULLET,		// 弾の種類
		OBJECT_RADAR,		// レーダーのオブジェクト
		OBJECT_MESH,		// メッシュフィールド
		OBJECT_TARGET,		// ターゲット
		OBJECT_EMPTY,		// 設定されていない
		OBJECT_FADE,
		OBJECT_ALERT,		// アラート
		OBJECT_EFFECT,		// エフェクト
		OBJECT_ALERT_MANAGAER,	// アラートのマネージャ―専用、急ごしらえ
//		OBJECT_BILLBOARD,	// ビルボード
		OBJECT_MAX
	};

	enum Priority
	{
		LAYER_ONE,
		LAYER_TWO,
		LAYER_THREE,
		LAYER_FOUR,
		LAYER_FIVE,
		LAYER_MAX
	};

	enum Object_mode
	{
		NONE_MODE = -1,
		NORMAL_MODE = 0,
		TITLE_MODE,
		RADAR_MODE,
		MAX_MODE
	};

	explicit CObject(int nPriority = LAYER_ONE);			//コンストラクタ
	virtual ~CObject();			//デストラクタ

	virtual HRESULT Init(const D3DXVECTOR3 &pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0; 

	static void UpdateAll();
	static void DrawAll(Object_mode mode);
	static void UninitAll();

	// 角度の正規化
	D3DXVECTOR3 NormalizeRotXYZ(D3DXVECTOR3 Rot);
	float NormalizeRot(float fRot);

	// クォータニオンの設定
	void SetQuaternion(const D3DXQUATERNION quaternion) { m_quaternion = quaternion; }

	const D3DXVECTOR3& GetPosition() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const float& GetScale() const { return m_scale; }
	const D3DXVECTOR3& GetSize() const { return m_size; }

	// ゲッター
	CObject	*GetObjectinfo() { return this; }
	int		GetNumber() { return m_Number; }
	int		GetHP() { return m_HP; }
	bool	GetTargeting() { return m_Targeting; }
	bool	GetCollision() { return m_Collision; }
	static  CObject *GetObjectTop(int nPriority) { return m_pTop[nPriority]; }
	static  CObject *GetObjectType(CObject::EObjType type);
	CObject *GetObjectNext() { return m_pNext; }
	EObjType GetObjectType() { return m_type; }

	// セッター
	void SetHP(int HP) { m_HP = HP; }
	void SetPosition(const D3DXVECTOR3& pos);
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetObjectType(EObjType type) { m_type = type; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetCollision(bool bCollision) { m_Collision = bCollision; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXQUATERNION& GetQuaternion() { return m_quaternion; }

	D3DXVECTOR3 GetPosOld() { return m_posOld; }

	// マトリックス
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }				// ワールドマトリックスのセッター
	D3DXMATRIX *GetMtxWorld() { return &m_mtxWorld; }								// ワールドマトリックスのゲッター

	void Release();
	void DFlagDelete();

	// 2点から角度を求める
	D3DXVECTOR3 AtanRot(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
	int ManageHP(int Value);

	// 引数 : ずらす座標の大きさ、クォータニオン、目標座標
	D3DXVECTOR3 MtxPos(D3DXVECTOR3 pos, D3DXQUATERNION qua, D3DXVECTOR3 TargetPos);
	// 引数 : ずらす座標の大きさ、角度、目標座標
	D3DXVECTOR3 MtxPosRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 TargetPos);
	// 引数 : 座標、古い座標、目標座標、サイズ、目標サイズ、押し返すか返さないか
	bool Collision(CObject *Target, bool bExtrude);
	// 引数: 目標の座標 、 扇の中心 、 範囲(角度) 、長さ , 方向(角度)
	bool SearchEye(D3DXVECTOR3 Vec1, D3DXVECTOR3 Vec2, float rangeRadian, float length, float directionDegree);

protected:
	static int	m_nNumObject;
	static int m_nNumAll;
	int m_nID;
	int m_Number;								// 何番目のオブジェクトか(番号カウントは各自で)

private:
	bool m_Targeting;							// ターゲットの対象になっているかいないか
	bool m_DeathFlag;							// 死亡フラグ
	bool bCollision;							// 当たり判定
	int m_Priority;								// プライオリティ
	static CObject *m_pTop[LAYER_MAX];			// 先頭のオブジェクトへのポインタ
	static CObject *m_pCurrent[LAYER_MAX];		// 現在(一番後ろ)のオブジェクトへのポインタ
	CObject *m_pNext;							// 自分の次のオブジェクトへのポインタ
	CObject *m_pPrev;							// 自分の一つ前のオブジェクトへのポインタ
	EObjType m_type;
	D3DXVECTOR3 m_pos;							// 座標設定
	D3DXVECTOR3 m_size;							// 大きさ設定
	D3DXVECTOR3 m_rot;							// 回転設定
	D3DXVECTOR3 m_posOld;						// 古い座標
	D3DXMATRIX	m_mtxWorld;						// ワールドマトリックス
	D3DXQUATERNION		m_quaternion;			//クォータニオン
	Object_mode m_objmode;						// オブジェクトの描画モード
	float		m_scale;						// 拡大率設定
	int			m_HP;							// 体力
	bool		m_Collision;					// 当たり判定
};

#endif