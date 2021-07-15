#include "TestTitleSceneUeyama.h"
#include "DxLib.h"
#include "GameScene_easy.h"
#include "GameScene_normal.h"
#include "GameScene_hard.h"
#include "TestSceneUeyama.h"

// 最大透過量
const int MAX_TRANSP_VAL = 255;
// 透過量変化用ベクトル
const int TRANSP_MODERATION = -1;

const int FIRST_TRANS_VAL = 100;

// 全難易度
const int ALL_DIFFICULT = 3;

const int SCREEN_SIZE_W = 1920;
const int SCREEN_SIZE_H = 1080;

const int VOLUME_PAL_SUP = 130;

//	フェードインの速度
const int FADE_IN_SPEED = 3;
//	フェードアウトの速度
const int FADE_OUT_SPEED = 3;


TestTitleSceneUeyama::TestTitleSceneUeyama()
	:m_state(TITLE_TRANS_STATE::FIRST_ENTER)
	, m_cursolNum(0)
	, m_fadeInFinishFlag(false)
	, m_fadeOutFlag(false)
	, m_fadeOutFinishFlag(false)
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	// 透過量変数を122に設定
	m_transpVal = MAX_TRANSP_VAL;
	m_fadeTransVal = FIRST_TRANS_VAL;
	// 毎透過量変数を１に設定
	m_permeationAmount = 1;
}

TestTitleSceneUeyama::~TestTitleSceneUeyama()
{
	StopSoundMem(m_soundHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_click_sound_handle);		//	ENTERで進むときのサウンドメモリを解放
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_logoGraphHandle);
	DeleteGraph(m_guidanceGraphHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns> シーンのポインタ </returns>
SceneBase* TestTitleSceneUeyama::Update(float _deltaTime)
{

	// ステートメントごとに処理を変更
	switch (m_state)
	{
	case TITLE_TRANS_STATE::FIRST_ENTER:

		// ※キー入力重複対策のフラグ
		// ENTERキーから指を離したら、次のENTERの入力を有効に
		if (!CheckHitKey(KEY_INPUT_RETURN))
		{
			m_checkKeyFlag = false;
		}

		// ENTERで次のステートへ
		if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == false)
		{
			// ※キー入力重複対策のフラグ
			m_checkKeyFlag = true;
			ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_click_sound_handle);
			PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);

			m_state = TITLE_TRANS_STATE::SECOND_CHOICE;
		}

		break;

	case TITLE_TRANS_STATE::SECOND_CHOICE:

		// ※キー入力重複対策のフラグ
		// ENTERキーから指を離したら、次のENTERの入力を有効に
		if (!CheckHitKey(KEY_INPUT_RETURN) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN))
		{
			m_checkKeyFlag = false;
		}

		// 難易度選択
		if (CheckHitKey(KEY_INPUT_UP) && !m_checkKeyFlag)
		{
			// ※キー入力重複対策のフラグ
			m_checkKeyFlag = true;

			// カーソル制御 (0:イージー、1:ノーマル、2:ハード)
			if (m_cursolNum == 1 || m_cursolNum == 2)
			{
				m_cursolNum--;
			}
			else if (m_cursolNum == 0)
			{
				m_cursolNum = 2;
			}
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) && !m_checkKeyFlag)
		{
			// ※キー入力重複対策のフラグ
			m_checkKeyFlag = true;

			// カーソル制御 (0:イージー、1:ノーマル、2:ハード)
			if (m_cursolNum == 1 || m_cursolNum == 0)
			{
				m_cursolNum++;
			}
			else if (m_cursolNum == 2)
			{
				m_cursolNum = 0;
			}
		}

		// ENTERで選択した難易度のシーンへ
		if (CheckHitKey(KEY_INPUT_RETURN) && !m_checkKeyFlag)
		{
			ChangeVolumeSoundMem(m_volumePal + VOLUME_PAL_SUP, m_click_sound_handle);
			PlaySoundMem(m_click_sound_handle, DX_PLAYTYPE_NORMAL);
			m_fadeOutFlag = true;
		}

		if (m_cursolNum == 0 && m_fadeOutFinishFlag)
		{
			// イージーモードシーンのインスタンスを返す
			return new GameSceneEasy();
		}

		if (m_cursolNum == 1 && m_fadeOutFinishFlag)
		{
			// ノーマルモードのインスタンスを返す
			return new GameSceneNormal();
		}

		if (m_cursolNum == 2 && m_fadeOutFinishFlag)
		{
			// ハードモードのインスタンスを返す
			return new GameSceneHard();
		}

		break;

	default:

		break;
	}



	return this;
}

void TestTitleSceneUeyama::Draw()
{
	if (!m_fadeInFinishFlag)
	{
		// フェードイン処理
		for (int i = 0; i < 255; i += FADE_IN_SPEED)
		{
			// 描画輝度をセット
			SetDrawBright(i, i, i);

			// グラフィックを描画
			DrawGraph(0, 0, m_backGraphHandle, TRUE);
			DrawGraph(0, 0, m_logoGraphHandle, TRUE);
			ScreenFlip();
		}
		m_fadeInFinishFlag = true;
	}
	// 透過量更新
	UpdateTransparent();

	// バックグラウンド
	DrawGraph(0, 0, m_backGraphHandle, TRUE);

	// 選択時にカーソルが見やすいように背景を暗くする
	if (m_state == TITLE_TRANS_STATE::SECOND_CHOICE)
	{
		// 透過して描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
		DrawBox(0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, GetColor(0, 0, 0), TRUE);
		// 透過を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// タイトルロゴ
	DrawGraph(0, 0, m_logoGraphHandle, TRUE);

	// ステートメントごとに処理を変更
	switch (m_state)
	{
	case TITLE_TRANS_STATE::FIRST_ENTER:

		// 透過して描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_transpVal);
		DrawGraph(0, 0, m_guidanceGraphHandle, TRUE);		//	PUSH ENTER
		// 透過を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;

	case TITLE_TRANS_STATE::SECOND_CHOICE:

		//--------------------------------------------------//
		// 難易度選択カーソル
		//-------------------------------------------------//
		// 透過して描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_transpVal);
		// カーソルはDrawBoxで描画
		DrawBox(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 3,
			SCREEN_SIZE_H / 2 + m_cursolNum * 80 - 8,
			SCREEN_SIZE_W / 2 + GetFontSize() * 4 * 3,
			SCREEN_SIZE_H / 2 + m_cursolNum * 80 + 72,
			GetColor(255, 155, 50), TRUE);
		// 透過を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 難易度表示
		for (int i = 0; i < ALL_DIFFICULT; i++)
		{
			if (i == 0)
			{
				DrawExtendFormatString(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 2, SCREEN_SIZE_H / 2 + (i * 80), 4.0, 4.0, GetColor(255, 255, 255), "イージー");
			}

			if (i == 1)
			{
				DrawExtendFormatString(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 2, SCREEN_SIZE_H / 2 + (i * 80), 4.0, 4.0, GetColor(255, 255, 255), "ノーマル");
			}

			if (i == 2)
			{
				DrawExtendFormatString(SCREEN_SIZE_W / 2 - GetFontSize() * 4 * 1.5, SCREEN_SIZE_H / 2 + (i * 80), 4.0, 4.0, GetColor(255, 255, 255), "ハード");
			}
		}

		// フェードアウト処理
		if (m_fadeOutFlag)
		{
			for (int i = 0; i < 255; i += FADE_OUT_SPEED)
			{
				// 描画輝度をセット
				SetDrawBright(255 - i, 255 - i, 255 - i);

				// グラフィックを描画
				DrawGraph(0, 0, m_backGraphHandle, FALSE);
				ScreenFlip();
			}
			m_fadeOutFinishFlag = true;
			
		}
		break;

	default:

		break;
	}

}

/// <summary>
/// サウンドの再生処理
/// </summary>
void TestTitleSceneUeyama::Sound()
{
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
	ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
}

/// <summary>
/// 読み込み処理
/// </summary>
void TestTitleSceneUeyama::Load()
{
	m_backGraphHandle = LoadGraph("data/img/Title_back.png");			//	グラフィックハンドルにタイトル画面のイメージをセット
	m_logoGraphHandle = LoadGraph("data/img/Title_logo.png");			//	グラフィックハンドルにタイトル画面のイメージをセット
	m_guidanceGraphHandle = LoadGraph("data/img/Title_guidance.png");	//	グラフィックハンドルにタイトル画面のイメージをセット
	m_soundHandle = LoadSoundMem("data/sound/titleBgm.ogg");
	m_click_sound_handle = LoadSoundMem("data/sound/EnterToSound.wav");	//	ENTERで進む際のサウンドをロード
}

/// <summary>
/// 点滅エフェクトに用いる透過量の更新処理
/// </summary>
void TestTitleSceneUeyama::UpdateTransparent()
{
	// 透過量が122より大きくなったら
	if (m_transpVal >= MAX_TRANSP_VAL)
	{
		// 透過量を255に設定
		m_transpVal = MAX_TRANSP_VAL - 1;
		// 毎透過量を-1にする
		m_permeationAmount *= TRANSP_MODERATION;
	}
	// 透過量が0より小さければ
	else if (MAX_TRANSP_VAL / 2 >= m_transpVal)
	{
		// 透過量を設定
		m_transpVal = MAX_TRANSP_VAL / 2 + 1;
		// 毎透過量を1にする
		m_permeationAmount *= TRANSP_MODERATION;
	}
	// 毎透過量を透過量に加算する
	m_transpVal += m_permeationAmount;
}
