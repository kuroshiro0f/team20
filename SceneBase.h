#pragma once

class SceneBase
{
public:
	SceneBase();						//	コンストラクタ
	virtual ~SceneBase() {};			//	仮想デストラクタ	(要調査）

	//	純粋仮想関数（要調査）
	virtual SceneBase* Update(float _deltaTime) = 0;	//	更新
	virtual void Draw() = 0;			//	描画
	virtual void Sound() = 0;			//	音楽
	virtual void Load() = 0;			//	初期化
	int getVolume() { return m_volumePal; }
	void setVolume(int _volume) { m_volumePal = _volume; }

protected:
	int m_volumePal;
};