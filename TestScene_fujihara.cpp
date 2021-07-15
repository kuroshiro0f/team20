#include "TestScene_fujihara.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "UI.h"
#include "Camera.h"

#include "DxLib.h"
#include "Effect.h"

static int enemyNum = 10;
static int GIRL_Y = 0;
static int LADY_Y = 0;
static int GIRL_MIN_Y = -75;
static int LADY_MIN_Y = -75;
static int COUNTDOWN = 6;
static int GONG_VOLUME_PAL = 30;

// ターゲットが飛んでくる間隔 (秒単位)
const int TARGET_SHOT_INTERVAL = 3;
const int SCREEN_SIZE_W = 1920;
const int SCREEN_SIZE_H = 1080;


TestScene_fujihara::TestScene_fujihara()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_effect(nullptr)
	, m_targetCount(0)
	, m_startTime(0)
	, m_iceThrowFlag(false)
	, m_iceHitFlagBuffer(false)
	, m_girl_Y(GIRL_Y)
	, m_lady_Y(LADY_Y)
	, m_girlUpFlag(true)
	//　確認用
	, m_hitCount(0)
	, m_hitFlag(false)
	, m_girl_hitReactionFlag(false)
	, m_girl_missReactionFlag(false)
	, m_girl_ReactionFlag(false)
{
	// 次のシーンへ移行するかどうか
	m_finishFlag = FALSE;
	// エネミー・スコアUI初期化
	for (int i = 0; i < enemyNum; i++)
	{
		m_target[i] = nullptr;
		m_score_ui[i] = nullptr;
		m_hit_ui[i] = nullptr;
	}
	m_target[enemyNum] = nullptr;

	// 開始時のタイムを取得
	m_startTime = GetNowCount() / 1000;
	// ステートセット(カウントダウンから)
	m_state = GAME_SCENE_STATE::COUNTDOWN;
}

TestScene_fujihara::~TestScene_fujihara()
{
	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
	delete m_camera;	//	カメラのポインタメンバ変数を消去
	delete m_mark;		//	マークのポインタメンバ変数を消去
	StopSoundMem(m_finishSoundHandle);
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_finishGraphHandle);
	DeleteGraph(m_manualGraphHandle);
	DeleteGraph(m_girlGraphHandle);					//  女の子の画像メモリを開放する
	DeleteGraph(m_girl_missReaction_GraphHandle);	//  女の子の画像メモリを開放する
	DeleteGraph(m_girl_hitReaction_GraphHandle);	//  女の子の画像メモリを開放する
	DeleteGraph(m_ladyGraphHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_finishSoundHandle);
	DeleteSoundMem(m_iceSoundHandle);
	DeleteSoundMem(m_missSoundHandle);
	DeleteSoundMem(m_hitSoundHandle);
	for (int i = 0; i < enemyNum; i++)
	{
		delete m_target[i];
		delete m_score_ui[i];		//  スコアUIへのポインタメンバ変数
		delete m_hit_ui[i];			//	ヒット判定UIへのポインタメンバ変数
	}
	delete m_target[enemyNum];

	m_effect->Delete();
	delete m_effect;
}

SceneBase* TestScene_fujihara::Update()
{

	// デバッグビルドのみデバッグ関数を呼び出す
#ifdef _DEBUG
	DebugKey();
#endif

	switch (m_state)
	{
	case GAME_SCENE_STATE::COUNTDOWN:
		if ((COUNTDOWN + 1) - (GetNowCount() / 1000 - m_startTime) <= 1)
		{
			m_startTime = GetNowCount() / 1000;
			m_state = GAME_SCENE_STATE::GAME;
		}
		break;
	case GAME_SCENE_STATE::GAME:
		// 机の更新
		m_mark->Mark_Update();

		if (m_targetCount == 0)
		{
			m_target[m_targetCount]->SetSetTime(m_startTime);
		}


		// エネミー射出管理
		if (GetNowCount() / 1000 - m_startTime > TARGET_SHOT_INTERVAL)
		{
			m_startTime = GetNowCount() / 1000;
			if (m_target[m_targetCount]->GetIceState() == NO_SHOT)
			{
				m_target[m_targetCount]->SetIceState(NOW_SHOT);
				PlaySoundMem(m_iceSoundHandle, DX_PLAYTYPE_BACK);
				ChangeVolumeSoundMem(m_volumePal + 20, m_iceSoundHandle);
			}
			if (m_target[m_targetCount]->GetIceState() == END_SHOT)
			{

				m_girl_ReactionFlag = false;						// 女の子がリアクションしないようにする
				m_girl_hitReactionFlag = false;
				m_girl_missReactionFlag = false;
				m_target[m_targetCount + 1]->SetSetTime(m_startTime);
				m_targetCount++;
			}
		}

		// 現在の番号に応じてエネミーの更新
		m_target[m_targetCount]->Update();
		m_target[m_targetCount]->SetTargetCount(m_targetCount);
		m_iceHitFlagBuffer = HitChecker::Check(*m_player, *m_target[m_targetCount]);
		// x,y,z軸のそれぞれのポジションを取得
		m_target[m_targetCount]->SetSinglePosX();
		// m_iceHitFlagBufferがtrueになったら
		if (!m_girl_ReactionFlag && m_target[m_targetCount]->GetIceState() == NOW_SHOT)
		{
			if (m_iceHitFlagBuffer)
			{
				m_girl_ReactionFlag = true;			// 女の子がリアクションする
				m_girl_hitReactionFlag = true;		// 女の子がHITした時のリアクションをする
			}
			else if (m_target[m_targetCount]->GetPosX() <= -80)
			{
				m_girl_ReactionFlag = true;			// 女の子がリアクションする
				m_girl_missReactionFlag = true;		// 女の子がmissした時のリアクションをする
			}
		}
		m_target[m_targetCount]->Reaction(m_hit_ui[m_targetCount], m_iceHitFlagBuffer);

		m_player->Update();

		m_camera->Update(*m_player);


		// UIの中華娘を動かす
		if (m_girlUpFlag)
		{
			m_girl_Y--;
			if (m_girl_Y < GIRL_MIN_Y)
			{
				m_girl_Y = GIRL_MIN_Y;
				m_girlUpFlag = false;
			}
		}
		else if (!m_girlUpFlag)
		{
			m_girl_Y++;
			if (m_girl_Y > 0)
			{
				m_girl_Y = 0;
				m_girlUpFlag = true;
			}
		}



		if (m_targetCount == enemyNum)
		{
			m_finishFlag = TRUE;
		}
		if (m_finishFlag == TRUE)
		{
			// scoreUIのスコアをResultのscore変数にセット
			return new Result(m_score_ui[m_targetCount]->GetScore());				//	リザルトシーンに切り替える
		}
		break;
	default:
		break;
	}
	return this;						//	ゲームシーンを表示し続ける
}


void TestScene_fujihara::Draw()
{
	// 背景
	DrawGraph(0, 0, m_backGraphHandle, TRUE);
	DrawGraph(0, m_girl_Y, m_girlGraphHandle, TRUE);
	//女の子のリアクション描画
	if (m_girl_hitReactionFlag == true)				// hitしたならば
	{
		DrawGraph(300, m_girl_Y + 450, m_girl_hitReaction_GraphHandle, TRUE);
	}
	else if (m_girl_missReactionFlag == true)		// missしたならば
	{
		DrawGraph(300, m_girl_Y + 450, m_girl_missReaction_GraphHandle, TRUE);
	}
	DrawGraph(0, m_lady_Y, m_ladyGraphHandle, TRUE);//	タイトル画面の背景を表示
	// 目印となる机
	m_mark->Mark_Draw();
	// ターゲット(アイス)
	for (int i = 0; i <= m_targetCount; i++)
	{
		m_target[i]->Draw();
	}

	// プレーヤー
	m_player->Draw();

	// 終了時
	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
	{
		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	最後のエネミーが射出され終わったら"ゲーム終了"の表示
	}
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i]->Draw();
	}
	for (int i = 0; i < enemyNum; ++i)
	{
		m_hit_ui[i]->Draw();
	}

	// エフェクトの再生
	if (!(m_effect->GetNowPlaying() == 0) && m_target[m_targetCount]->GetHitIce())
	{
		m_effect->PlayEffekseer(VGet(0, 20, 0));
		m_target[m_targetCount]->SetHitIce(false);
	}

	if (m_state == GAME_SCENE_STATE::COUNTDOWN)
	{
		// 透過して描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
		DrawBox(0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, GetColor(0, 0, 0), TRUE);
		// 透過を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	DrawGraph(0, 0, m_manualGraphHandle, TRUE);							//	操作説明を表示
	// カウントダウンの描画
	if (m_state == GAME_SCENE_STATE::COUNTDOWN)
	{
		int Count = (COUNTDOWN)-(GetNowCount() / 1000 - m_startTime);
		DrawExtendFormatString(960, 540, 10.0, 10.0, GetColor(255, 0, 0), "%d", Count);
	}

	/*m_obstructManager->Draw();*/
	/*DrawString(0, 0, "ゲーム画面です", GetColor(255, 255, 255));*/
}

void TestScene_fujihara::Sound()
{
	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
	{
		StopSoundMem(m_soundHandle);
		PlaySoundMem(m_finishSoundHandle, DX_PLAYTYPE_BACK, FALSE);
		ChangeVolumeSoundMem(m_volumePal + GONG_VOLUME_PAL, m_finishSoundHandle);
	}
	if (m_finishFlag == FALSE)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
		ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
	}
}

void TestScene_fujihara::Load()
{
	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	グラフィックハンドルにゲーム終了文字のイメージをセット
	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	グラフィックハンドルにゲーム画面のイメージをセッ
	// m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	サウンドハンドルにゲーム画面のBGMをセット
	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	サウンドハンドルにゲーム終了時の効果音をセット
	m_girlGraphHandle = LoadGraph("data/img/chinaGirl.png");
	m_girl_missReaction_GraphHandle = LoadGraph("data/img/chinaGirl_aseri(01).png");	//  女の子の反応の画像ハンドルをロード
	m_girl_hitReaction_GraphHandle = LoadGraph("data/img/chinaGirl_iine.png");			//  女の子の反応の画像ハンドルをロード
	m_ladyGraphHandle = LoadGraph("data/img/chinaLady.png");
	m_manualGraphHandle = LoadGraph("data/img/manual.png");			//	グラフィックハンドルに操作説明のイメージをセット
	m_iceSoundHandle = LoadSoundMem("data/sound/throwIce.mp3");		//	サウンドハンドルにアイス発射時の効果音をセット
	m_hitSoundHandle = LoadSoundMem("data/sound/hitIce.mp3");		//	サウンドハンドルにヒット時の効果音をセット
	m_missSoundHandle = LoadSoundMem("data/sound/missIce.mp3");		//	サウンドハンドルにミス時の効果音をセット
	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
	m_mark = new Mark;				//	マーククラスのインスタンスを生成
	for (int i = 0; i < (enemyNum + 1); i++)
	{
		m_target[i] = new Target;
		m_target[i]->SetInterval(TARGET_SHOT_INTERVAL);
		m_target[i]->SetAccel(0.025f);
		m_target[i]->SetThrowSound(m_iceSoundHandle);
		m_target[i]->SetHitSound(m_hitSoundHandle);
		m_target[i]->SetMissSound(m_missSoundHandle);
		// m_target[i]->SetAccelVec()
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			m_score_ui[j + (i * 5)] = new UI(j, i, scoreHandle);
			m_hit_ui[j + (i * 5)] = new UI(j, i, -1);
		}
	}
	// UIクラスのprivateメンバ変数に画像ハンドルをロード
	m_score_ui[0]->Load();

	m_effect = new PlayEffect("data/effects/FeatherBomb.efk", 5.0f);

}

void TestScene_fujihara::DebugKey()
{
	// 確認用
	if (CheckHitKey(KEY_INPUT_A))
	{
		if (m_hitCount < enemyNum)
		{
			m_hitFlag = true;
			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
			m_hitCount++;
		}
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		if (m_hitCount < enemyNum)
		{
			m_hitFlag = false;
			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
			m_hitCount++;
		}
	}
	if (m_iceThrowFlag)
	{
		DrawString(1800, 980, "発射", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(1800, 980, "未発射", GetColor(255, 255, 255));
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		m_checkKeyFlag = TRUE;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	エンターが押されたら
	{
		m_finishFlag = TRUE;
	}
}
