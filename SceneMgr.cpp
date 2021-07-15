#include "SceneMgr.h"
#include "Title.h"
#include "Result.h"
#include "TestSceneUeyama.h"

#include "DxLib.h"

SceneMgr::SceneMgr()
{
	m_scene = nullptr;		//	メンバ変数の初期化
}

SceneMgr::~SceneMgr()
{
	delete m_scene;			//	メンバ変数の消去
}

void SceneMgr::Update(float _deltaTime)
{
	SceneBase* tmpScene = m_scene->Update(_deltaTime);		//	現在のシーンを保存(publicの関数・変数を呼び出すときはアロー演算子(->)　要調査)
	if (tmpScene != m_scene)						//	シーンが切り替わった時
	{
		delete m_scene;								//	直前のシーンを消す
		m_scene = tmpScene;							//	シーンを更新する
		m_scene->Load();							//	シーンの初期化
	}
}

void SceneMgr::Draw()
{
	m_scene->Draw();		//	シーンを描画
}

void SceneMgr::Sound()
{
	m_scene->Sound();		//	BGMを流す
}

void SceneMgr::SetScene(SceneBase* _Scene)
{
	if (m_scene != nullptr)	//	m_Sceneが空ではない場合
	{
		delete m_scene;		//	m_Sceneを消去
	}
	m_scene = _Scene;		//	シーンの更新
	m_scene->Load();		//	シーンの初期化
}
