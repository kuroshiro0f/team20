#include "Title.h"
#include "Game.h"
#include "TestSceneUeyama.h"

#include "DxLib.h"

const int LOGO_X = 0;			//	ロゴのX座標
const int LOGO_Y = 0;			//	ロゴのY座標
const int GUIDANCE_X = 0;		//	ガイドのX座標
const int GUIDANCE_Y = 0;		//	ガイドのY座標

Title::Title()
{
	m_backGraphHandle = LoadGraph("data/img/Title_back.png");			//	グラフィックハンドルにタイトル画面のイメージをセット
	m_logoGraphHandle = LoadGraph("data/img/Title_logo.png");			//	グラフィックハンドルにタイトル画面のイメージをセット
	m_guidanceGraphHandle = LoadGraph("data/img/Title_guidance.png");	//	グラフィックハンドルにタイトル画面のイメージをセット
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

Title::~Title()
{
}

SceneBase* Title::Update()
{
	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	/*if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		return new Game;
	}*/
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		return new TestSceneUeyama;
	}
	return this;
}

void Title::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	タイトル画面の背景を表示
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	タイトル画面のロゴを表示
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	タイトル画面のガイドを表示
}

void Title::Load()
{
	//	座標とグラフィックハンドルを持ったUIクラスのインスタンスを生成
}
