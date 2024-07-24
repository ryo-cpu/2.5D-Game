// 2023 Takeru Yui All Rights Reserved.
#include<vector>
#include"Object.h"
#include "Map.h"
#include "DxLib.h"
#include "WorldSprite.h"

const float Map::ChipSize = 0.725f;
const int Map::ChipPixelSize = 32;

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
	: sprite{ (nullptr) }
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	for (int i = 0; i <  MapChipNumY; i++)
	{
		if (sprite[i] != nullptr)
		{
			
				delete sprite;
			
			
		}
	}
	
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	// とりあえずマップロード
	int chipGraph = LoadGraph("data/map.png");
	
	

	// マップチップを表示するためのクラスWorldSpriteに
	// 元画像のハンドル、１チップあたりのサイズ、表示するマップチップ番号を渡す
	for (int i = 0; i <  MapChipNumY; i++)
	{
		for (int j = 0; j <  MapChipNumX; j++)
		{


			sprite[i][j] = new WorldSprite();
			sprite[i][j]->Initialize(chipGraph, ChipPixelSize, MapData[i][j]);
		
			// マップチップの位置と大きさを設定
			VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet((j+ 1)*ChipSize,( MapChipNumY - i)* ChipSize, 0), chipHalfOffset);	// 真ん中ピボットなのでマッチップ半分サイズずらす+地面なので一つ下に
			sprite[i][j]->SetTransform(chipPos, Map::ChipSize);
			///画像の頂点を設定
			sprite[i][j]->SetApex(chipPos, MapData[i][j],Map::ChipSize);
		}
	}
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 処理なし
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	for (int i = 0; i <  MapChipNumY; i++)
	{
		for (int j = 0; j <  MapChipNumX; j++)
		{
			sprite[i][j]->Draw();
			const VECTOR* Apex=sprite[i][j]->GetApex();
			DrawTriangle3D(Apex[0], Apex[1], Apex[2],GetColor(255,0,0),TRUE);
		}
		// ゆくゆくはカメラを持ってきて、カメラ範囲以外表示しないように
		
	}
}

void Map::HitCalc(Object& object)
{
	
	HitBlock Collison = object.GetCollison();

	for (int y = 0; y < MapChipNumY; y++)
	{

		for (int x = 0; x < MapChipNumX; x++)
		{
			if (MapData[y][x] != -1)
			{
				///sprite[x][y]の頂点を取得
				const VECTOR* Apex = sprite[y][x]->GetApex();
				///一点ずつ当たってるか調べる
				///左下
				if (Object::isCollisonTriangle(Collison.DownLeft, Apex[0], Apex[1], Apex[2]))
				{
					VECTOR Push_BackPower;
					Push_BackPower = Object::Push_Back_Vector(Collison.DownLeft, Apex[0], Apex[1], Apex[2]);
					///当たっている側だけを押し返す
					Collison.DownLeft = VAdd(Collison.DownLeft, Push_BackPower);
					Collison.UpLeft = VAdd(Collison.UpLeft, Push_BackPower);

				}
				///右下
				if (Object::isCollisonTriangle(Collison.DownRight, Apex[0], Apex[1], Apex[2]))
				{
					VECTOR Push_BackPower;
					Push_BackPower = Object::Push_Back_Vector(Collison.DownRight, Apex[0], Apex[1], Apex[2]);
					///当たっている側だけを押し返す
					Collison.DownRight = VAdd(Collison.DownRight, Push_BackPower);
					Collison.UpRight = VAdd(Collison.UpRight, Push_BackPower);

				}

				///左上
				if (Object::isCollisonTriangle(Collison.UpLeft, Apex[0], Apex[1], Apex[2]))
				{
					VECTOR Push_BackPower;
					Push_BackPower = Object::Push_Back_Vector(Collison.UpLeft, Apex[0], Apex[1], Apex[2]);
					///当たっている側だけを押し返す
					Collison.DownLeft = VAdd(Collison.UpLeft, Push_BackPower);
					Collison.UpLeft = VAdd(Collison.DownLeft, Push_BackPower);

				}
				///一点ずつ当たってるか調べる
				///右上
				if (Object::isCollisonTriangle(Collison.UpRight, Apex[0], Apex[1], Apex[2]))
				{
					VECTOR Push_BackPower;
					Push_BackPower = Object::Push_Back_Vector(Collison.UpRight, Apex[0], Apex[1], Apex[2]);
					///当たっている側だけを押し返す
					Collison.DownRight = VAdd(Collison.DownRight, Push_BackPower);
					Collison.UpRight = VAdd(Collison.UpRight, Push_BackPower);

				}
				
			

			}

		}


	}
	///めり込んでないか調べるためもう一周
	for (int y = 0; y < MapChipNumY; y++)
	{

		for (int x = 0; x < MapChipNumX; x++)
		{
			if (MapData[y][x] != -1)
			{
				///sprite[x][y]の頂点を取得
				const VECTOR* Apex = sprite[y][x]->GetApex();
				
				///めり込んでないか調べる
				if ((Object::isCollisonTriangle(Collison.UpRight, Apex[0], Apex[1], Apex[2])) &&
					(Object::isCollisonTriangle(Collison.UpRight, Apex[0], Apex[1], Apex[2])) &&
					(Object::isCollisonTriangle(Collison.DownRight, Apex[0], Apex[1], Apex[2])) &&
					(Object::isCollisonTriangle(Collison.DownLeft, Apex[0], Apex[1], Apex[2])))
				{
					///押し返しを元に戻して
					Collison = object.GetCollison();
					///動く前に戻す
					Collison.DownLeft = VSub(Collison.DownLeft, object.GetVelocity());
					Collison.UpLeft = VSub(Collison.UpLeft, object.GetVelocity());
					Collison.DownRight = VSub(Collison.DownRight, object.GetVelocity());
					Collison.UpRight = VSub(Collison.UpRight, object.GetVelocity());
					break;
				}


			}

		}


	}
	
	///下の辺の高低差を求める
	float Cos_LR = VDot(Collison.DownLeft,Collison.DownRight) / (VSize((Collison.DownLeft)) * VSize((Collison.DownRight)));
    object.SetSlope(VGet(0, -90.f,-acos(Cos_LR)));

	///オブジェクトの方に代入
	object.SetHitBlock(Collison);
	///posを修正
	object.FixPos();

}



