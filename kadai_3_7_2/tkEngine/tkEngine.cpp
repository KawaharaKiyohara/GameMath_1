/*!
 *@brief	�G���W��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkGameObjectManager.h"
#include "tkEngine/timer/tkStopwatch.h"

namespace tkEngine {
	CEngine::CEngine()
	{

	}
	CEngine::~CEngine()
	{
		Final();
	}
	bool CEngine::Init(const SInitParam& initParam)
	{
		std::locale("");
		//�J�����g�f�B���N�g����Assets�ɁB
		SetCurrentDirectory("Assets");
		//�E�B���h�E�������B
		if (!InitWindow(initParam)) {
			return false;
		}
		//GameObjectManager�̏������B
		GameObjectManager().Init(initParam.gameObjectPrioMax);
		//GraphicsEngine�̏������B
		if (!m_graphicsEngine.Init(m_hWnd, initParam)) {
			return false;
		}
		//SoundEngine�̏�����
		m_soundEngine.Init();
		//�����G���W���̏������B
		m_physicsWorld.Init();
		//�������������B
		m_random.Init((unsigned long)time(NULL));
		//�p�b�h���������B
		int padNo = 0;
		for (auto& pad : m_pad) {
			pad.Init(padNo);
			padNo++;
		}
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		m_font = std::make_unique<CFont>();
		m_vectorRender = NewGO<prefab::CVectorRender>(initParam.gameObjectPrioMax-1);
		//�x�N�g���f�o�b�O��L���ɂ���B
		dbg::SetDrawVectorEnable();
#endif
		return true;
	}
	bool CEngine::InitWindow(const SInitParam& initParam)
	{
		TK_ASSERT(initParam.screenHeight != 0, "screenHeight is zero");
		TK_ASSERT(initParam.screenWidth != 0, "screenWidth is zero");

		m_screenHeight = initParam.screenHeight;
		m_screenWidth = initParam.screenWidth;
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
			TEXT("�Q�[�����w����@���K���P"), nullptr
		};
		RegisterClassEx(&wc);
		// Create the application's window
		RECT rc = { 0, 0, m_screenWidth,m_screenHeight };
		AdjustWindowRect(
			&rc,                                      // �N���C�A���g��`
			WS_OVERLAPPED,							  // �E�B���h�E�X�^�C��
			FALSE                                     // ���j���[�t���O
		);
		m_hWnd = CreateWindow(TEXT("�Q�[�����w����@���K���P"), TEXT("�Q�[�����w����@���K���P"),
			WS_OVERLAPPEDWINDOW, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
			nullptr, nullptr, wc.hInstance, nullptr);


		ShowWindow(m_hWnd, initParam.nCmdShow);
		return m_hWnd != nullptr;
	}
	void CEngine::ResourceUnload()
	{
		m_graphicsEngine.GetDirectXModelResource().Release();
		m_graphicsEngine.GetEffectEngine().GetResourceManager().Release();
		m_soundEngine.GetWaveFileBank().ReleaseAll();
	}
	void CEngine::Final()
	{
		m_physicsWorld.Release();
		m_soundEngine.Release();
		m_graphicsEngine.Release();
		
	}
	void CEngine::RunGameLoop()
	{
		MSG msg = {0};
	    while( WM_QUIT != msg.message )
	    {
	        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	        {
	            TranslateMessage( &msg );
	            DispatchMessage( &msg );
	        }
	        else
	        {
				//�X�V�B
				Update();
	        }
	    }
	}
	void CEngine::Update()
	{
		
		m_sw.Start();
		
		//�p�b�h�̍X�V�B
		for (auto& pad : m_pad) {
			pad.Update();
		}
		//�T�E���h�G���W���̍X�V�B
		m_soundEngine.Update();
		//GameObjectManager�X�V
		GameObjectManager().Execute();
		
		//�����G���W���̍X�V�B
		m_physicsWorld.Update();
#if 0
		static int count = 0;
		m_timeTotal += (float)m_sw.GetElapsed();
		count++;
		if (count == 30) {
			m_fps = 1.0f / (m_timeTotal / count);
			m_timeTotal = 0.0f;
			count = 0;
			
		}
		
		m_font->Begin(GraphicsEngine().GetRenderContext());
		wchar_t fps[256];
		swprintf_s(fps, L"FPS = %f", m_fps);
		float w = (float)GraphicsEngine().Get2DSpaceScreenWidth();
		float h = (float)GraphicsEngine().Get2DSpaceScreenHeight();
		m_font->Draw(
			fps, 
			{ 
				w * -0.5f,
				h * 0.5f
			},
			CVector4::White,
			0.0f,
			1.0f,
			{0.0f, 1.0f}
		);
		m_font->End(GraphicsEngine().GetRenderContext());
#endif
		m_graphicsEngine.EndRender();
		
		m_sw.Stop();
		
		GameTime().PushFrameDeltaTime((float)m_sw.GetElapsed());
	}
	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch (msg)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return 0;
	}
}