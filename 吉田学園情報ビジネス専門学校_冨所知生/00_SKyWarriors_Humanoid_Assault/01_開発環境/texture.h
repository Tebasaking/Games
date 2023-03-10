//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		TEXTURE_TEST = 0,			// テストに使用する画像を入れるとこ
		TEXTURE_FIRE,				// 仮画像1
		TEXTURE_NUMBER,				// 仮画像2
		TEXTURE_EXPLOSION,			// 爆発画像
		TEXTURE_SKY,				// 空
		TEXTURE_SEA,				// 海
		TEXTURE_GROUND,				// 陸
		TEXTURE_THUNDER,			// 戦闘機のテクスチャ
		TEXTURE_TARGET,				// ターゲット
		TEXTURE_TITLE,				// タイトル
		TEXTURE_RESULT,				// リザルト
		TEXTURE_RADAR_MAP,			// レーダーマップ
		TEXTURE_FRAME,				// レーダーのフレーム
		TEXTURE_ENEMY_TANK,			// タンク
		TEXTURE_ENEMY_FLY,			// 戦闘機
		TEXTURE_ARROW,				// 矢印
		TEXTURE_WAVE,				// 波
		TEXTURE_PARTIClE,			// パーティクル
		TEXTURE_SMOKE,				// 煙
		TEXTURE_TITLE_LOGO,			// タイトルロゴ
		TEXTURE_TITLE_START,		// スタート
		TEXTURE_TITLE_TUTORIAL,		// チュートリアル
		TEXTURE_TITLE_END,			// エンド
		TEXTURE_EXPLOSION2,			// 爆発テクスチャその2
		TEXTURE_UI_SPEED_AND_ALT,	// プレイヤーのUIスピードと高度
		TEXTURE_UI_WEAPON,			// プレイヤーの武器UI
		TEXTURE_GAGE_BOX,			// リロードのゲージの箱
		TEXTURE_GAGE,				// リロードのゲージ
		TEXTURE_UI_ALERT,			// ミサイルのアラート
		TEXTURE_RANKING,			// ランキングの画像
		TEXTURE_GAME_OVER,			// ゲームオーバーの画像
		TEXTURE_TIME_OVER,			// タイムオーバーの画像
		TEXTURE_TUTORIAL_000,		// TUTORIAL001
		TEXTURE_TUTORIAL_001,		// TUTORIAL002
		TEXTURE_TUTORIAL_002,		// TUTORIAL003
		TEXTURE_STOP,				// ストップ
		TEXTURE_MISSILE_MARK,		// ミサイルのマーク
		TEXTURE_TUTORIAL_GAME,
		TEXTURE_SERIHU_GEKITUI_01,	// 撃墜セリフ01
		TEXTURE_SERIHU_GEKITUI_02,	// 撃墜セリフ02
		TEXTURE_SERIHU_TIME_LIMIT_30,// 残り30秒のタイムリミット
		TEXTURE_MAX,
		TEXTURE_NONE,	// 使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
