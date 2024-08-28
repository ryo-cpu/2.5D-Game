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
	bool isChengeBlock = false;
	///一点ずつ当たってるか調べる
	HITRESULT_LINE DownHitSensor;
	HITRESULT_LINE UpHitSensor;
	HITRESULT_LINE RightHitSensor;
	HITRESULT_LINE LeftHitSensor;

	for (int y = 0; y < MapChipNumY; y++)
	{

		for (int x = 0; x < MapChipNumX; x++)
		{
			if (MapData[y][x] != -1)
			{
				///sprite[x][y]の頂点を取得
				const VECTOR* Apex = sprite[y][x]->GetApex();
				



				//下線
				DownHitSensor= HitCheck_Line_Triangle(Collison.DownLeft, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
				if (DownHitSensor.HitFlag)
				{
					VECTOR Push_BackPower;
					Push_BackPower = Object::Push_Back_Vector(DownHitSensor.Position, Apex[0], Apex[1], Apex[2]);
					
					//辺の長さを内分
					float OLL = VSize( VSub(Collison.DownRight, Collison.DownLeft));
					float L_S = VSize( VSub(Collison.DownLeft, DownHitSensor.Position));
					float R_S = VSize(VSub(Collison.DownRight, DownHitSensor.Position));

					float Magnifivation_From_OLL_to_L = L_S / OLL;
					float Magnifivation_From_OLL_to_R = R_S / OLL;



					///Push_BackPowerを内分したものにかける
					Collison.DownRight = VAdd(Collison.DownRight,VScale(Push_BackPower,Magnifivation_From_OLL_to_L));
					Collison.UpRight = VAdd(Collison.UpRight,VScale( Push_BackPower,Magnifivation_From_OLL_to_L));
					Collison.DownLeft = VAdd(Collison.DownLeft,VScale(Push_BackPower,Magnifivation_From_OLL_to_R));
					Collison.UpLeft = VAdd(Collison.UpLeft,VScale( Push_BackPower,Magnifivation_From_OLL_to_R));
					
					isChengeBlock = true;
				
					
				}
				else
				{
					//上線
					UpHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.UpRight, Apex[0], Apex[1], Apex[2]);
					if (UpHitSensor.HitFlag)
					{
						VECTOR Push_BackPower;
						Push_BackPower = Object::Push_Back_Vector(UpHitSensor.Position, Apex[0], Apex[1], Apex[2]);





						///上辺はただ押し返す
						Collison.DownRight = VAdd(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VAdd(Collison.UpRight, Push_BackPower);
						Collison.DownLeft = VAdd(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpLeft, Push_BackPower);

					}
					///左辺

					LeftHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.DownLeft, Apex[0], Apex[1], Apex[2]);
					if (LeftHitSensor.HitFlag)
					{
						VECTOR Push_BackPower;
						Push_BackPower = Object::Push_Back_Vector(LeftHitSensor.Position, Apex[0], Apex[1], Apex[2]);





						///左辺はただ押し返す
						Collison.DownRight = VAdd(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VAdd(Collison.UpRight, Push_BackPower);
						Collison.DownLeft = VAdd(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpLeft, Push_BackPower);

					}

					///右辺

					RightHitSensor = HitCheck_Line_Triangle(Collison.UpRight, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
					if (RightHitSensor.HitFlag)
					{
						VECTOR Push_BackPower;
						Push_BackPower = Object::Push_Back_Vector(RightHitSensor.Position, Apex[0], Apex[1], Apex[2]);





						///右辺はただ押し返す
						Collison.DownRight = VAdd(Collison.DownRight, Push_BackPower);
						Collison.UpRight = VAdd(Collison.UpRight, Push_BackPower);
						Collison.DownLeft = VAdd(Collison.DownLeft, Push_BackPower);
						Collison.UpLeft = VAdd(Collison.UpLeft, Push_BackPower);

					}
				}
				
				

			}

		}


	}
	
	///下辺を表すベクトル LR
	VECTOR LR = VSub(Collison.DownRight,Collison.DownLeft);
	if (isChengeBlock)
	{
		///下の辺の高低差を求める
		
		
		/////LR と　Collison.DownRight　の内積／二つのSizeをかけたもの　でCosの値を求める
		float Cos_LR = VDot(LR, Collison.DownLeft) / (VSize(LR) * VSize(Collison.DownLeft));
		/////ACosで角度を求める
		float rag =acosf(Cos_LR);
		/////誤差をなくすため小数点代2以下を切り捨て
		////小数点第一を1の位に持ってくる
		rag = rag * 100;
		/////小数点以下を切り捨て
		rag = floorf(rag);
		/////元の桁に戻す
	   rag = rag / 100;
		/////出た値をslope(傾き）に代入する
		object.SetSlope(VGet(0, -1.f, rag));
		////傾きを元に戻す
	
	///傾ける値から回転力を追加する

		
		
		////右上
		Collison.UpRight = Object::RotFreeAxis(Collison.DownRight, Collison.DownRight,MMult(MGetTranslate(VGet(0, object.GetHeight(), 0)),MGetRotZ(rag/2)
			));

		////左上
		Collison.UpRight = Object::RotFreeAxis(Collison.DownLeft, Collison.DownLeft, MMult(MGetRotZ(rag / 2),
			MGetTranslate(VGet(0, object.GetHeight(), 0))));


		
	}
	

	
	///修正された物がめり込んでないか調べる
	/// ///めり込んでないか調べるためもう一周
	for (int y = 0; y < MapChipNumY; y++)
	{

		for (int x = 0; x < MapChipNumX; x++)
		{


			if (MapData[y][x] != -1)
			{
				///sprite[x][y]の頂点を取得
				const VECTOR* Apex = sprite[y][x]->GetApex();
				///線の判定
				DownHitSensor = HitCheck_Line_Triangle(Collison.DownLeft, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
				RightHitSensor = HitCheck_Line_Triangle(Collison.UpRight, Collison.DownRight, Apex[0], Apex[1], Apex[2]);
				UpHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.UpRight, Apex[0], Apex[1], Apex[2]);
				LeftHitSensor = HitCheck_Line_Triangle(Collison.UpLeft, Collison.DownLeft, Apex[0], Apex[1], Apex[2]);
				///めり込んでないか調べる
				if (DownHitSensor.HitFlag || UpHitSensor.HitFlag || RightHitSensor.HitFlag || LeftHitSensor.HitFlag)
				{
					///押し返しを元に戻して
					Collison = object.GetCollison();
					///動く前に戻す
					Collison.DownLeft = VSub(Collison.DownLeft, object.GetVelocity());
					Collison.UpLeft = VSub(Collison.UpLeft, object.GetVelocity());
					Collison.DownRight = VSub(Collison.DownRight, object.GetVelocity());
					Collison.UpRight = VSub(Collison.UpRight, object.GetVelocity());
					isChengeBlock = false;
					break;



				}


			}

		}


	}
	///オブジェクトの方に代入
	object.SetHitBlock(Collison);
	///posを修正
	object.FixPos();

}



