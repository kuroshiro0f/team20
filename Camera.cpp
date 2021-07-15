//-----------------------------------------------------------------------------
// @brief  カメラクラス.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "Player.h"
#include "Camera.h"

#define USE_LERP_CAMERA 1

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	// ３D空間に何かを描画する際に、カメラからどれだけ離れたところ（Near）から、
	// どこまで（Far）のものを描画するかを設定する(FOV)
	SetCameraNearFar(0.75f, 450.0f);

	// Vgetはベクトルの取得
	// 原点の値をセット
	pos = VGet(0, 0, 0);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Camera::~Camera()
{
	// 処理なし.
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Camera::Update(const Player& player)
{
#if !USE_LERP_CAMERA
	// z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
	//pos = VGet(0, player.GetPos().y + 20.0f, player.GetPos().z - 30.0f);

#else
	// lerpを使用して実装.
	// lerp(VECTOR a, VECTOR b, float t)は
	// answer = a + ((b-a) * t)
	// 
	VECTOR aimPos = VAdd(/*player.GetPos()*/VGet(0,0,0), VScale(/*player.GetDir()*/VGet(0,0,-1), 50.0f));
	// カメラの見る位置を少し上にする
	aimPos = VAdd(aimPos, VGet(0, 0, 0));
	VECTOR posToAim = VSub(aimPos, pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	pos = VAdd(pos, scaledPosToAim);
#endif
	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(VGet(-80,60,-80), /*player.GetPos()*/VGet(20,0,-20));
}