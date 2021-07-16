//#include "TestSceneKoga.h"
//#include "Result.h"
//#include "Mark.h"
//#include "Target.h"
//#include "Player.h"
//#include "ObstructManager.h"
//#include "Hitchecker.h"
//#include "UI.h"
//#include "Camera.h"
//
//#include "DxLib.h"
//#include "Effect.h"
//#include "TestScene_fujihara.h"
//
//static int enemyNum = 10;
//static int GIRL_Y = 0;
//static int LADY_Y = 0;
//static int GIRL_MIN_Y = -75;
//static int LADY_MIN_Y = -75;
//
//// ターゲットが飛んでくる間隔 (秒単位)
//static const int TARGET_SHOT_INTERVAL = 3;
//
//TestSceneKoga::TestSceneKoga()
//	:m_player(nullptr)
//	, m_camera(nullptr)
//	, m_mark(nullptr)
//	, m_effect(nullptr)
//	, m_targetCount(0)
//	, m_startTime(0)
//	, m_iceThrowFlag(false)
//	, m_iceHitFlagBuffer(false)
//	, m_girl_Y(GIRL_Y)
//	, m_lady_Y(LADY_Y)
//	, m_girlUpFlag(true)
//	//　確認用
//	, m_hitCount(0)
//	, m_hitFlag(false)
//{
//	// 次のシーンへ移行するかどうか
//	m_finishFlag = FALSE;
//	// エネミー・スコアUI初期化
//	for (int i = 0; i < enemyNum; i++)
//	{
//		m_target[i] = nullptr;
//		m_score_ui[i] = nullptr;
//		m_hit_ui[i] = nullptr;
//	}
//	m_target[enemyNum] = nullptr;
//
//	// 開始時のタイムを取得
//	m_startTime = GetNowCount() / 1000;
//}
//
//TestSceneKoga::~TestSceneKoga()
//{
//	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
//	delete m_camera;	//	カメラのポインタメンバ変数を消去
//	delete m_mark;		//	マークのポインタメンバ変数を消去
//	StopSoundMem(m_finishSoundHandle);
//	DeleteGraph(m_backGraphHandle);
//	DeleteGraph(m_finishGraphHandle);
//	DeleteGraph(m_manualGraphHandle);
//	DeleteGraph(m_girlGraphHandle);
//	DeleteGraph(m_ladyGraphHandle);
//	DeleteSoundMem(m_soundHandle);
//	DeleteSoundMem(m_finishSoundHandle);
//	for (int i = 0; i < enemyNum; i++)
//	{
//		delete m_target[i];
//		delete m_score_ui[i];		//  スコアUIへのポインタメンバ変数
//		delete m_hit_ui[i];			//	ヒット判定UIへのポインタメンバ変数
//	}
//	delete m_target[enemyNum];
//
//	m_effect->Delete();
//	delete m_effect;
//}
//
//SceneBase* TestSceneKoga::Update()
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
//	if (m_targetCount == 0)
//	{
//		m_target[m_targetCount]->SetSetTime(m_startTime);
//	}
//
//
//	// エネミー射出管理
//	if (GetNowCount() / 1000 - m_startTime > TARGET_SHOT_INTERVAL)
//	{
//		m_startTime = GetNowCount() / 1000;
//		if (m_target[m_targetCount]->GetIceState() == NO_SHOT)
//		{
//			m_target[m_targetCount]->SetIceState(NOW_SHOT);
//			PlaySoundMem(m_iceSoundHandle, DX_PLAYTYPE_BACK);
//			ChangeVolumeSoundMem(m_volumePal+20, m_iceSoundHandle);
//		}
//		if (m_target[m_targetCount]->GetIceState() == END_SHOT)
//		{
//			m_target[m_targetCount + 1]->SetSetTime(m_startTime);
//			m_targetCount++;
//		}
//	}
//
//	// 現在の番号に応じてエネミーの更新
//	m_target[m_targetCount]->Update();
//	m_target[m_targetCount]->SetTargetCount(m_targetCount);
//	m_iceHitFlagBuffer = HitChecker::Check(*m_player, *m_target[m_targetCount]);
//	m_target[m_targetCount]->Reaction(m_hit_ui[m_targetCount], m_iceHitFlagBuffer);
//
//	m_player->Update();
//
//	m_camera->Update(*m_player);
//
//
//	// UIの中華娘を動かす
//	if (m_girlUpFlag)
//	{
//		m_girl_Y--;
//		if (m_girl_Y < GIRL_MIN_Y)
//		{
//			m_girl_Y = GIRL_MIN_Y;
//			m_girlUpFlag = false;
//		}
//	}
//	else if (!m_girlUpFlag)
//	{
//		m_girl_Y++;
//		if (m_girl_Y > 0)
//		{
//			m_girl_Y = 0;
//			m_girlUpFlag = true;
//		}
//	}
//
//
//
//	if (m_targetCount == enemyNum)	//	エンターが押されたら
//	{
//		m_finishFlag = TRUE;
//	}
//	if (m_finishFlag == TRUE)
//	{
//		// scoreUIのスコアをResultのscore変数にセット
//
//		WaitTimer(3000);
//		return new Result(m_score_ui[m_targetCount]->GetScore());				//	リザルトシーンに切り替える
//	}
//	return this;						//	ゲームシーンを表示し続ける
//}
//
//void TestSceneKoga::Draw()
//{
//	// 背景
//	DrawGraph(0, 0, m_backGraphHandle, TRUE);
//	// 操作説明系
//	DrawGraph(0, 0, m_manualGraphHandle, TRUE);							//	操作説明を表示
//	DrawGraph(0, m_girl_Y, m_girlGraphHandle, TRUE);
//	DrawGraph(0, m_lady_Y, m_ladyGraphHandle, TRUE);//	タイトル画面の背景を表示
//	// 目印となる机
//	m_mark->Mark_Draw();
//	// ターゲット(アイス)
//	for (int i = 0; i <= m_targetCount; i++)
//	{
//		m_target[i]->Draw();
//	}
//
//	// プレーヤー
//	m_player->Draw();
//
//	// 終了時
//	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
//	{
//		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	最後のエネミーが射出され終わったら"ゲーム終了"の表示
//	}
//	for (int i = 0; i < enemyNum; ++i)
//	{
//		m_score_ui[i]->Draw();
//	}
//	for (int i = 0; i < enemyNum; ++i)
//	{
//		m_hit_ui[i]->Draw();
//	}
//
//	// エフェクトの再生
//	if (!(m_effect->GetNowPlaying() == 0) && m_target[m_targetCount]->GetHitIce())
//	{
//		m_effect->PlayEffekseer(VGet(0, 20, 0));
//		m_target[m_targetCount]->SetHitIce(false);
//	}
//
//	/*m_obstructManager->Draw();*/
//	/*DrawString(0, 0, "ゲーム画面です", GetColor(255, 255, 255));*/
//}
//
//void TestSceneKoga::Sound()
//{
//	if (m_target[enemyNum - 1]->GetIceState() == Target_State::END_SHOT)
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
//void TestSceneKoga::Load()
//{
//	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	グラフィックハンドルにゲーム終了文字のイメージをセット
//	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	グラフィックハンドルにゲーム画面のイメージをセッ
//	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	サウンドハンドルにゲーム画面のBGMをセット
//	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");	//	サウンドハンドルにゲーム終了時の効果音をセット
//	m_girlGraphHandle = LoadGraph("data/img/chinaGirl.png");
//	m_ladyGraphHandle = LoadGraph("data/img/chinaLady.png");
//	m_manualGraphHandle = LoadGraph("data/img/manual.png");			//	グラフィックハンドルに操作説明のイメージをセット
//	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
//	m_iceSoundHandle = LoadSoundMem("data/sound/throwIce.mp3");		//	サウンドハンドルにアイス発射時の効果音をセット
//	m_hitSoundHandle = LoadSoundMem("data/sound/hitIce.mp3");		//	サウンドハンドルにヒット時の効果音をセット
//	m_missSoundHandle = LoadSoundMem("data/sound/missIce.mp3");		//	サウンドハンドルにミス時の効果音をセット
//	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
//	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
//	m_mark = new Mark;				//	マーククラスのインスタンスを生成
//	for (int i = 0; i < (enemyNum + 1); i++)
//	{
//		m_target[i] = new Target;
//		m_target[i]->SetInterval(TARGET_SHOT_INTERVAL);
//		m_target[i]->SetThrowSound(m_iceSoundHandle);
//		m_target[i]->SetHitSound(m_hitSoundHandle);
//		m_target[i]->SetMissSound(m_missSoundHandle);
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
//
//}
//
//void TestSceneKoga::DebugKey()
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
