#include "Result.h"
#include "TestTitleSceneUeyama.h"

const int LOGO_X = 0;
const int LOGO_Y = 0;
const int ICE_VEC_Y = 5;		//  アイスの画像の動く速度
const int ICE_Y = -450;			//  アイスの初期Y座標
const int GUIDANCE_X = 0;
const int GUIDANCE_Y = 0;
const int RESULT_NUM = 3;
const int NICE_P = 5;
const int PF_P = 10;
const int VOLUME_PAL_SUP = 90;

const int SCREEN_SIZE_W = 1920;
const int SCREEN_SIZE_H = 1080;

// 最大透過量
const int defaultTrans = 255;
// 透過量変化用ベクトル
const int transModeration = -1;

const int addAlphaVal = 5;

Result::Result(const int& _score)
	:m_score(_score)
	,m_checkResultFlag(0)
	, m_ice_draw_num(0)
	, m_alphaVal(255)
	, m_fadeInFinishFlag(false)
	, m_fadeOutFlag(false)
	, m_fadeOutFinishFlag(false)
	, m_loadFinishFlag(false)
{
	// 透過量変数を255に設定
	transParent = defaultTrans;
	// 毎透過量変数を１に設定
	permeationAmount = 1;

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	for (int i = 0; i < 11; ++i)
	{
		// i個目のiceの画像にY座標をセット
		m_numGraphY[i] = ICE_Y;
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
	DeleteSoundMem(m_click_sound_handle);					//	ENTERで進むときのサウンドメモリを解放

}

SceneBase* Result::Update(float _deltaTime)
{
	/*if (CheckHitKey(KEY_INPUT_UP))
	{
		m_volumePal++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_volumePal--;
	}*/
	/*m_scoreStr(std::to_string(m_score));*/
	if (m_fadeInFinishFlag)
	{
		//  RESULT_NUM以下ならば
		if (m_checkResultFlag <= RESULT_NUM)
		{
			if (m_checkResultFlag <= 1 || m_checkResultFlag == 3)
			{
				WaitTimer(1000);
				//  時間でUIが描画されるようにするFlag
				m_checkResultFlag++;
			}
			if (m_checkResultFlag == 2)
			{
				//  iceの画像の座標が0になったら
				if (m_numGraphY[m_ice_draw_num] >= 0)
				{
					m_numGraphY[m_ice_draw_num] = 0;
					if (m_ice_draw_num < m_score)
					{
						// 次のICEの描画に移る
						m_ice_draw_num++;
						if (m_numGraphY[m_score - 1] == 0)
						{
							m_ice_draw_num--;
							WaitTimer(1000);
							//  時間でUIが描画されるようにするFlag
							m_checkResultFlag++;
						}
					}
				}
				else
				{
					m_numGraphY[m_ice_draw_num] += ICE_VEC_Y;
				}
				if (m_score == 0)
				{
					WaitTimer(1000);
					m_checkResultFlag++;
				}
			}
		}


		if (!CheckHitKey(KEY_INPUT_RETURN))
		{
			m_checkKeyFlag = FALSE;
		}

		// 透過量が255より大きくなったら
		if (transParent >= defaultTrans)
		{
			// 透過量を121に設定
			transParent = defaultTrans - 1;
			// 毎透過量を-1にする
			permeationAmount *= transModeration;
		}
		// 透過量が0より小さければ
		else if (0 >= transParent)
		{
			// 透過量を１に設定
			transParent = 1;
			// 毎透過量を1にする
			permeationAmount *= transModeration;
		}
		// 毎透過量を透過量に加算する
		transParent += (permeationAmount * 3);

		if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)
		{
			ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_click_sound_handle);
			PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);		//	音が再生し終わるまで待機
			m_fadeOutFlag = true;
		}
		if (m_fadeOutFinishFlag)
		{
			return new TestTitleSceneUeyama;
		}
	}
	return this;
}

void Result::Draw()
{
	DrawGraph(LOGO_X, LOGO_Y, m_logoGraphHandle, TRUE);					//	リザルト画面のロゴを表示

	
	if (m_checkResultFlag >= 1)
	{
		DrawGraph(0, 0, m_scoreGraphHandle, TRUE);						//	リザルト画面のロゴを表示
	}
	if (m_checkResultFlag >= 2)
	{
		if (m_score != 0)
		{
			for (int i = 0; i <= m_ice_draw_num; ++i)
			{
				DrawGraph(0, m_numGraphY[i], m_numGraphHandle[i], TRUE);				//	打ち落とした数のアイスを描画
			}
		}
	}
	if (m_checkResultFlag >= 3)
	{
		// 透過して描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transParent);
		DrawGraph(GUIDANCE_X, GUIDANCE_Y, m_guidanceGraphHandle, TRUE);		//	リザルト画面のロゴを表示
		// 透過を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(0, 0, m_evaluationGraphHandle[m_evaluation], TRUE);				//	リザルト画面のロゴを表示
	}
	if (!m_fadeInFinishFlag)
	{
		// アルファ値の減算
		m_alphaVal -= addAlphaVal;

		// アルファブレンド有効化(ここでアルファ値をセット)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaVal);

		// 画面全体に任意のカラーの四角形を描画
		DrawBox(0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, GetColor(0, 0, 0), TRUE);

		// アルファブレンド無効化
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// アルファ値が最大(255)になったらフェードアウト終了
		if (m_alphaVal <= 0)
		{
			m_fadeInFinishFlag = true;
		}
	}
	// フェードアウト開始
	if (m_fadeOutFlag)
	{
		// アルファ値の加算
		m_alphaVal += addAlphaVal;

		// アルファブレンド有効化(ここでアルファ値をセット)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaVal);

		// 画面全体に任意のカラーの四角形を描画
		DrawBox(0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, GetColor(0, 0, 0), TRUE);

		// アルファブレンド無効化
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// アルファ値が最大(255)になったらフェードアウト終了
		if (m_alphaVal >= 255)
		{
			m_fadeOutFinishFlag = true;
		}
	}
}

void Result::Sound()
{
	switch (m_checkResultFlag)
	{
	case 1:
		PlaySoundMem(m_scoreSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_scoreSoundHandle);
		break;
	case 2:
		// アイスが落ちるときの音を流す
		/*PlaySoundMem(m_numSoundHandle, DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_numSoundHandle);*/
		break;
	case 3:
		//	評価を表示するときの音
		PlaySoundMem(m_evaluationSoundHandle[m_evaluation], DX_PLAYTYPE_BACK, TRUE);
		ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_evaluationSoundHandle[m_evaluation]);
		break;
	}
	/*PlaySoundMem(m_bgmSoundHandle, DX_PLAYTYPE_LOOP, TRUE);
	ChangeVolumeSoundMem(m_volumePal, m_bgmSoundHandle);*/
}

void Result::Load()
{
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTERで進む際のサウンドをロード

	if (m_score < NICE_P)
	{
		m_evaluation = 0;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/result_02_png/Result _01_neverGiveLogo.png");		//	グラフィックハンドルにリザルト画面のイメージをセット
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NGU.mp3");			//	サウンドハンドルにリザルト画面の効果音をセット
	}
	if (m_score >= NICE_P && m_score < PF_P)
	{
		m_evaluation = 1;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/result_02_png/Result _01_niceLogo.png");				//	グラフィックハンドルにリザルト画面のイメージをセット
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/NICE.mp3");		//	サウンドハンドルにリザルト画面の効果音をセット
	}
	if (m_score == PF_P)
	{
		m_evaluation = 2;
		m_evaluationGraphHandle[m_evaluation] = LoadGraph("data/img/result_02_png/Result _01_perfectLogo.png");			//	グラフィックハンドルにリザルト画面のイメージをセット
		m_evaluationSoundHandle[m_evaluation] = LoadSoundMem("data/sound/PF.mp3");			//	サウンドハンドルにリザルト画面の効果音をセット
	}
	/*m_scoreStr(std::to_string(m_score));*/
	m_logoGraphHandle = LoadGraph("data/img/result_02_png/Result _01_backGround.png");				//	グラフィックハンドルにリザルト画面のイメージをセット
	// m_scoreGraphHandle = LoadGraph("data/img/Result_score.png");			//	グラフィックハンドルにリザルト画面のイメージをセット
	m_guidanceGraphHandle = LoadGraph("data/img/result_02_png/Result_01_EnterLogo.png");		//	グラフィックハンドルにリザルト画面のイメージをセット
	m_numGraphHandle[0] = LoadGraph("data/img/result_02_png/Result.png");
	m_numGraphHandle[1] = LoadGraph("data/img/result_02_png/Result_01_ice02.png");
	m_numGraphHandle[2] = LoadGraph("data/img/result_02_png/Result_01_ice03.png");
	m_numGraphHandle[3] = LoadGraph("data/img/result_02_png/Result_01_ice04.png");
	m_numGraphHandle[4] = LoadGraph("data/img/result_02_png/Result_01_ice05.png");
	m_numGraphHandle[5] = LoadGraph("data/img/result_02_png/Result_01_ice06.png");
	m_numGraphHandle[6] = LoadGraph("data/img/result_02_png/Result_01_ice07.png");
	m_numGraphHandle[7] = LoadGraph("data/img/result_02_png/Result_01_ice08.png");
	m_numGraphHandle[8] = LoadGraph("data/img/result_02_png/Result_01_ice09.png");
	m_numGraphHandle[9] = LoadGraph("data/img/result_02_png/Result_01_ice10.png");
	m_numGraphHandle[10] = LoadGraph("data/img/result_02_png/Result_01_ice11.png");
	//m_bgmSoundHandle = LoadSoundMem("");									//	サウンドハンドルにリザルト画面のBGMをセット
	m_scoreSoundHandle = LoadSoundMem("data/sound/score.mp3");				//	サウンドハンドルにリザルト画面の効果音をセット
	m_numSoundHandle = LoadSoundMem("data/sound/num.mp3");					//	サウンドハンドルにリザルト画面の効果音をセット
}