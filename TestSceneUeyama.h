#pragma once

#include "SceneBase.h"

class TestSceneUeyama : public SceneBase
{
public:
	TestSceneUeyama();
	~TestSceneUeyama();

	SceneBase* Update()override;	//	更新
	void Draw()override;			//	描画
	void Load()override;			//	初期化

private:
	class Player* m_player;			//	プレイヤークラスへのポインタメンバ変数
	class Target* m_target[10];		//
	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
	class ObstructManager* m_obstructManager;	//
	int TargetCount = 0;
	int StartTime = 0;
	int m_backGraphHandle;			//	背景のグラフィックハンドル
	bool m_checkKeyFlag;			//	キーが押されたままかを判定するフラグ
};