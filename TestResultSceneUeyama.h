#ifndef _TESTRESULTSCENEUEYAMA_H_
#define _TESTRESULTSCENEUEYAMA_H_

#include "SceneBase.h"
#include "UI.h"
//#include <iostream>
//#include <string>

#include "DxLib.h"

class TestResultSceneUeyama : public SceneBase
{
public:
	TestResultSceneUeyama(const int& _score);			//	コンストラクタ
	~TestResultSceneUeyama();			//　デストラクタ

	SceneBase* Update(float _deltaTime)override;	//	更新
	void Draw()override;			//	描画
	void Sound()override;			//	音楽
	void Load()override;			//	初期化

private:
	int m_score;						//	スコア格納変数
	int m_evaluation;
	//string m_scoreStr;				//	スコア表示用変数
	int m_backGraphHandle;				//	背景のグラフィックハンドル
	int m_logoGraphHandle;				//	ロゴのグラフィックハンドル
	int m_guidanceGraphHandle;			//	ガイドのグラフィックハンドル
	int m_scoreGraphHandle;				//	スコアのグラフィックハンドル
	int m_numGraphHandle[11];			//
	int m_evaluationGraphHandle[3];		//	評価のグラフィックハンドル
	// 毎透過量
	int permeationAmount;
	// 透過量
	int transParent;
	int m_click_sound_handle;			//	ENTERで進むときのサウンドハンドル
	int m_bgmSoundHandle;				//	BGMのサウンドハンドル
	int m_scoreSoundHandle;				//	スコアのサウンドハンドル
	int m_numSoundHandle;				//	数表示のサウンドハンドル
	int m_evaluationSoundHandle[3];		//	評価のサウンドハンドル
	int m_checkResultFlag = 0;			//	場面管理用フラグ
	bool m_checkKeyFlag;				//	キーが押されたままかを判定するフラグ
	bool m_fadeInFinishFlag;			//	フェードインの終了判定フラグ
	bool m_fadeOutFlag;					//	フェードアウト開始用のフラグ
	bool m_fadeOutFinishFlag;			//	フェードアウトの終了判定フラグ
};

#endif // _TESTRESULTSCENEUEYAMA_H_

