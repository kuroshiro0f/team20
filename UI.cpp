#include "UI.h"

// スゴクカタイアイスの画像サイズ
const int score_pixel = 320;
// 画像の縮小する大きさ
const double score_shrink = 0.4f;
// RotaGraphを使うので真ん中からのスゴクカタイアイスの画像サイズ
const int score_graph_size = score_pixel*score_shrink;

// ハンドルを入れる変数の実体を作る
int UI::m_help_graphHandle;
int UI::m_score_graphHandle;
int UI::m_hit_graphHandle;
int UI::m_miss_graphHandle;

// ScoreUIコンストラクタ
UI::UI(const int& _x, const int& _y, const int& _graph_handle)
{
	// x,y座標に画像の位置座標を格納する
	m_posX = (_x * score_graph_size) + 100;
	m_posY = (_y * score_graph_size) + 100;
	// 使う画像を格納する
	m_handle = _graph_handle;
}

// ScoreUIデストラクタ
UI::~UI()
{

}

void UI::Load()
{
	// 操作説明画像の読み込み
	m_help_graphHandle = LoadGraph("data/model/score_ui/");
	// スコア画像の読み込み
	m_score_graphHandle = LoadGraph("data/model/score_ui/hit.png");
	// HIT画像の読み込み
	m_hit_graphHandle = LoadGraph("data/model/score_ui/hit.png");
	// MISS画像の読み込み
	m_miss_graphHandle = LoadGraph("data/model/score_ui/miss.png");
}

// 更新
// 引数にエネミーからscoreとtargetCountを持ってくる
void UI::ScoreUpdate(UI* _scoreUi, bool _hitOrMiss)
{
	// 当たり判定を読んで×か〇かの判定？
	// 当たっていれば
	if (_hitOrMiss)
	{
		// 何個目かをエネミーから呼ぶ？
		m_handle = m_hit_graphHandle;
	}
	// 当たっていなければ
	else
	{
		// 何個目かをエネミーから呼ぶ？	
		m_handle = m_miss_graphHandle;
	}

}

// 描画(仮引数の値で呼び出す画像を変える)
void UI::Draw()
{
	//DrawGraph(m_posX, m_posY, m_handle, TRUE);
	DrawRotaGraph(m_posX, m_posY, score_shrink, 0, m_handle, TRUE, FALSE);
}
