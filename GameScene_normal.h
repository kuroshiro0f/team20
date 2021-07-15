#pragma once

#pragma once

#include "SceneBase.h"
#include "DxLib.h"

class GameSceneNormal :public SceneBase
{
public:

	enum class GAME_SCENE_STATE
	{
		COUNTDOWN,
		GAME
	};

	GameSceneNormal();				//	コンストラクタ
	~GameSceneNormal();			//	デストラクタ

	SceneBase* Update(float _deltaTime)override;	//	更新
	void Draw()override;			//	描画
	void Sound()override;			//	音楽
	void Load()override;			//	初期化
	void DebugKey();

	int GetTargetCount() { return m_targetCount; }

private:
	class Player* m_player;			//	プレイヤークラスへのポインタメンバ変数
	class Target* m_target[11];			//
	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
	class UI* m_score_ui[10];		//  UIクラスへのポインタメンバ変数
	class UI* m_hit_ui[10];			//	ヒット判定UIクラスへのポインタメンバ変数
	class PlayEffect* m_effect;     //  エフェクトプレーヤー
	GAME_SCENE_STATE m_state;
	int m_targetCount;				//	アイスの飛ばした個数
	int m_startTime;				//	ゲームの開始時間
	int m_girl_Y;					//	
	int m_lady_Y;
	int m_backGraphHandle;			//	背景のグラフィックハンドル
	int m_finishGraphHandle;		//	ゲーム終了文字のグラフィックハンドル
	int m_soundHandle;				//	ゲーム画面・サウンドハンドル
	int m_finishSoundHandle;		//	ゲーム画面・終了の効果音用サウンドハンドル
	int m_iceSoundHandle;			//	アイスの発射音用サウンドハンドル
	int m_hitSoundHandle;			//	アイスと皿の衝突音用サウンドハンドル
	int m_missSoundHandle;			//	アイスと皿が衝突失敗した時の交換用サウンドハンドル
	int m_doorSoundHandle;			//	入店音のサウンドハンドル
	int m_manualGraphHandle;		//	操作説明のグラフィックハンドル
	int m_girlGraphHandle;
	int m_ladyGraphHandle;
	int m_girl_missReaction_GraphHandle;	//  ミスした時の女の子に追加する画像ハンドル
	int m_girl_hitReaction_GraphHandle;		//  成功した時の女の子に追加する画像ハンドル
	//float m_deltaTime;				//	デルタタイム
	bool m_checkKeyFlag;			//	キーが押されたままかを判定するフラグ
	bool m_finishFlag;				//	ゲーム終了判定フラグ
	bool m_iceThrowFlag;			//	アイス射出フラグ
	bool m_iceHitFlagBuffer;
	bool m_girlUpFlag;
	bool m_fadeInFinishFlag;		//	フェードインの終了判定フラグ
	bool m_fadeOutFlag;				//	フェードアウト開始用のフラグ
	bool m_fadeOutFinishFlag;		//	フェードアウトの終了判定フラグ

	bool m_girl_hitReactionFlag;	//  女の子のhitした時のリアクションをするかどうか
	bool m_girl_missReactionFlag;	//  女の子のmissした時のアクションをするかどうか
	bool m_girl_ReactionFlag;		//  女の子にリアクションさせるかどうか

	//// 確認用変数
	int m_hitCount;
	bool m_hitFlag;
};