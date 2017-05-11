//**********************************//
//*	名　前：Clock.h
//*	内　容：時計クラス
//*	日　付：2017.5.2
//*	制作者：N.Shibayama
//**********************************//

#pragma once
#include "Game.h"
#include "SimpleMath.h"
#include "ObjectBase.h"

class Clock :public ObjectBase
{
protected:
	bool m_hand;									//時計の針(長針(true)、短針(false))
	DirectX::SimpleMath::Vector2 m_longTipPos;		//長針の先端座標
	DirectX::SimpleMath::Vector2 m_shotTipPos;		//短針の先端座標

public:
	Clock();
	~Clock();
	void Update();									//更新
	void Render();									//描画
	bool getHand();									//針の状態取得
	DirectX::SimpleMath::Vector2 getLongTipPos();	//針の先端座標取得
	DirectX::SimpleMath::Vector2 getShotTipPos();	//針の先端座標取得
	void clockwise();								//針を右回りに動かす


};