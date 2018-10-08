#pragma once

class Background;
class Player;
class GameCamera;
class Fade;

class QuestionBase : public IGameObject
{
protected:
	//テストの結果。
	enum EnTestResult {
		enTestResult_Failed,	//テスト失敗。
		enTestResult_Progress,	//テスト実行中。
		enTestResult_Success,	//テスト成功。
	};
public:
	QuestionBase();
	virtual ~QuestionBase();
	void Update() override;
	void PostRender(CRenderContext& rc) override;
private:
	virtual EnTestResult OnTestProgress() = 0;
	virtual const wchar_t* GetTitleText() const = 0;
	virtual const wchar_t* GetFailedText() const = 0;
protected:
	enum EnStep {
		enStep_FadeInStart,		//フェードイン開始。
		enStep_FadeIn,			//フェードイン。
		enStep_TitleIn,			//タイトル入場中。
		enStep_TitleDisp,		//タイトルを表示中。
		enStep_TitleOut,		//タイトル退場中。
		enStep_TestProgress,	//テスト実行中。
		enStep_TestFailedIn,	//テスト失敗のテキスト入場。
		enStep_TestFailed,		//テスト失敗。
		enStep_TestSuccess,		//テスト成功。
		enStep_GameOver,		//ゲーム終わり。
	};
	
	EnStep m_step = enStep_FadeInStart;	//実行ステップ
	Background* m_background = nullptr;	//背景。
	Player* m_player = nullptr;			//プレイヤー。	
private:
	const CVector2 m_titleInStartPos = { -1300.0f, 200.0f };
	CVector2 m_tatileOutStartPos;
	CVector2 m_titlePos = m_titleInStartPos;
	float m_timer = 0.0f;	//いろんなモノに使うタイマーちゃん。
	Fade* m_fade = nullptr;
	std::vector<prefab::CDirectionLight*>	m_dirLights;	//ディレクションライトのリスト。	
	GameCamera* m_gameCamera = nullptr;	//ゲームカメラ。
	CFont m_font;		//フォント。
	std::wstring m_fontText;
	prefab::CSoundSource* m_bgm = nullptr;
};

