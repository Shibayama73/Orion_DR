//∞----------------------------------------------------∞
//∞*ファイル名：Time.cpp								∞
//∞*内容　　　：時間クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.25 							∞
//∞----------------------------------------------------∞

#include "pch.h"
#include "Time.h"

#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;

//制限時間
const int TIME_MAX = 72;


Time::Time()
{
	//数値の初期化
	m_current_time = 0;
	m_remnant_time = 0;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 0.0f;
	m_grpH = 0.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;
}
Time::~Time()
{	
}	

//∞------------------------------------------------------------------∞
//∞*func：描画関数
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Time::Render()
{

}

//∞------------------------------------------------------------------∞
//∞*func：現在の時間の取得
//∞*arg：なし
//∞*return：なし
//∞*heed：長針がpos(450,0)になったら呼び出す
//∞------------------------------------------------------------------∞
void Time::CurrentTime()
{
	m_current_time++;
}

//∞------------------------------------------------------------------∞
//∞*func：残りの時間計算関数
//∞*arg：なし
//∞*return：残り時間がある(true)か、ないか(false)
//∞*heed：falseを返したら、容赦なくゲームオーバ
//∞------------------------------------------------------------------∞
bool Time::RemnantTime()
{
	if (m_remnant_time < TIME_MAX)
	{
		m_remnant_time = TIME_MAX - m_current_time;
		return true;
	}
	return false;
}

//∞------------------------------------------------------------------∞
//∞*func：時間描画関数
//∞*arg：描画位置(float x、float y)、描画する数値(int n)
//∞*return：なし
//∞------------------------------------------------------------------∞
void DrawNum(float x, float y, int n)
{
	int w = n;		//作業用
	int i = 0;		//文字数

	if (w == 0)
	{
		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			//DrawRectGraph(x - i * 25, y, (w % 10) * 25, 48, 25, 32, g_PongImage, TRUE, FALSE);
			w = w / 10;
			i++;
		}
	}
}
