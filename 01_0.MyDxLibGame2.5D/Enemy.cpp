
#include "Enemy.h"
#include "WorldSprite.h"

const float Enemy::ChipSize = 0.725f;
const int Enemy::ChipPixelSize = 32;
void Enemy::Load()
{
	int chipGraph = LoadGraph("data/map.png");



	// �}�b�v�`�b�v��\�����邽�߂̃N���XWorldSprite��
	// ���摜�̃n���h���A�P�`�b�v������̃T�C�Y�A�\������}�b�v�`�b�v�ԍ���n��
	


			sprite = new WorldSprite();
			sprite->Initialize(chipGraph, ChipPixelSize,65);

			// �}�b�v�`�b�v�̈ʒu�Ƒ傫����ݒ�
			VECTOR chipHalfOffset = VGet(-Enemy::ChipSize * 0.5f, -	Enemy::ChipSize * 0.5f, 0);					// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(20*ChipSize,0,0), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
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
