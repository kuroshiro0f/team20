#ifndef _TARGET_H_
#define _TARGET_H_

#include "DxLib.h"

class ObstructBase;
class TestSceneKoga;
class PlayEffect;
class UI;

enum Target_State
{
	NO_SHOT, NOW_SHOT, END_SHOT
};

class Target
{
public:
	Target();				// コンストラクタ.
	~Target();				// デストラクタ.

	void Update(float _deltaTime);			// 更新.
	void Draw();			// 描画.
	void Reaction(UI* _ui, bool _hitFlag);		// リアクション.



	// モデルハンドルの取得.
	int GetModelHandle() { return modelHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	void SetSinglePosX() { m_posX = pos.x; }
	const int GetPosX() { return m_posX; }

	// ディレクションのgetter/setter.
	const VECTOR& GetDir() const { return dir; }
	void SetDir(const VECTOR set) { dir = set; }

	// 加速(accelVec)のSetter
	void SetAccel(float _accel) { m_target_accel = _accel; }

	// あたり判定半径の取得.
	float GetHitRadius() { return hitRadius; }



	void SetTargetCount(int _targetCount) { m_targetCount = _targetCount; }
	void SetSetTime(int _setTime) { m_setTime = _setTime; }
	void SetInterval(int _interval) { m_shotInterval = _interval; }

	void SetThrowSound(int _sound) { m_throwIceSoundHandle = _sound; }
	void SetHitSound(int _sound) { m_hitIceSoundHandle = _sound; }
	void SetMissSound(int _sound) { m_missIceSoundHandle = _sound; }
	void SetIceType(int _iceType) { m_iceType = _iceType; }
	int GetIceType() { return m_iceType; }

	void SetHitIce(bool _hitFlag) { m_hitFlag = _hitFlag; }
	bool GetHitIce() { return m_hitFlag; }

	static void ScoreUpdateUI(UI& _ui, bool _hitFlag);

	Target_State GetIceState() { return m_iceState; }
	void SetIceState(Target_State _iceState) { m_iceState = _iceState; }

private:
	int		modelHandle;	// モデルハンドル.
	int		m_FontHandle;	// フォントハンドル
	VECTOR	pos;			// ポジション.
	int m_posX;

	VECTOR	velocity;		// 移動力.
	VECTOR	accelVec;

	VECTOR	dir;			// 回転方向.
	float	hitRadius;		// あたり判定の半径.
	int		timenow;		// 経過時間.
	bool	m_hitFlag;

	int		m_throwIceSoundHandle;
	int		m_hitIceSoundHandle;
	int		m_missIceSoundHandle;


	int		m_targetCount;
	int		m_plusX;
	int		m_setTime;
	int     m_shotInterval;     // エネミーを飛ばす間隔
	int		m_iceType;

	float m_target_accel;

	//	静的定数
	//static const float MAX_SPEED;
	//static const float DEFAULT_DECEL;
	//static const float BREAK_DECEL;
	//static const float GRIP_DECEL;
	//static const float GRIP_POWER;
	//static const float COLIDE_DECEL_FAC;*/
	static const int m_target_X;
	static const int m_target_Y;
	static const int m_target_Z;
	static const int m_font_X;
	static const int m_font_Y;
	static const int m_font_size;
	static const int m_font_thick;
	
	Target_State m_iceState;
};

#endif // _TARGET_H_