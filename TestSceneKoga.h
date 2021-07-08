//#pragma once
//
//#include"SceneBase.h"
//
//class TestSceneKoga : public SceneBase
//{
//public:
//	TestSceneKoga();		// コンストラクタ
//	~TestSceneKoga();		// デストラクタ
//	
//	SceneBase* Update()override;	//	更新
//	void Draw()override;			//	描画
//	void Sound()override;
//	void Load()override;			//	初期化
//
//	int GetTargetCount() { return m_targetCount; }
//
//private:
//	class Player* m_player;			//	プレイヤークラスへのポインタメンバ変数
//	class Target* m_target[10];		//	ターゲットクラスへのポインタメンバ変数
//	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
//	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
//	class ObstructManager* m_obstructManager;	//
//	int m_targetCount;				//	アイスの飛ばした個数
//	int m_startTime;				//	ゲームの開始時間
//	bool m_iceThrowFlag;			//	アイス射出フラグ
//};