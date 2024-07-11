// 2023 Takeru Yui All Rights Reserved.
#include "Player.h"
#include"Enemy.h"
#include "DxLib.h"





/// <summary>
/// コンストラクタ
/// </summary>
//Player::Player()
//{
//	// ３Ｄモデルの読み込み
//	modelHandle = MV1LoadModel("data/Robot.mv1");
//
//	pos = VGet(10, 0, 0);
//	velocity = VGet(0, 0, 0);
//	dir = VGet(0, 0, 1);
//	width=1;
//   height=1;
//   Depth=1;
//
//}

/// <summary>
/// デストラクタ
/// </summary>


/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 単純に方向転換
	dir = VGet(0, 0, 0);
	if (Key & PAD_INPUT_UP)
	{
		dir = VAdd(dir, VGet(0, 1, 0));
	}
	
	if (Key & PAD_INPUT_RIGHT)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}

	// ゼロ除算避け
	if (VSquareSize(dir) > 0)
	{
		// 正規化
		dir = VNorm(dir);
	}

	// ポジションを更新.
	velocity = VScale(dir, Speed);
	pos = VAdd(pos, velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}
	//printfDx("%f %f %f\n", dir.x, dir.y, dir.z);

	// 3Dモデルのスケール決定
	MV1SetScale(modelHandle, VGet(Scale, Scale, Scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);

	// 回転
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, -90.0f, 0.0f));
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
}



//bool Player::isCollision(Enemy* enemy)
//{
//
//	return false;
//}
//
