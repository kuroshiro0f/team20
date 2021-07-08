#include "Result.h"
#include "Title.h"

const int LOGO_X = 0;
const int LOGO_Y = 0;
const int GUIDANCE_X = 0;
const int GUIDANCE_Y = 0;
const int RESULT_NUM = 3;
const int NICE_P = 5;
const int PF_P = 10;

Result::Result()
	:m_score(6)
{
	if (m_score < NICE_P)
	{
		m_evaluation = 0;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/NEVERGIVEUP.png");		//	グラフィックハンドルにリザルト画面のイメージをセット
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NGU.mp3");			//	サウンドハンドルにリザルト画面の効果音をセット
	}
	if (m_score >= NICE_P && m_score < PF_P)
	{
		m_evaluation = 1;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/NICE.png");				//	グラフィックハンドルにリザルト画面のイメージをセット
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NICE.mp3");		//	サウンドハンドルにリザルト画面の効果音をセット
	}
	if (m_score == PF_P)
	{
		m_evaluation = 2;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/PERFECT.png");			//	グラフィックハンドルにリザルト画面のイメージをセット
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/PF.mp3");			//	サウンドハンドルにリザルト画面の効果音をセット
	}
	/*m_scoreStr(std::to_string(m_score));*/
	m_logoGraphHandle = LoadGraph("data/img/Result_logo.png");				//	グラフィックハンドルにリザルト画面のイメージをセット
	m_scoreGraphHandle = LoadGraph("data/img/Result_score.png");			//	グラフィックハンドルにリザルト画面のイメージをセット
	m_guidanceGraphHandle = LoadGraph("data/img/Result_guidance.png");		//	グラフィックハンドルにリザルト画面のイメージをセット
	m_numGraphHandle[0] = LoadGraph("data/img/0.png");
	m_numGraphHandle[1] = LoadGraph("data/img/1.png");
	m_numGraphHandle[2] = LoadGraph("data/img/2.png");
	m_numGraphHandle[3] = LoadGraph("data/img/3.png");
	m_numGraphHandle[4] = LoadGraph("data/img/4.png");
	m_numGraphHandle[5] = LoadGraph("data/img/5.png");
	m_numGraphHandle[6] = LoadGraph("data/img/6.png");
	m_numGraphHandle[7] = LoadGraph("data/img/7.png");
	m_numGraphHandle[8] = LoadGraph("data/img/8.png");
	m_numGraphHandle[9] = LoadGraph("data/img/9.png");
	m_numGraphHandle[10] = LoadGraph("data/img/10.png");
	//m_bgmSoundHandle = LoadSoundMem("");									//	サウンドハンドルにリザルト画面のBGMをセット
	m_scoreSoundHandle = LoadSoundMem("data/sound/score.mp3");				//	サウンドハンドルにリザルト画面の効果音をセット
	m_numSoundHandle = LoadSoundMem("data/sound/num.mp3");					//	サウンドハンドルにリザルト画面の効果音をセット
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
}

Result::~Result()
{
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_scoreGraphHandle);
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(m_numGraphHandle[i]);
	}
	DeleteGraph(m_evaluationGraphHandle[m_evaluation]);
	DeleteGraph(m_guidanceGraphHandle);
	/*StopSoundMem(m_bgmSoundHandle);
	DeleteSoundMem(m_bgmSoundHandle);*/
	DeleteSoundMem(m_scoreSoundHandle);
	DeleteSoundMem(m_numSoundHandle);
	DeleteSoundMem(m_evaluationSoundHandle[m_evaluation]);
}

SceneBase* Result::Update()
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_volumePal++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_volumePal--;
	}
	/*m_scoreStr(std::to_string(m_score));*/
	if (m_checkResultFlag <= RESULT_NUM)
	{
		WaitTimer(1000);
		m_checkResultFlag++;
	}
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
	if (m_checkResultFlag >= 1)
	{
		DrawGraph(0, 0, m_scoreGraphHandle, TRUE);						//	リザルト画面のロゴを表示
	}
	if (m_checkResultFlag >= 2)
	{
		DrawGraph(0, 0, m_numGraphHandle[m_score], TRUE);				//	リザルト画面のロゴを表示
	}
	if (m_checkResultFlag >= 3)
	{
		DrawGraph(0, 0, m_evaluationGraphHandle[0], TRUE);				//	リザルト画面のロゴを表示
	}
	/*DrawString(0, 0, "リザルト", GetColor(255, 255, 255));*/
}

void Result::Sound()
{
	switch(m_checkResultFlag)
	{
	case 1:
		PlaySoundMem(m_scoreSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal, m_scoreSoundHandle);
		break;
	case 2:
		PlaySoundMem(m_numSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal, m_numSoundHandle);
		break;
	case 3:
		PlaySoundMem(m_evaluationSoundHandle[m_evaluation], DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal, m_evaluationSoundHandle[m_evaluation]);
		break;
	}
	/*PlaySoundMem(m_bgmSoundHandle, DX_PLAYTYPE_LOOP, TRUE);
	ChangeVolumeSoundMem(m_volumePal, m_bgmSoundHandle);*/
}

void Result::Load()
{
}


