#pragma once
#include "DxLib.h"
class  WorldSprite;
class Enemy
{
private:
   int Img;
   WorldSprite* sprite;
   int		modelHandle;	// ���f���n���h��.
   VECTOR	pos;			// �|�W�V����.
   VECTOR	velocity;		// �ړ���.
   VECTOR	dir;			// ��]����.
public:
   void Load();
   void Update();
   void Draw();
   static const float	ChipSize;
   static const int	ChipPixelSize;
};

