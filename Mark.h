#ifndef _MARK_H_
#define _MARK_H_

#include"DxLib.h"

class Mark
{
public:
	Mark();					//	コンストラクタ
	~Mark();				//	デストラクタ

	void Mark_Update();		//	更新
	void Mark_Draw();		//	描画

	//	モデルハンドルの取得
	int GetModelHandle()
	{
		return m_modelHandle;
	}



private:
	int m_modelHandle;		//	モデルハンドル
	VECTOR m_pos;				//	ポジション
};

#endif // _MARK_H_