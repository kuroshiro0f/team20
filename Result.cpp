#include "Result.h"
#include "Title.h"

const int LOGO_X = 0;
const int LOGO_Y = 0;
const int GUIDANCE_X = 0;
const int GUIDANCE_Y = 0;

Result::Result()
{
	m_logoGraphHandle = LoadGraph("data/img/Result_logo.png");			//	グラフィックハンドルにリザルト画面のロゴイメージをセット
	m_guidanceGraphHandle = LoadGraph("data/img/Result_guidance.png");	//	グラフィックハンドルにリザルト画面のガイドイメージをセット
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

Result::~Result()
{
}

SceneBase* Result::Update()
{
	if (!CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = FALSE;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
	{
		return new Title;
	}
	return this;
}

void Result::Draw()
{
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	リザルト画面のロゴを表示
	DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	リザルト画面のロゴを表示
	/*DrawString(0, 0, "リザルト", GetColor(255, 255, 255));*/
}

void Result::Load()
{
}


