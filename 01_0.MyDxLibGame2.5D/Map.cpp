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
			if (MapData[y][x] == -1)
			{






			}

		}


	}
}



