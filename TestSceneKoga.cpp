#include "TestSceneKoga.h"
#include "Result.h"
#include "Mark.h"
#include "Target.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Hitchecker.h"
#include "Camera.h"

#include "DxLib.h"

TestSceneKoga::TestSceneKoga()
	:m_player(nullptr)
	, m_camera(nullptr)
	, m_mark(nullptr)
	, m_obstructManager(nullptr)
	, m_targetCount(0)
	, m_startTime(0)
	, m_iceThrowFlag(false)
{
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = nullptr;
	}
	m_startTime = GetNowCount() / 1000;
}
TestSceneKoga::~TestSceneKoga()
{
	delete m_player;	//	プレイヤーのポインタメンバ変数を消去
	delete m_camera;	//	カメラのポインタメンバ変数を消去
	delete m_mark;		//	マークのポインタメンバ変数を消去
	for (int i = 0; i < 10; i++)
	{
		delete m_target[i];	//	ターゲットのポインタメンバ変数を消去
	}
	//m_obstructManager->DestroyObstructs();
	//delete m_obstructManager;
}

SceneBase* TestSceneKoga::Update()
{
	m_mark->Mark_Update();
	if (GetNowCount()/1000 - m_startTime > 1 )
	{
		m_startTime = GetNowCount() / 1000;
		m_target[m_targetCount]->SetIsShot(true);
		m_targetCount++;
	}
	
	if (m_iceThrowFlag)
	{
		DrawString(1800, 980, "発射", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(1800, 980, "未発射", GetColor(255, 255, 255));
	}

	for (int i = 0; i < m_targetCount; i++)
	{
		m_target[i]->Update();
	}
	
	
	m_player->Update();
	//m_obstructManager->Update();
	m_camera->Update(*m_player);
	for (int i = 0; i < m_targetCount; i++)
	{
		HitChecker::Check(*m_player, *m_target[i]);
	}
	if (m_targetCount > 10)	//	アイスが10個飛ばし終わったら
	{
		WaitTimer(300);
		return new Result;				//	リザルトシーンに切り替える
	}
	return this;						//	ゲームシーンを表示し続ける
}
void TestSceneKoga::Draw()
{
	m_mark->Mark_Draw();
	for (int i = 0; i < m_targetCount; i++)
	{
		m_target[i]->Draw();
	}
	m_player->Draw();
	//m_obstructManager->Draw();
	DrawString(0, 0, "ゲーム画面です", GetColor(255, 255, 255));

}
void TestSceneKoga::Load()
{
	m_player = new Player;			//	プレイヤークラスのインスタンスを生成
	m_camera = new Camera;			//	カメラクラスのインスタンスを生成
	m_mark = new Mark;				//	マーククラスのインスタンスを生成
	for (int i = 0; i < 10; i++)
	{
		m_target[i] = new Target;
	}
	//m_obstructManager = new ObstructManager;
	//m_obstructManager->CreateObstructs();
}
