// 2023 Takeru Yui All Rights Reserved.
#include "Player.h"
#include "DxLib.h"




// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::Speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Player::Scale = 0.002f;		// スケール
const VECTOR G=VGet(0,-0.5f,0);
/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("data/Robot.mv1");

	pos = VGet(10, 3, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
	slope = VGet(0.0f, -90.0f, 0.0f);
	width=0.5;
   height=0.5;
   Depth=0;
   Initialization_HitBlock();
}

Player::~Player()
{
	//処理なし
}
//
// 


void Player::Update()
{
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	HitBlock Collison = this->GetCollison();
	// 単純に方向転換
	dir = VGet(0, 0, 0);
	if (Key & PAD_INPUT_UP)
	{
		dir = VAdd(dir,Object::VectorNorm(VSub(Collison.UpRight,Collison.DownRight)));
	}
	else if (Key & PAD_INPUT_DOWN)
	{
		dir = VAdd(dir, Object::VectorNorm(VSub(Collison.DownRight, Collison.UpRight)));
	}
	
	if (Key & PAD_INPUT_RIGHT)
	{
		
		dir = VAdd(dir, Object::VectorNorm(VSub(Collison.UpRight, Collison.UpLeft)));
	}
	
	else if (Key & PAD_INPUT_LEFT)
	{
		dir = VAdd(dir, Object::VectorNorm(VSub(Collison.UpLeft, Collison.UpRight)));
	}
	
	///重力追加
	//dir = VAdd(dir, G);
	// ゼロ除算避け
	if (VSquareSize(dir) > 0)
	{
		// 正規化
		dir = VNorm(dir);
	}

	// ポジションを更新.
	velocity = VScale(dir, Speed);

	pos = VAdd(pos, velocity);
	MoveHitBlock();
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}

	// 3Dモデルのスケール決定
	MV1SetScale(modelHandle, VGet(Scale, Scale, Scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);

	// 回転
	MV1SetRotationXYZ(modelHandle,slope);
	
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	/*MV1DrawModel(modelHandle);*/
	DrawTriangle3D(Collison.UpRight, Collison.DownRight, Collison.DownLeft, GetColor(255, 0, 0), FALSE);
	DrawTriangle3D(Collison.UpLeft, Collison.UpRight, Collison.DownLeft, GetColor(255, 0, 0), FALSE);
	/*DrawFormatString(0, 0, GetColor(255, 12, 3), "方向%f %f %f", dir.x, dir.y, dir.z);
	DrawFormatString(0, 100, GetColor(255, 12, 3), "左下%f %f %f", Collison.DownLeft.x, Collison.DownLeft.y, Collison.DownLeft.z);
	DrawFormatString(0, 200, GetColor(255, 12, 3), "左上%f %f %f", Collison.UpLeft.x, Collison.UpLeft.y, Collison.UpLeft.z);
	DrawFormatString(0, 300, GetColor(255, 12, 3), "右下%f %f %f", Collison.DownRight.x, Collison.DownRight.y, Collison.DownRight.z);
	DrawFormatString(0, 400, GetColor(255, 12, 3), "右上%f %f %f", Collison.UpRight.x, Collison.UpRight.y, Collison.UpRight.z);*/

}



//bool Player::isCollision(Enemy* enemy)
//{
//
//	return false;
//}
//
