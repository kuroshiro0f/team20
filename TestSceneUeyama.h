//#pragma once
//
//#include "SceneBase.h"
//
//class TestSceneUeyama : public SceneBase
//{
//public:
//	TestSceneUeyama();
//	~TestSceneUeyama();
//
//	SceneBase* Update()override;	//	更新
//	void Draw()override;			//	描画
//	void Sound()override;			//	音楽
//	void Load()override;			//	初期化
//
//private:
//	class Player* m_player;			//	プレイヤークラスへのポインタメンバ変数
//	class Target* m_target[10];		//
//	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
//	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
//	class ObstructManager* m_obstructManager;	//
//	int TargetCount = 0;
//	int StartTime = 0;
//	int m_backGraphHandle;			//	背景のグラフィックハンドル
//	int m_finishGraphHandle;		//	ゲーム終了文字のグラフィックハンドル
//	int m_soundHandle;				//	ゲーム画面・サウンドハンドル
//	int m_finishSoundHandle;		//	ゲーム画面・終了の効果音用サウンドハンドル
//	bool m_checkKeyFlag;			//	キーが押されたままかを判定するフラグ
//	bool m_finishFlag;				//	ゲーム終了判定フラグ
//};