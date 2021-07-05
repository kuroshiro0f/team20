#pragma once

class SceneBase
{
public:
	SceneBase() {};						//	コンストラクタ
	virtual ~SceneBase() {};			//	仮想デストラクタ	(要調査）

	//	純粋仮想関数（要調査）
	virtual SceneBase* Update() = 0;	//	更新
	virtual void Draw() = 0;			//	描画
	virtual void Load() = 0;			//	初期化
};