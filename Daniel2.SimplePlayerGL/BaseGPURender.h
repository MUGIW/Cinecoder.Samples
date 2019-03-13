#pragma once

// OpenGL Graphics includes
#include <GL/freeglut.h>

// DirectX includes
#include <d3d11.h>

#include "Timer.h"
#include "DecodeDaniel2.h"
#include "AudioSource.h"

class BaseGPURender
{
protected:
	bool m_bPause;
	bool m_bVSync;
	bool m_bRotate;
	bool m_bLastRotate = m_bRotate;

	bool m_bFullScreen;
	bool m_bFullCurScreen;

	std::shared_ptr<DecodeDaniel2>	m_decodeD2;		// Wrapper class which demonstration decoding Daniel2 format
	std::shared_ptr<AudioSource>	m_decodeAudio;	// Audio decoder

	C_Event m_evExit;

	std::wstring m_windowCaption;

	C_CritSec m_mutex; // global mutex

	bool m_bShowSlider;
	float edgeLineX;
	float edgeLineY;
	float sizeSquare;
	float sizeSquare2;

	bool m_bCopyToTexture;
	bool m_bDecoder;

	bool m_bMaxFPS;
	bool m_bVSyncHand;

protected:
	// Window
	WNDCLASSEX	m_wndClass;
	HINSTANCE	m_Instance;
	HWND		m_hWnd;
	HDC			m_hDC;

	RECT		m_posWindow;

	int window_width;
	int window_height;

	// Texture
	cudaGraphicsResource* cuda_tex_result_resource;
	unsigned int size_tex_data;
	unsigned int bytePerPixel;

	unsigned int image_width;
	unsigned int image_height;

	// Timer
	int fpsCount;
	C_Timer timer;

	C_Timer timerqFPSMode;
	double timeStartFPSMode;
	double ValueFPS;

	bool m_bInitRender;

	bool m_bUseGPU;

	size_t iAllFrames;
	size_t iCurPlayFrameNumber;

public:
	BaseGPURender();
	virtual ~BaseGPURender();

	int SetParameters(bool bVSync, bool bRotate, bool bMaxFPS);
	int Init(std::string filename, size_t iMaxCountDecoders = 2, bool useCuda = false);
	int InitAudioTrack(std::string filename, CC_FRAME_RATE frameRate);

	int StartPipe();
	int StopPipe();

	bool IsInit() { return m_bInitRender; }

protected:
	int CreateWnd();
	int DestroyWindow();
	int UpdateWindow();

	virtual int RenderWindow() = 0;
	virtual int InitRender() = 0;
	virtual int DestroyRender() = 0;
	virtual int SetVerticalSync(bool bVerticalSync);
	virtual int GenerateImage(bool & bRotateFrame) = 0;
	virtual int GenerateCUDAImage(bool & bRotateFrame);
	virtual int CopyBufferToTexture(C_Block *pBlock) = 0;

	int CopyCUDAImage(C_Block *pBlock);
	int ComputeFPS();
	void SetPause(bool bPause);

	void SeekToFrame(size_t iFrame);
	void SeekToFrame(int x, int y);

protected:
	DWORD ThreadProc();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT ProcessWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

