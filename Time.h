//∞----------------------------------------------------∞
//∞*ファイル名：Time.cpp								∞
//∞*内容　　　：時間クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.25 							∞
//∞----------------------------------------------------∞
#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"
class Time : public ObjectBase
{
public:
	Time();
	~Time();
	void Render();
	//*今の時間をカウントする
	void CurrentTime();
	//残りの時間の計算、falseになったらゲームオーバー
	bool RemnantTime();

private:
	int	m_current_time;		//*現在の時間
	int m_remnant_time;		//*残りの時間
};

