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

private:
	int		modelHandle;	// ���f���n���h��.
	VECTOR	pos;			// �|�W�V����.

	VECTOR	velocity;		// �ړ���.

	VECTOR	dir;			// ��]����.
	float	hitRadius;		// �����蔻��̔��a.
	int		timenow;		// �o�ߎ���.
	bool	score;			// �����������ǂ����̔���.
};

#endif // _TARGET_H_