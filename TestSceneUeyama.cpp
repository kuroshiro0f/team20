//#include "TestSceneUeyama.h"
//#include "Result.h"
//#include "Mark.h"
//#include "Target.h"
//#include "Player.h"
//#include "ObstructManager.h"
//#include "Hitchecker.h"
//#include "Camera.h"
//
//#include "DxLib.h"
//
//
//TestSceneUeyama::TestSceneUeyama()
//	:m_player(nullptr)
//	, m_camera(nullptr)
//	, m_mark(nullptr)
//	, m_obstructManager(nullptr)
//{
//	m_finishGraphHandle = LoadGraph("data/img/gameEnd.png");		//	グラフィックハンドルにゲーム終了文字のイメージをセット
//	m_backGraphHandle = LoadGraph("data/img/gameBack.png");			//	グラフィックハンドルにゲーム画面のイメージをセッ
//	m_soundHandle = LoadSoundMem("data/sound/gameBgm.ogg");			//	サウンドハンドルにゲーム画面のBGMをセット
//	m_finishSoundHandle = LoadSoundMem("data/sound/gameEnd.wav");		//	サウンドハンドルにゲーム終了時の効果音をセット
//	m_finishFlag = FALSE;
//	for (int i = 0; i < 10; i++)
//	{
//		m_target[i] = nullptr;
//	}
//	StartTime = GetNowCount();
//	if (CheckHitKey(KEY_INPUT_RETURN))
//	{
//		m_checkKeyFlag = TRUE;
//	}
//}
//
//TestSceneUeyama::~TestSceneUeyama()
//{
//	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
//	delete m_camera;	//	カメラのポインタメンバ変数を消去
//	delete m_mark;		//	マークのポインタメンバ変数を消去
//	StopSoundMem(m_finishSoundHandle);
//	DeleteGraph(m_backGraphHandle);
//	DeleteGraph(m_finishGraphHandle);
//	DeleteSoundMem(m_soundHandle);
//	DeleteSoundMem(m_finishSoundHandle);
//	for (int i = 0; i < 10; i++)
//	{
//		delete m_target[i];
//	}
//	//m_obstructManager->DestroyObstructs();
//	/*delete m_obstructManager;*/
//}
//
//SceneBase* TestSceneUeyama::Update()
//{
//	m_mark->Mark_Update();
//	m_target[TargetCount]->Update();
//	m_player->Update();
//	/*m_obstructManager->Update();*/
//	m_camera->Update(*m_player);
//	/*HitChecker::Check(*m_player, *m_obstructManager);*/
//	if (!CheckHitKey(KEY_INPUT_RETURN))
//	{
//		m_checkKeyFlag = FALSE;
//	}
//	if (CheckHitKey(KEY_INPUT_RETURN) && m_checkKeyFlag == FALSE)	//	エンターが押されたら
//	{
//		m_finishFlag = TRUE;
//		return this;						//	ゲームシーンを表示し続ける
//	}
//	if (m_finishFlag == TRUE)
//	{
//		WaitTimer(3000);
//		return new Result;				//	リザルトシーンに切り替える
//	}
//	return this;						//	ゲームシーンを表示し続ける
//}
//
//void TestSceneUeyama::Draw()
//{
//	DrawGraph(0, 0, m_backGraphHandle, TRUE);							//	タイトル画面の背景を表示
//	m_mark->Mark_Draw();
//	m_target[TargetCount]->Draw();
//	m_player->Draw();
//	if (m_finishFlag == TRUE)
//	{
//		DrawGraph(0, 0, m_finishGraphHandle, TRUE);							//	タイトル画面の背景を表示
//	}
//	/*m_obstructManager->Draw();*/
//	/*DrawString(0, 0, "ゲーム画面です", GetColor(255, 255, 255));*/
//}
//
//void TestSceneUeyama::Sound()
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
//
//void TestSceneUeyama::Load()
//{
//	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
//	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
//	m_mark = new Mark;				//	マーククラスのインスタンスを生成
//	for (int i = 0; i < 10; i++)
//	{
//		m_target[i] = new Target;
//	}
//	/*m_obstructManager = new ObstructManager;
//	m_obstructManager->CreateObstructs();*/
//}
