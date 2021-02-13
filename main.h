#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define NOMINMAX

#include <stdio.h>
#include <windows.h>
#include <assert.h>



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
#pragma warning(pop)



#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "xaudio2.lib")


#define SCREEN_WIDTH	(960)			// ウインドウの幅
#define SCREEN_HEIGHT	(540)			// ウインドウの高さ


HWND GetWindow();
int GetFPS();

//fpsのクラス
class Fps {
	int m_StartTime;         //測定開始時刻
	int m_Count;             //カウンタ
	float m_Fps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps() {
		m_StartTime = 0;
		m_Count = 0;
		m_Fps = 0;
	}

	bool Update() {
		if (m_Count == 0) { //1フレーム目なら時刻を記憶
			m_StartTime = timeGetTime();
		}
		if (m_Count == N) { //60フレーム目なら平均を計算する
			int t = timeGetTime();
			m_Fps = 1000.f / ((t - m_StartTime) / (float)N);
			m_Count = 0;
			m_StartTime = t;
		}
		m_Count++;
		return true;
	}

	void Wait() {
		int tookTime = timeGetTime() - m_StartTime;	//かかった時間
		int waitTime = m_Count * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}

	float Getfps()
	{
		return m_Fps;
	}
};