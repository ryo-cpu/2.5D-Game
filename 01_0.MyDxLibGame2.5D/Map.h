// 2023 Takeru Yui All Rights Reserved.
#pragma once
#include <vector>

class WorldSprite;
const int MapChipNumX= 10;
const int MapChipNumY= 10;
/// <summary>
/// 2Dの背景マップ
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();

	// マップチップのサイズ
	static const float	ChipSize;
	static const int	ChipPixelSize;

private:
	// マップチップの画像表示をするためのクラス
	std::vector<WorldSprite*> S;
	WorldSprite* sprite[ MapChipNumY][ MapChipNumX];
	int MapData[ MapChipNumY][ MapChipNumX]{
		{1,65,1,1,1,1,1,1,1,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,15,15,15,15,15,15,15,15,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
};

