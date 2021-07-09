#include "Target.h"
#include "ObstructBase.h"
#include "TestSceneKoga.h"

// 静的定数.
const int Target::m_target_X = 400;
//const int Target::m_target_X = 0;
const int Target::m_target_Y = 10;
const int Target::m_target_Z = 0;
const float Target::m_target_accel = 0.1f;
//const float Target::m_target_accel = 0;
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Target::Target()
	: modelHandle(-1)
	, hitRadius(5.0f)
	, timenow(0)
	, m_isShot(false)
	,m_endShot(false)
{
	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("data/model/target/icecream/SVH-icecream/icecream.pmx");

	// posはVector型なので、VGetで原点にセット
	pos = VGet(m_target_X, m_target_Y, m_target_Z);
	// 移動する力を（すべての座標）ゼロにする
	velocity = VGet(0, 0, 0);
	// 
	dir = VGet(-1, 0, 0);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
Target::~Target()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Target::Update()
{
	VECTOR accelVec = VGet(0, 0, 0);
	
	//	アイス射出フラグがtrueになったら
	if (m_isShot)
	{
		accelVec = VScale(dir, m_target_accel);
		if (pos.x < -500 || pos.x > 500)
		{
			accelVec = VGet(0, 0, 0);
			///////
			m_endShot = true;
		}
	}
	

	// ベロシティ加速計算.
	velocity = VAdd(velocity, accelVec);


	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);

	// ポジションを更新.
	pos = VAdd(pos, velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}
	//printfDx("%f %f %f\n", dir.x, dir.y, dir.z);

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);

	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}

//-----------------------------------------------------------------------------
// @brief  描画.
//-----------------------------------------------------------------------------
void Target::Draw()
{
	// 元モデルでは小さすぎるので描画倍率を設定
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);

	// デバッグあたり判定.
	//DrawSphere3D(pos, hitRadius, 5, 0x00ffff, 0x00ffff, false);
}

//-----------------------------------------------------------------------------
// @brief  衝突処理.
//-----------------------------------------------------------------------------
//void Target::OnHitObstruct(ObstructBase& obstruct)
//{
//	// 自分自身の位置を障害物のあたり判定分ずらす.
//	// Z軸とX軸の二次元座標として位置ずらしを行う.
//	VECTOR yZeroTarget = VGet(pos.x, 0, pos.z);
//	VECTOR yZeroObstruct = VGet(obstruct.GetPos().x, 0, obstruct.GetPos().z);
//
//	VECTOR obsToTarget = VSub(yZeroTarget, yZeroObstruct);
//
//	// ぶつかったときに離す距離。ちょうどだとfloat誤差で重なり続けるので少し間をあける.
//	float awayRange = (hitRadius + obstruct.GetHitRadius() + 0.01f);
//
//	VECTOR awayVec = VScale(VNorm(obsToTarget), awayRange);
//	pos = VAdd(yZeroObstruct, awayVec);
//
//	// ぶつかったら減速する.
//	velocity = VScale(velocity, COLIDE_DECEL_FAC);
//}