#ifndef _TARGET_H_
#define _TARGET_H_

#include "DxLib.h"

class ObstructBase;

class Target
{
public:
	Target();				// コンストラクタ.
	~Target();				// デストラクタ.

	void Update();			// 更新.
	void Draw();			// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() { return modelHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

	// ディレクションのgetter/setter.
	const VECTOR& GetDir() const { return dir; }
	void SetDir(const VECTOR set) { dir = set; }

	// あたり判定半径の取得.
	float GetHitRadius() { return hitRadius; }

private:
	int		modelHandle;	// モデルハンドル.
	VECTOR	pos;			// ポジション.

	VECTOR	velocity;		// 移動力.

	VECTOR	dir;			// 回転方向.
	float	hitRadius;		// あたり判定の半径.
	int		timenow;		// 経過時間.
	bool	score;			// 当たったかどうかの判定.
};

#endif // _TARGET_H_