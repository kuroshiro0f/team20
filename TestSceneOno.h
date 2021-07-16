//#pragma once
//#include "SceneBase.h"
//#include <vector>
//
//#include "DxLib.h"
//
//class TestSceneOno : public SceneBase
//{
//public:
//	TestSceneOno();				//	コンストラクタ
//	~TestSceneOno();			//	デストラクタ
//
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
//	std::vector<class Target*> m_targets;
//	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
//	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
//	class UI* m_score_ui[10];		//  UIクラスへのポインタメンバ変数
//	class UI* m_hit_ui[10];			//	ヒット判定UIクラスへのポインタメンバ変数
//	class PlayEffect* m_effect;         //  エフェクトプレーヤー
//	class PlayEffect* m_playerOrbitEfk;
//	int m_targetCount;				//	アイスの飛ばした個数
//	int m_hitCount;
//	int m_startTime;				//	ゲームの開始時間
//	int m_backGraphHandle;			//	背景のグラフィックハンドル
//	int m_finishGraphHandle;		//	ゲーム終了文字のグラフィックハンドル
//	int m_soundHandle;				//	ゲーム画面・サウンドハンドル
//	int m_finishSoundHandle;		//	ゲーム画面・終了の効果音用サウンドハンドル
//	bool m_checkKeyFlag;			//	キーが押されたままかを判定するフラグ
//	bool m_finishFlag;				//	ゲーム終了判定フラグ
//	bool m_iceThrowFlag;			//	アイス射出フラグ
//	bool m_hitFlag;
//};
