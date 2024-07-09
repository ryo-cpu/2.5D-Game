
#include "Enemy.h"
#include "WorldSprite.h"

const float Enemy::ChipSize = 0.725f;
const int Enemy::ChipPixelSize = 32;
void Enemy::Load()
{
	int chipGraph = LoadGraph("data/map.png");



	// マップチップを表示するためのクラスWorldSpriteに
	// 元画像のハンドル、１チップあたりのサイズ、表示するマップチップ番号を渡す
	


			sprite = new WorldSprite();
			sprite->Initialize(chipGraph, ChipPixelSize,65);

			// マップチップの位置と大きさを設定
			VECTOR chipHalfOffset = VGet(-Enemy::ChipSize * 0.5f, -	Enemy::ChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet(20*ChipSize,0,0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			pos = chipPos;
			sprite->SetTransform(chipPos, Enemy::ChipSize);

}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	
 sprite->Draw();
		
}
