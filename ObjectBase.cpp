//******************************************//
//*	名　前：ObjectBase.cpp
//*	内　容：オブジェクトのベースクラス
//*	日　付：2017.05.02
//* 更新日：2017.06.02
//*	制作者：N.Shibayama
//******************************************//

#include "ObjectBase.h"

//==================================//
//内容		コンストラクタ
//引数		なし
//戻り値	なし
//==================================//
ObjectBase::ObjectBase()
{
}

//==================================//
//内容		デストラクタ
//引数		なし
//戻り値	なし
//==================================//
ObjectBase::~ObjectBase()
{
}

//==================================//
//内容		更新
//引数		なし
//戻り値	なし
//==================================//
void ObjectBase::Update()
{
	m_posX += m_spdX;
	m_posY += m_spdY;
}

//==================================//
//内容		描画
//引数		なし
//戻り値	なし
//==================================//
void ObjectBase::Render()
{
}

//∞------------------------------------------------------------------∞
//∞*func：描画位置の取得関数（m_grpX）
//∞*arg：なし
//∞*return：m_grpX
//∞------------------------------------------------------------------∞
float ObjectBase::GetGrpX()
{
	return m_grpX;
}

//∞------------------------------------------------------------------∞
//∞*func：描画位置の取得関数（m_grpY）
//∞*arg：なし
//∞*return：m_grpY
//∞------------------------------------------------------------------∞
float ObjectBase::GetGrpY()
{
	return m_grpY;
}

//∞------------------------------------------------------------------∞
//∞*func：描画位置の取得関数（m_grpW）
//∞*arg：なし
//∞*return：m_grpW
//∞------------------------------------------------------------------∞
float ObjectBase::GetGrpW()
{
	return m_grpW;
}

//∞------------------------------------------------------------------∞
//∞*func：描画位置の取得関数（m_grpH）
//∞*arg：なし
//∞*return：m_grpH
//∞------------------------------------------------------------------∞
float ObjectBase::GetGrpH()
{
	return m_grpH;
}

//∞------------------------------------------------------------------∞
//∞*func：位置の取得関数（m_posX）
//∞*arg：なし
//∞*return：m_posX
//∞------------------------------------------------------------------∞
float ObjectBase::GetPosX()
{
	return m_posX;
}

//∞------------------------------------------------------------------∞
//∞*func：位置の取得関数（m_posY）
//∞*arg：なし
//∞*return：m_posY
//∞------------------------------------------------------------------∞
float ObjectBase::GetPosY()
{
	return m_posY;
}

//∞------------------------------------------------------------------∞
//∞*func：速度の設定（m_spdX）
//∞*arg：spdX
//∞*return：なし
//∞------------------------------------------------------------------∞
void ObjectBase::SetSpdX(float spdX)
{
	m_spdX = spdX;
}

//∞------------------------------------------------------------------∞
//∞*func：速度の設定（m_spdY）
//∞*arg：spdY
//∞*return：なし
//∞------------------------------------------------------------------∞
void ObjectBase::SetSpdY(float spdY)
{
	m_spdY = spdY;
}

