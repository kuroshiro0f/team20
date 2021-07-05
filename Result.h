#ifndef _RESULT_H_
#define _RESULT_H_

#include "SceneBase.h"

#include "DxLib.h"

class Result : public SceneBase
{
public:
	Result();			//	�R���X�g���N�^
	~Result();			//�@�f�X�g���N�^

	SceneBase* Update()override;	//	�X�V
	void Draw()override;			//	�`��
	void Load()override;			//	������

private:
	int m_logoGraphHandle;				//	���U���g��ʁE���S�̃O���t�B�b�N�n���h��
	int m_guidanceGraphHandle;			//	���U���g��ʁE�K�C�h�̃O���t�B�b�N�n���h��
	bool m_checkKeyFlag;				//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
};

#endif // _RESULT_H_

