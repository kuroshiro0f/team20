#ifndef _TARGET_H_
#define _TARGET_H_

#include "DxLib.h"

class ObstructBase;

class Target
{
public:
	Target();				// �R���X�g���N�^.
	~Target();				// �f�X�g���N�^.

	void Update();			// �X�V.
	void Draw();			// �`��.

	// ���f���n���h���̎擾.
	int GetModelHandle() { return modelHandle; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

	// �f�B���N�V������getter/setter.
	const VECTOR& GetDir() const { return dir; }
	void SetDir(const VECTOR set) { dir = set; }

	// �����蔻�蔼�a�̎擾.
	float GetHitRadius() { return hitRadius; }

	void SetIsShot(bool _shotFlag) { m_isShot = _shotFlag; }

	bool GetEndShot() { return m_endShot; }

private:
	int		modelHandle;	// ���f���n���h��.
	VECTOR	pos;			// �|�W�V����.

	VECTOR	velocity;		// �ړ���.

	VECTOR	dir;			// ��]����.
	float	hitRadius;		// �����蔻��̔��a.
	int		timenow;		// �o�ߎ���.
	bool	m_isShot;
	bool	m_endShot;

	//	�ÓI�萔
	static const float m_target_accel;
	//static const float MAX_SPEED;
	//static const float DEFAULT_DECEL;
	//static const float BREAK_DECEL;
	//static const float GRIP_DECEL;
	//static const float GRIP_POWER;
	//static const float COLIDE_DECEL_FAC;*/
	static const int m_target_X;
	static const int m_target_Y;
	static const int m_target_Z;
};

#endif // _TARGET_H_