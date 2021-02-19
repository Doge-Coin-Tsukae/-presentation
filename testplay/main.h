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


#define SCREEN_WIDTH	(960)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)			// �E�C���h�E�̍���


HWND GetWindow();
int GetFPS();

//fps�̃N���X
class Fps {
	int m_StartTime;         //����J�n����
	int m_Count;             //�J�E���^
	float m_Fps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps() {
		m_StartTime = 0;
		m_Count = 0;
		m_Fps = 0;
	}

	bool Update() {
		if (m_Count == 0) { //1�t���[���ڂȂ玞�����L��
			m_StartTime = timeGetTime();
		}
		if (m_Count == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = timeGetTime();
			m_Fps = 1000.f / ((t - m_StartTime) / (float)N);
			m_Count = 0;
			m_StartTime = t;
		}
		m_Count++;
		return true;
	}

	void Wait() {
		int tookTime = timeGetTime() - m_StartTime;	//������������
		int waitTime = m_Count * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}

	float Getfps()
	{
		return m_Fps;
	}
};