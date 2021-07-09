//-----------------------------------------------------------------------------
// @brief  ヒットチェック.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------

#include "HitChecker.h"
#include "Player.h"
#include "ObstructManager.h"
#include "Target.h"
#include "TestSceneKoga.h"

//-----------------------------------------------------------------------------
// @brief  ヒットチェック処理.
//-----------------------------------------------------------------------------
bool HitChecker::Check(Player& player, Target& _Target)
{
	// Z軸とX軸の二次元座標としてあたり判定を行う.
	VECTOR yZeroPlayer = VGet(player.GetPos().x, 0, player.GetPos().z);
	bool isHit = true;

	// 一度でもぶつかったら位置が変わるのでヒット計算をしなおす.
	while (isHit)
	{
		isHit = false;

		VECTOR yZeroObstruct = VGet(_Target.GetPos().x, 0, _Target.GetPos().z);
		// お互いのポジションと半径の距離が重なったら当たっていることになる.
	
		VECTOR playerToObs = VSub(yZeroObstruct, yZeroPlayer);
		//printfDx("playerToObs:%f %f %f\n", playerToObs.x, playerToObs.y, playerToObs.z);
		if (VSize(playerToObs) < player.GetHitRadius() + _Target.GetHitRadius())
		{
			//printfDx("Hit!");
			isHit = true;
			return true;
		}
		return false;
		
	}
}