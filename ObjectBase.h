//******************************************//
//*	名　前：ObjectBase.h
//*	内　容：オブジェクトのベースクラス
//*	日　付：2017.05.02
//* 更新日：2017.06.02
//*	制作者：N.Shibayama
//******************************************//

#pragma once

class ObjectBase
{
protected:
	float m_grpX;	//画像のX座標
	float m_grpY;	//画像のY座標
	float m_grpW;	//画像のW座標
	float m_grpH;	//画像のH座標
	float m_posX;	//X座標
	float m_posY;	//Y座標
	float m_spdX;	//速度X座標
	float m_spdY;	//速度Y座標
	int m_state;	//状態

public:
	ObjectBase();	//コンストラクタ
	~ObjectBase();	//デストラクタ
	virtual void Update();	//更新
	virtual void Render();	//描画

	//取得関数
	float GetGrpX();
	float GetGrpY();
	float GetGrpW();
	float GetGrpH();
	float GetPosX();
	float GetPosY();

	void SetSpdX(float spdX);
	void SetSpdY(float spdY);

};

