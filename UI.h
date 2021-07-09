#pragma once
#include "DxLib.h"

// スコアのUIクラス
class UI final
{
public:
	// コンストラクタ
	UI(const int& _x, const int& _y, const int& _graph_handle);
	// デストラクタ
	~UI();
	// ロード
	void UI::Load();
	// 更新
	// 引数にエネミーからscoreとターゲットカウントを持ってくる
	void UI::ScoreUpdate(bool _hitOrMiss);
	// 描画
	void UI::Draw();
	// getter
	int GetScore() { return m_score; }

private:
	// 操作説明画像ハンドル
	static int m_help_graphHandle;
	// スコア画像ハンドル
	static int  m_score_graphHandle;
	// 当たった時の画像ハンドル
	static int m_hit_graphHandle;
	// 外れた時の画像ハンドル
	static int m_miss_graphHandle;

	// スコア保存用変数
	static int m_score;

	// スコアの座標
	int m_posX;
	int m_posY;
	// ハンドル格納変数
	int m_handle;
};