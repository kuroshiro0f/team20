#include "TestSceneKoga.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "UI.h"
#include "Camera.h"

#include "DxLib.h"



static int enemyNum = 10;

TestSceneKoga::TestSceneKoga()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_targetCount(0)
	, m_startTime(0)
	, m_iceThrowFlag(false)
{
	// 次のシーンへ移行するかどうか
	m_finishFlag = FALSE;
	// エネミー・スコアUI初期化
	for (int i = 0; i < enemyNum; i++)
	{
		//m_target[i] = nullptr;
		m_score_ui[i] = nullptr;
		m_hit_ui[i] = nullptr;
	}
	for (int i = 0; i < enemyNum + 1; i++)
	{
		m_target[i] = nullptr;
		//m_score_ui[i] = nullptr;
		//m_hit_ui[i] = nullptr;
	}
	m_startTime = GetNowCount() / 1000;
	
}

TestSceneKoga::~TestSceneKoga()
{
	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
	delete m_camera;	//	カメラのポインタメンバ変数を消去
	delete m_mark;		//	マークのポインタメンバ変数を消去
	StopSoundMem(m_finishSoundHandle);
	DeleteGraph(m_backGraphHandle);
	DeleteGraph(m_finishGraphHandle);
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_finishSoundHandle);
	for (int i = 0; i < enemyNum; i++)
	{
		delete m_target[i];
		delete m_score_ui[i];		//  スコアUIへのポインタメンバ変数
		delete m_hit_ui[i];			//	ヒット判定UIへのポインタメンバ変数
	}
	delete m_target[enemyNum];

}

SceneBase* TestSceneKoga::Update()
{

	// デバッグビルドのみデバッグ関数を呼び出す
#ifdef _DEBUG
	DebugKey();
#endif

	// 机の更新
	m_mark->Mark_Update();

	if (m_targetCount == 0)
	{
		m_target[m_targetCount]->SetSetTime(m_startTime);
	}

	// エネミー射出管理
	if (GetNowCount() / 1000 - m_startTime > 3)
	{
		m_startTime = GetNowCount() / 1000;
		if (m_target[m_targetCount]->GetIceState() == NO_SHOT)
		{
			m_target[m_targetCount]->SetIceState(NOW_SHOT);
		}
		if (m_target[m_targetCount]->GetIceState() == END_SHOT)
		{
			m_target[m_targetCount + 1] ->SetSetTime(m_startTime);
			m_targetCount++;
		}
	}

	// 現在の番号に応じてエネミーの更新
	//for (int i = 0; i < m_targetCount; i++)
	//{
		m_target[m_targetCount]->Update();
		m_target[m_targetCount]->SetTargetCount(m_targetCount);
		m_target[m_targetCount]->Reaction(HitChecker::Check(*m_player, *m_target[m_targetCount]));

	//}
	m_player->Update();

	m_camera->Update(*m_player);

	if (m_targetCount == enemyNum)	//	エンターが押されたら
	{
		m_finishFlag = true;
	}
	if (m_finishFlag == true)
	{
		WaitTimer(3000);
		return new Result;				//	リザルトシーンに切り替える
	}
	return this;						//	ゲームシーンを表示し続ける
}

void TestSceneKoga::Draw()
{
	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	タイトル画面の背景を表示
	m_mark->Mark_Draw();
	for (int i = 0; i <= m_targetCount; i++)
	{
		m_target[i]->Draw();
	}
	m_player->Draw();
	if (m_finishFlag == TRUE)
	{
		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	タイトル画面の背景を表示
	}
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i]->Draw();
	}
	for (int i = 0; i < hitCount; ++i)
	{
		m_hit_ui[i]->Draw();
	}
	/*m_obstructManager->Draw();*/
	/*DrawString(0, 0, "ゲーム画面です", GetColor(255, 255, 255));*/
}

void TestSceneKoga::Sound()
{
	if (m_finishFlag == TRUE)
	{
		StopSoundMem(m_soundHandle);
		PlaySoundMem(m_finishSoundHandle, DX_PLAYTYPE_BACK, FALSE);
		ChangeVolumeSoundMem(m_volumePal, m_finishSoundHandle);
	}
	if (m_finishFlag == FALSE)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
		ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
	}
}

void TestSceneKoga::Load()
{
	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	グラフィックハンドルにゲーム終了文字のイメージをセット
	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	グラフィックハンドルにゲーム画面のイメージをセッ
	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	サウンドハンドルにゲーム画面のBGMをセット
	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	サウンドハンドルにゲーム終了時の効果音をセット
	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
	m_mark = new Mark;				//	マーククラスのインスタンスを生成
	for (int i = 0; i < enemyNum + 1; i++)
	{
		m_target[i] = new Target;
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

}

void TestSceneKoga::DebugKey()
{
	// 確認用
	if (CheckHitKey(KEY_INPUT_A))
	{
		if (hitCount < enemyNum)
		{
			hitFrag = true;
			m_hit_ui[hitCount]->ScoreUpdate(m_hit_ui[hitCount], hitFrag);
			hitCount++;
		}
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		if (hitCount < enemyNum)
		{
			hitFrag = false;
			m_hit_ui[hitCount]->ScoreUpdate(m_hit_ui[hitCount], hitFrag);
			hitCount++;
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
