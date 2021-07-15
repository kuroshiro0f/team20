//#pragma once
//#include "SceneBase.h"
//
//class TestScene_fujihara :public SceneBase
//{
//public:
//	TestScene_fujihara();			//  コンストラクタ
//	~TestScene_fujihara();			//  デストラクタ
//	SceneBase* Update()override;	//	更新
//	void Draw()override;			//	描画
//	void Sound()override;			//	音楽
//	void Load()override;			//	初期化
//	void DebugKey();
//
//	int GetTargetCount() { return m_targetCount; }
//
//private:
//	class Player* m_player;			//	プレイヤークラスへのポインタメンバ変数
//	class Target* m_target[11];			//
//	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
//	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
//	class UI* m_score_ui[10];		//  UIクラスへのポインタメンバ変数
//	class UI* m_hit_ui[10];			//	ヒット判定UIクラスへのポインタメンバ変数
//	int m_targetCount;				//	アイスの飛ばした個数
//	int m_startTime;				//	ゲームの開始時間
//	int m_backGraphHandle;			//	背景のグラフィックハンドル
//	int m_finishGraphHandle;		//	ゲーム終了文字のグラフィックハンドル
//	int m_soundHandle;				//	ゲーム画面・サウンドハンドル
//	int m_finishSoundHandle;		//	ゲーム画面・終了の効果音用サウンドハンドル
//	bool m_checkKeyFlag;			//	キーが押されたままかを判定するフラグ
//	bool m_finishFlag;				//	ゲーム終了判定フラグ
//	bool m_iceThrowFlag;			//	アイス射出フラグ
//
//	//// 確認用変数
//	int m_hitCount;
//	bool m_hitFlag;
//};
