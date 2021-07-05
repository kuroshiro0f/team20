#ifndef _GAME_H_
#define _GAME_H_

#include "SceneBase.h"

#include "DxLib.h"

class Game : public SceneBase
{
public:
	Game();				//	コンストラクタ
	~Game();			//	デストラクタ

	SceneBase* Update()override;	//	更新
	void Draw()override;			//	描画
	void Load()override;			//	初期化

private:
	class Player* m_player;			//	プレイヤークラスへのポインタメンバ変数
	class Target* m_target[10];			//
	class Camera* m_camera;			//	カメラクラスへのポインタメンバ変数
	class Mark* m_mark;				//	マーククラスへのポインタメンバ変数
	class ObstructManager* m_obstructManager;	//
	int TargetCount = 0;
	int StartTime = 0;
};

#endif // _GAME_H_
