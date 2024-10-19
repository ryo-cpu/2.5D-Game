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
	/// @brief MapDataに座標や頂点を設定
	void Load();
	/// @brief Mapをファイルから引っ張ってくる
	void DownLoad();
	void Update();
	/// @brief 表示範囲をplayerの座標を元に制限する
	/// @param Ppos player座標
	void Draw(const  VECTOR &Ppos);
	/// @brief 表示
	void Draw();
	/// @brief PushOnBoxを用いてMap全体との当たり判定を行う
	/// @param object 当たり判定がひつような対象
	void HitCalc(Object&object);
	/// @brief mapChip1つ当たりの当たり判定処理
	/// @param Colison 当たり判定
	/// @param x マップチップの番号X
	/// @param y マップチップの番号Y
	bool PushOnBox(HitBlock&Colison,int x,int y);
	


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

