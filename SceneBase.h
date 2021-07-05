#pragma once

class SceneBase
{
public:
	SceneBase() {};						//	�R���X�g���N�^
	virtual ~SceneBase() {};			//	���z�f�X�g���N�^	(�v�����j

	//	�������z�֐��i�v�����j
	virtual SceneBase* Update() = 0;	//	�X�V
	virtual void Draw() = 0;			//	�`��
	virtual void Load() = 0;			//	������
};