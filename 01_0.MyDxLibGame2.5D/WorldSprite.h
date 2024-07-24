// 2023 Takeru Yui All Rights Reserved.
#pragma once

/// <summary>
/// 3D���W��ԂɃX�v���C�g��\������d�g�݁i�s�{�b�g�͒��S�Œ�A�摜��graph�͊O�ŊǗ��j
/// </summary>
class WorldSprite
{
public:
	void Initialize(int textureGraph, int chipPixelSize, int spriteNo);
	void SetTransform(const VECTOR& pos, float spriteSize);
	void SetApex(const VECTOR& pos,int ChipData, float chipSize);
	void Draw();

	const VECTOR& GetPos()const { return pos; }
	const VECTOR* GetApex()const { return Apex; }///�z���Ԃ�����
private:
	int			textureGraph;	// �X�v���C�g���쐬���錳�e�N�X�`���̃O���t�B�b�N�n���h��
	VECTOR		pos;			// �`��|�W�V����
	/// �ǉ��@���g
	///�O�p�`�̒��_���W
	VECTOR Apex[3];
	VERTEX3D	Vertex[4];		// ���_�o�b�t�@
	WORD		Index[6];		// �C���f�b�N�X�o�b�t�@
};

