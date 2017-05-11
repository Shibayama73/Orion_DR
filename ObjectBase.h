//******************************************//
//*	名　前：ObjectBase.h
//*	内　容：オブジェクトのベースクラス
//*	日　付：2017.5.2
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

};

