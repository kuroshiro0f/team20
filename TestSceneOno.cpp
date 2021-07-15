//#include "TestSceneOno.h"
//#include "Result.h"
//#include "Mark.h"
//#include "Target.h"
//#include "Player.h"
//#include "ObstructManager.h"
//#include "Hitchecker.h"
//#include "UI.h"
//#include "Camera.h"
//#include "Effect.h"
//
//#include "DxLib.h"
//
//
//static int enemyNum = 10;
//
//TestSceneOno::TestSceneOno()
//	:m_player(nullptr)
//	, m_camera(nullptr)
//	, m_mark(nullptr)
//	,m_effect(nullptr)
//	,m_playerOrbitEfk(nullptr)
//	, m_targetCount(0)
//	, m_startTime(0)
//	, m_iceThrowFlag(false)
//	,m_hitCount(0)
//	,m_hitFlag(false)
//{
//	// 次のシーンへ移行するかどうか
//	m_finishFlag = FALSE;
//	// エネミー・スコアUI初期化
//	for (int i = 0; i < enemyNum; i++)
//	{
//		m_score_ui[i] = nullptr;
//		m_hit_ui[i] = nullptr;
//	}
//
//	// ターゲット領域の確保
//	m_targets.resize(enemyNum + 1);
//
//	m_startTime = GetNowCount() / 1000;
//}
//
//TestSceneOno::~TestSceneOno()
//{
//	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
//	delete m_camera;	//	カメラのポインタメンバ変数を消去
//	delete m_mark;		//	マークのポインタメンバ変数を消去
//	StopSoundMem(m_finishSoundHandle);
//	DeleteGraph(m_backGraphHandle);
//	DeleteGraph(m_finishGraphHandle);
//	DeleteSoundMem(m_soundHandle);
//	DeleteSoundMem(m_finishSoundHandle);
//	for (int i = 0; i < enemyNum; i++)
//	{
//		delete m_score_ui[i];		//  スコアUIへのポインタメンバ変数
//		delete m_hit_ui[i];			//	ヒット判定UIへのポインタメンバ変数
//	}
//
//	// 全ターゲットの確保
//	while (!m_targets.empty())
//	{
//		delete m_targets.back();
//		m_targets.pop_back();
//	}
//
//	m_effect->Delete();
//	delete m_effect;
//	m_playerOrbitEfk->Delete();
//	delete m_playerOrbitEfk;
//}
//
//SceneBase* TestSceneOno::Update()
//{
//
//	// デバッグビルドのみデバッグ関数を呼び出す
//#ifdef _DEBUG
//	DebugKey();
//#endif
//
//	// 机の更新
//	m_mark->Mark_Update();
//
//	// エネミー射出管理
//	if (GetNowCount() / 1000 - m_startTime > 1)
//	{
//		m_startTime = GetNowCount() / 1000;
//		m_targets[m_targetCount]->SetIceState(Target_State::NOW_SHOT);
//		m_targetCount++;
//	}
//
//	// 現在の番号に応じてエネミーの更新
//	for (int i = 0; i < m_targetCount; i++)
//	{
//		m_targets[i]->Update();
//	}
//	m_player->Update();
//
//	m_camera->Update(*m_player);
//	for (int i = 0; i < m_targetCount; i++)
//	{
//		HitChecker::Check(*m_player, *m_targets[i]);
//	}
//	if (m_targetCount > enemyNum)	//	エンターが押されたら
//	{
//		m_finishFlag = TRUE;
//	}
//	if (m_finishFlag == TRUE)
//	{
//		WaitTimer(3000);
//		return new Result(m_score_ui[m_targetCount]->GetScore());				//	リザルトシーンに切り替える
//	}
//	return this;						//	ゲームシーンを表示し続ける
//}
//
//void TestSceneOno::Draw()
//{
//	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	タイトル画面の背景を表示
//	m_mark->Mark_Draw();
//	for (int i = 0; i < m_targetCount; i++)
//	{
//		m_targets[i]->Draw();
//	}
//	m_player->Draw();
//	if (m_finishFlag == TRUE)
//	{
//		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	タイトル画面の背景を表示
//	}
//	for (int i = 0; i < enemyNum; ++i)
//	{
//		m_score_ui[i]->Draw();
//	}
//	for (int i = 0; i < m_hitCount; ++i)
//	{
//		m_hit_ui[i]->Draw();
//	}
//
//	// エフェクトの再生
//	if (!(m_effect->GetNowPlaying() == 0))
//	{
//		m_effect->PlayEffekseer(VGet(0, 20, 0));
//	}
//
//	// プレイヤーの軌道エフェクト
//	if (m_playerOrbitEfk->GetNowPlaying() != 0)
//	{
//		m_playerOrbitEfk->PlayEffekseer(m_player->GetPos());
//		VECTOR efkDir = VGet(0.0f, DX_PI_F, 0.0f);
//		m_playerOrbitEfk->SetPlayingEffectRotation(efkDir);
//	}
//	else
//	{
//		// エフェクト再生中はプレイヤーの座標を追尾
//		m_playerOrbitEfk->SetPlayingEffectPos(m_player->GetPos());
//	}
//	
//}
//
//void TestSceneOno::Sound()
//{
//	if (m_finishFlag == TRUE)
//	{
//		StopSoundMem(m_soundHandle);
//		PlaySoundMem(m_finishSoundHandle, DX_PLAYTYPE_BACK, FALSE);
//		ChangeVolumeSoundMem(m_volumePal, m_finishSoundHandle);
//	}
//	if (m_finishFlag == FALSE)
//	{
//		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK, FALSE);
//		ChangeVolumeSoundMem(m_volumePal, m_soundHandle);
//	}
//}
//
//void TestSceneOno::Load()
//{
//	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	グラフィックハンドルにゲーム終了文字のイメージをセット
//	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	グラフィックハンドルにゲーム画面のイメージをセッ
//	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	サウンドハンドルにゲーム画面のBGMをセット
//	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	サウンドハンドルにゲーム終了時の効果音をセット
//	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
//	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
//	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
//	m_mark = new Mark;				//	マーククラスのインスタンスを生成
//
//	// ターゲットの生成
//	for (int i = 0; i < m_targets.size(); i++)
//	{
//		m_targets[i] = new Target();
//	}
//
//	for (int i = 0; i < 2; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//		{
//			m_score_ui[j + (i * 5)] = new UI(j, i, scoreHandle);
//			m_hit_ui[j + (i * 5)] = new UI(j, i, -1);
//		}
//	}
//	// UIクラスのprivateメンバ変数に画像ハンドルをロード
//	m_score_ui[0]->Load();
//
//	m_effect = new PlayEffect("data/effects/FeatherBomb.efk");
//	m_playerOrbitEfk = new PlayEffect("data/effects/PlayerLine.efk");
//
//}
//
//void TestSceneOno::DebugKey()
//{
//	// 確認用
//	if (CheckHitKey(KEY_INPUT_A))
//	{
//		if (m_hitCount < enemyNum)
//		{
//			m_hitFlag = true;
//			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
//			m_hitCount++;
//		}
//	}
//	if (CheckHitKey(KEY_INPUT_B))
//	{
//		if (m_hitCount < enemyNum)
//		{
//			m_hitFlag = false;
//			//m_hit_ui[m_hitCount]->ScoreUpdate(m_hit_ui[m_hitCount], m_hitFlag);
//			m_hitCount++;
//		}
//	}
//	if (m_iceThrowFlag)
//	{
//		DrawString(1800, 980, "発射", GetColor(255, 255, 255));
//	}
//	else
//	{
//		DrawString(1800, 980, "未発射", GetColor(255, 255, 255));
//	}
//	if (CheckHitKey(KEY_INPUT_RETURN))
//	{
//		m_checkKeyFlag = TRUE;
//	}
//	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	エンターが押されたら
//	{
//		m_finishFlag = TRUE;
//	}
//}
