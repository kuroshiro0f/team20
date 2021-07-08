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

//// 確認用変数
int hitCount = NULL;
bool hitFrag = false;

static int enemyNum = 10;

TestScene_fujihara::TestScene_fujihara()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_target(nullptr)
	, m_obstructManager(nullptr)
{
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i] = nullptr;
		m_hit_ui[i] = nullptr;
	}
}

TestScene_fujihara::~TestScene_fujihara()
{
	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
	delete m_camera;	//	カメラのポインタメンバ変数を消去
	delete m_mark;		//	マークのポインタメンバ変数を消去
	delete m_target;
	m_obstructManager->DestroyObstructs();
	delete m_obstructManager;
	for (int i = 0; i < enemyNum; ++i)
	{
		delete m_score_ui[i];		//  スコアUIへのポインタメンバ変数
		delete m_hit_ui[i];			//	ヒット判定UIへのポインタメンバ変数
	}
}

SceneBase* TestScene_fujihara::Update()
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


	m_mark->Mark_Update();
	m_target->Update();
	m_player->Update();
	m_obstructManager->Update();
	m_camera->Update(*m_player);
	HitChecker::Check(*m_player, *m_obstructManager);
	if (CheckHitKey(KEY_INPUT_RETURN))	//	エンターが押されたら
	{
		WaitTimer(300);
		return new Result;				//	リザルトシーンに切り替える
	}
	return this;						//	ゲームシーンを表示し続ける
}

void TestScene_fujihara::Draw()
{
	m_mark->Mark_Draw();
	m_target->Draw();
	m_player->Draw();
	//m_obstructManager->Draw();
	for (int i = 0; i < enemyNum; ++i)
	{
		m_score_ui[i]->Draw();
	}
	for (int i = 0; i < hitCount; ++i)
	{
		m_hit_ui[i]->Draw();
	}


	DrawString(0, 0, "ゲーム画面です", GetColor(255, 255, 255));
}

void TestScene_fujihara::Load()
{
	int scoreHandle = LoadGraph("data/model/score_ui/score(1).png");
	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
	m_mark = new Mark;				//	マーククラスのインスタンスを生成
	m_target = new Target;			//	的クラスのインスタンスを生成
	// スコア表示のクラスを２０個インスタンス生成
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
	m_obstructManager = new ObstructManager;	//	
	m_obstructManager->CreateObstructs();
}