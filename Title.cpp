#include "Title.h"
#include "Game.h"
#include "TestSceneUeyama.h"
#include "TestSceneKoga.h"

#include "DxLib.h"

const int LOGO_X = 0;			//	ロゴのX座標
const int LOGO_Y = 0;			//	ロゴのY座標
const int GUIDANCE_X = 0;		//	ガイドのX座標
const int GUIDANCE_Y = 0;		//	ガイドのY座標

// 最大透過量
const int defaultTrans = 255;
// 透過量変化用ベクトル
const int transModeration = -1;

Title::Title()
{
	m_backGraphHandle = LoadGraph("data/img/Title_back.png");			//	グラフィックハンドルにタイトル画面のイメージをセット
	m_logoGraphHandle = LoadGraph("data/img/Title_logo.png");			//	グラフィックハンドルにタイトル画面のイメージをセット
	m_guidanceGraphHandle = LoadGraph("data/img/Title_guidance.png");	//	グラフィックハンドルにタイトル画面のイメージをセット
	m_soundHandle = LoadSoundMem("data/sound/titleBgm.ogg");			//	サウンドハンドルにタイトル画面のBGMをセット
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTERで進む際のサウンドをロード
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	// 透過量変数を255に設定
	transParent = defaultTrans;
	// 毎透過量変数を１に設定
	permeationAmount = 1;
}

Title::~Title()
{
	StopSoundMem(m_soundHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_click_sound_handle);		//	ENTERで進むときのサウンドメモリを解放
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_guidanceGraphHandle);
}

SceneBase* Title::Update()
{
	// 透過量が122より大きくなったら
	if (transParent >= defaultTrans)
	{
		// 透過量を255に設定
		transParent=defaultTrans-1;
		// 毎透過量を-1にする
		permeationAmount*= transModeration;
	}
	// 透過量が0より小さければ
	else if (defaultTrans/2 >= transParent )
	{
		// 透過量を設定
		transParent = defaultTrans/2+1;
		// 毎透過量を1にする
		permeationAmount*= transModeration;
	}
	// 毎透過量を透過量に加算する
	transParent += permeationAmount;

	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);
		return new TestSceneUeyama;
	}
	return this;
}

void Title::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	タイトル画面の背景を表示
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	タイトル画面のロゴを表示

	// 透過して描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transParent);
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	タイトル画面のガイドを表示
	// 透過を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::Sound()
{
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK,FALSE);
	ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
}

void Title::Load()
{
	//	座標とグラフィックハンドルを持ったUIクラスのインスタンスを生成
}
