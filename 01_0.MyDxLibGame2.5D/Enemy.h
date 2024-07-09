#pragma once
#include "DxLib.h"
class  WorldSprite;
class Enemy
{
private:
   int Img;
   WorldSprite* sprite;
   int		modelHandle;	// モデルハンドル.
   VECTOR	pos;			// ポジション.
   VECTOR	velocity;		// 移動力.
   VECTOR	dir;			// 回転方向.
public:
   void Load();
   void Update();
   void Draw();
   static const float	ChipSize;
   static const int	ChipPixelSize;
};

