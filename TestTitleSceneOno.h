//#pragma once
//#include "SceneBase.h"
//
//
//class TestTitleScene : public SceneBase
//{
//public:
//
//	enum class TITLE_TRANS_STATE
//	{
//		FIRST_ENTER = 0,
//		SECOND_CHOICE
//	};
//
//	TestTitleScene();
//	~TestTitleScene();
//
//	SceneBase* Update() override;
//	void Draw() override;
//	void Sound() override;
//	void Load() override;
//
//	void UpdateTransparent();
//
//private:
//
//	TITLE_TRANS_STATE m_state;
//
//	unsigned int m_cursolNum;    // 難易度選択時のカーソル番号
//
//	int m_backGraphHandle;				//	タイトル画面・背景のグラフィックハンドル
//	int m_logoGraphHandle;				//	タイトル画面・ロゴのグラフィックハンドル
//	int m_guidanceGraphHandle;			//	タイトル画面・ガイドのグラフィックハンドル
//	int m_soundHandle;					//	タイトル画面・サウンドハンドル
//	int m_click_sound_handle;			//  ENTERで進むときのサウンドハンドル
//										// 毎フレーム透過量
//	int m_permeationAmount;
//	// 透過量
//	int m_transpVal;
//
//	bool m_checkKeyFlag;				//	キーが押されたままかを判定するフラグ
//};