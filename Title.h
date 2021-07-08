#ifndef _TITLE_H_
#define _TITLE_H_

#include "SceneBase.h"

#include "DxLib.h"

class Title : public SceneBase
{
public:
	Title();					//	コンストラクタ
	~Title();					//	デストラクタ

	SceneBase* Update()override;	//	更新
	void Draw()override;			//	描画
	void Sound()override;			//	音楽
	void Load()override;			//	初期化

private:
	int m_backGraphHandle;				//	タイトル画面・背景のグラフィックハンドル
	int m_logoGraphHandle;				//	タイトル画面・ロゴのグラフィックハンドル
	int m_guidanceGraphHandle;			//	タイトル画面・ガイドのグラフィックハンドル
	int m_soundHandle;					//	タイトル画面・サウンドハンドル
	bool m_checkKeyFlag;				//	キーが押されたままかを判定するフラグ
};

#endif // _TITLE_H_

