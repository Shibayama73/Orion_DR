//**********************************//
//*	名　前：RankFileIO.cpp
//*	内　容：順位ファイルクラス
//*	日　付：2017.06.12
//* 更新日：2017.06.12
//*	制作者：N.Shibayama
//**********************************//

#include "RankFileIO.h"

#include "GameOver.h"
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

const int MAX_RANK = 3;

//==================================//
//内容		コンストラクタ
//引数		なし
//戻り値	なし
//==================================//
RankFileIO::RankFileIO()
{
	//	初期化
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 60.0f;
	m_grpH = 80.0f;

	for (int i = 0; i < MAX_RANK; i++) {
		m_rank[i] = 0;
	}

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/result.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> number;
	DX::ThrowIfFailed(resource.As(&number));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC numDesc;
	number->GetDesc(&numDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = 0.0;
	m_origin.y = 0.0;

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

}

//==================================//
//内容		デストラクタ
//引数		なし
//戻り値	なし
//==================================//
RankFileIO::~RankFileIO()
{
}

//==================================//
//内容		描画
//引数		なし
//戻り値	なし
//==================================//
void RankFileIO::Render(float posX, float posY)
{
	//	順位
	for (int i = 0; i < MAX_RANK; i++)
	{
		DrawNum(posX, posY + (110 * i), m_rank[i]);
	}

}

//===============================================================================//
//内容		順位の描画
//引数		表示位置X座標(float x)、表示位置Y座標(float y)、表示する数値(int n)
//戻り値	なし
//===============================================================================//
void RankFileIO::DrawNum(float posX, float posY, int num)
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	int number = num;	//作業用
	int i = 0;			//文字数

	RECT rect;

	if (number < 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		m_spriteBatch->Draw(m_texture.Get(), Vector2(posX, posY), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
	}
	else
	{
		while (number)
		{
			m_grpX = (number % 10) * m_grpW;
			rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
			m_spriteBatch->Draw(m_texture.Get(), Vector2((posX - i * m_grpW), posY), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			number = number / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}

//=====================================================//
//内容		ランキングデータファイルの読込み・書込み
//引数		読込み(0)、書込み(1)
//戻り値	正常(0)、異常(1)
//=====================================================//
int RankFileIO::RankingDataFileIO(int io)
{
	char *Filename = "rank.txt";
	FILE *fp;

	//読込みのとき
	if (io == 0)
	{
		fp = fopen(Filename, "r");
		//	読込みが失敗したとき
		if (fp == NULL) {
			return 1;
		}

		//fgets(s, 100, fp);
		//	一行ずつ読込み
		for (int i = 0; i < MAX_RANK; i++) {
			fscanf(fp, "%d", &m_rank[i]);
		}
	}
	//書込みのとき
	else
	{
		fp = fopen(Filename, "w");
		//	書込みが失敗したとき
		if (fp == NULL) {
			return 1;
		}
		//	1行ずつ書込み
		for (int i = 0; i < MAX_RANK; i++) {
			fprintf(fp, "%d\n", m_rank[i]);
		}
	}
	fclose(fp);
	return 0;
}

//========================================//
//内容		データを降順に並べる
//引数		なし
//戻り値	なし
//========================================//
void RankFileIO::SetRanking()
{
	//	順位ファイルの読込み
	this->RankingDataFileIO(0);

	//	格納
	int tmp;
	//	総数
	int total = 3;

	//	降順にソートする
	for (int i = 0; i < total; i++) {
		for (int j = i + 1; j < total; j++) {
			if (m_rank[i] < m_rank[j]) {
				tmp = m_rank[i];
				m_rank[i] = m_rank[j];
				m_rank[j] = tmp;
			}
		}
	}

}

//========================================================//
//内容		ファイルデータ値とスコアの値の大小を比べる
//引数		なし
//戻り値	なし
//========================================================//
void RankFileIO::ArraySort(int score)
{
	//	格納
	int tmp;
	//	総数
	int total = 4;

	int data[4] = { m_rank[0],m_rank[1],m_rank[2],score };

	//	降順にソートする
	for (int i = 0; i < total; i++) {
		for (int j = i + 1; j < total; j++) {
			if (data[i] < data[j]) {
				tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}

	//	降順のデータをランキングデータに入れる
	for (int k = 0; k < 3; k++)
	{
		m_rank[k] = data[k];
	}

}

