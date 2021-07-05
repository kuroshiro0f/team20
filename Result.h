#ifndef _RESULT_H_
#define _RESULT_H_

#include "SceneBase.h"

#include "DxLib.h"

class Result : public SceneBase
{
public:
	Result();			//	コンストラクタ
	~Result();			//　デストラクタ

	SceneBase* Update()override;	//	更新
	void Draw()override;			//	描画
	void Load()override;			//	初期化

private:
	int m_logoGraphHandle;				//	リザルト画面・ロゴのグラフィックハンドル
	int m_guidanceGraphHandle;			//	リザルト画面・ガイドのグラフィックハンドル
	bool m_checkKeyFlag;				//	キーが押されたままかを判定するフラグ
};

#endif // _RESULT_H_

