//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "Title.h"
#include "TestSceneUeyama.h"

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);		//	裏画面の設定

	//	シーンマネージャークラスのインスタンスを生成
	SceneMgr* Scene = new SceneMgr;

	//	タイトルシーンをセット
	Scene->SetScene(new Title);

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// シーン制御
		Scene->Update();

		// 描画処理
		Scene->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		//	画面消去
		ClearDrawScreen();
	}

	// シーンを削除
	delete(Scene);

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}