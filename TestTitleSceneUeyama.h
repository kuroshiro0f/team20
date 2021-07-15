#pragma once
#include "SceneBase.h"


class TestTitleSceneUeyama : public SceneBase
{
public:

	enum class TITLE_TRANS_STATE
	{
		FIRST_ENTER = 0,
		SECOND_CHOICE
	};

	TestTitleSceneUeyama();					//	コンストラクタ
	~TestTitleSceneUeyama();					//	デストラクタ

	SceneBase* Update(float _deltaTime) override;
	void Draw() override;
	void Sound() override;
	void Load() override;

	void UpdateTransparent();

	//	デルタタイムのセッター
	void SetDeltaTime(float _deltaTime) { m_deltaTime = _deltaTime; }

	//	デルタタイムのゲッター
	float GetDeltaTime() { return m_deltaTime; }

private:
	TITLE_TRANS_STATE m_state;

	unsigned int m_cursolNum;    // 難易度選択時のカーソル番号

	int m_backGraphHandle;				//	タイトル画面・背景のグラフィックハンドル
	int m_logoGraphHandle;				//	タイトル画面・ロゴのグラフィックハンドル
	int m_guidanceGraphHandle;			//	タイトル画面・ガイドのグラフィックハンドル
	int m_soundHandle;					//	タイトル画面・サウンドハンドル
	int m_click_sound_handle;			//  ENTERで進むときのサウンドハンドル
										// 毎フレーム透過量
	int m_permeationAmount;
	// 透過量
	int m_transpVal;
	int m_fadeTransVal;				//	フェードアウト中の透過量
	float m_deltaTime;				//	デルタタイム

	bool m_checkKeyFlag;				//	キーが押されたままかを判定するフラグ
	bool m_fadeInFinishFlag;		//	フェードインの終了判定フラグ
	bool m_fadeOutFlag;				//	フェードアウト開始用のフラグ
	bool m_fadeOutFinishFlag;		//	フェードアウトの終了判定フラグ
};