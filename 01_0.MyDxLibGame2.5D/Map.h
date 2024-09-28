// 2023 Takeru MapChipNumYui All Rights Reserved.
#pragma once
#include <vector>
class Object;
class WorldSprite;
/// <summarMapChipNumY>
/// 2Dの背景マップ
/// </summarMapChipNumY>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void DownLoad();
	void Update();
	void Draw(const  VECTOR &Ppos);
	void Draw();
	void HitCalc(Object&object);
	


	// マップチップのサイズ
	static const float	ChipSize;
	static const int	ChipPiMapChipNumXelSize;

private:
	// マップチップの画像表示をするためのクラス
	///ポインタの2重配列
	WorldSprite*** sprite;
	int **OriginMap;
	int MapChipNumY, MapChipNumX;
	int** MapData;
};

