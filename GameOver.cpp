//**********************************//
//*	名　前：GameOver.cpp
//*	内　容：オーバーシーン
//*	日　付：2017.04.25
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//**********************************//

#include "GameOver.h"
#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>

//	サウンド
#include "Resouces\Music\CueSheet_0.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

const int MAX_RANK = 3;

GameOver::GameOver()
{
	m_TimeCnt = 0;

	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 60.0f;
	m_grpH = 80.0f;

	if (FileIO(0, &m_score))
	{
		m_score = 0;
	}

	//	順位ファイルの読込み
	this->SetRanking();

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_result.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/result.png",
			resource.GetAddressOf(),
			m_time_tex.ReleaseAndGetAddressOf()));


	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = 0.0;
	m_origin.y = 0.0;

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	サウンド再生
	ADX2Le::Play(CRI_CUESHEET_0_RESULT);
}

GameOver::~GameOver()
{
	//	サウンドライブラリの終了処理
	ADX2Le::Finalize();
}

int GameOver::UpdateGame()
{
	//m_TimeCnt++;
	m_NextScene = OVER;
	m_scene = OVER;

	//	サウンドの更新
	ADX2Le::Update();

	//if (m_TimeCnt > 120)
	//{
	//	m_NextScene = TITLE;
	//}


	//エンターキーでタイトルシーン
	if (g_keyTracker->pressed.Enter)
	{
		m_NextScene = TITLE;
	}


	return m_NextScene;
}

void GameOver::RenderGame()
{
	//	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_texture.Get(), Vector2(0,0), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

	DrawNum(500, 400, m_score);
	
	//	順位
	for (int i = 0; i < MAX_RANK; i++)
	{
		DrawNum(200, 300 + (100 * i), m_rank[i]);
	}
}

//∞------------------------------------------------------------------∞
//∞*func：時間描画関数
//∞*arg：描画位置(float x、float y)、描画する数値(int n)
//∞*return：なし
//∞------------------------------------------------------------------∞
void GameOver::DrawNum(float x, float y, int n)
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	int w = n;		//作業用
	int i = 0;		//文字数

	RECT rect;

	if (w < 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };

		m_spriteBatch->Draw(m_time_tex.Get(), Vector2(x, y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			m_grpX = (w % 10) * m_grpW;
			rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
			m_spriteBatch->Draw(m_time_tex.Get(), Vector2((x - i * m_grpW), y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			w = w / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}


//∞------------------------------------------------------------------∞
//∞*func：ファイル読み書き関数
//∞*arg：読み書き指定（０：読み込み、１：書き込み）、読み書きしたい変数
//∞*return：正常（０）、エラー（１）
//∞------------------------------------------------------------------∞
int GameOver::FileIO(int io, int *score)
{
	char *Filename = "data.txt";
	FILE *fp;

	if (io == 0)
	{
		//読み込み
		fp = fopen(Filename, "r");
		if (fp == NULL)
		{
			return 1;
		}
		fscanf(fp, "%d", score);
	}
	else
	{
		//書き込み
		fp = fopen(Filename, "w");
		if (fp == NULL)
		{
			return 1;
		}
		fprintf(fp, "%d", score);
	}
	fclose(fp);
	return 0;
}

//=====================================================//
//内容		ランキングデータファイルの読込み・書込み
//引数		読込み(0)、書込み(1)
//戻り値	正常(0)、異常(1)
//=====================================================//
int GameOver::RankingDataFileIO(int io)
{
	char *Filename = "rank.txt";
	FILE *fp;
	char s[100];

	//読込みのとき
	if (io == 0)
	{
		fp = fopen(Filename, "r");
		//	読込みが失敗したとき
		if (fp == NULL){
			return 1;
		}

		fgets(s, 100, fp);
		//	一行ずつ読込み(2行目から)
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
		for (int i = 0; i < MAX_RANK; i++) {
			fprintf(fp, "%d", &m_rank[i]);
		}
	}
	fclose(fp);
	return 0;
}

//* 内容　データを降順に並べる
void GameOver::SetRanking()
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

