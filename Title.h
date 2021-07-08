#ifndef _TITLE_H_
#define _TITLE_H_

#include "SceneBase.h"

#include "DxLib.h"

class Title : public SceneBase
{
public:
	Title();					//	�R���X�g���N�^
	~Title();					//	�f�X�g���N�^

	SceneBase* Update()override;	//	�X�V
	void Draw()override;			//	�`��
	void Sound()override;			//	���y
	void Load()override;			//	������

private:
	int m_backGraphHandle;				//	�^�C�g����ʁE�w�i�̃O���t�B�b�N�n���h��
	int m_logoGraphHandle;				//	�^�C�g����ʁE���S�̃O���t�B�b�N�n���h��
	int m_guidanceGraphHandle;			//	�^�C�g����ʁE�K�C�h�̃O���t�B�b�N�n���h��
	int m_soundHandle;					//	�^�C�g����ʁE�T�E���h�n���h��
	bool m_checkKeyFlag;				//	�L�[�������ꂽ�܂܂��𔻒肷��t���O
};

#endif // _TITLE_H_

