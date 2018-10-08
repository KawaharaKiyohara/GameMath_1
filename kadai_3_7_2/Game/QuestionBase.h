#pragma once

class Background;
class Player;
class GameCamera;
class Fade;

class QuestionBase : public IGameObject
{
protected:
	//�e�X�g�̌��ʁB
	enum EnTestResult {
		enTestResult_Failed,	//�e�X�g���s�B
		enTestResult_Progress,	//�e�X�g���s���B
		enTestResult_Success,	//�e�X�g�����B
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
		enStep_FadeInStart,		//�t�F�[�h�C���J�n�B
		enStep_FadeIn,			//�t�F�[�h�C���B
		enStep_TitleIn,			//�^�C�g�����ꒆ�B
		enStep_TitleDisp,		//�^�C�g����\�����B
		enStep_TitleOut,		//�^�C�g���ޏꒆ�B
		enStep_TestProgress,	//�e�X�g���s���B
		enStep_TestFailedIn,	//�e�X�g���s�̃e�L�X�g����B
		enStep_TestFailed,		//�e�X�g���s�B
		enStep_TestSuccess,		//�e�X�g�����B
		enStep_GameOver,		//�Q�[���I���B
	};
	
	EnStep m_step = enStep_FadeInStart;	//���s�X�e�b�v
	Background* m_background = nullptr;	//�w�i�B
	Player* m_player = nullptr;			//�v���C���[�B	
private:
	const CVector2 m_titleInStartPos = { -1300.0f, 200.0f };
	CVector2 m_tatileOutStartPos;
	CVector2 m_titlePos = m_titleInStartPos;
	float m_timer = 0.0f;	//�����ȃ��m�Ɏg���^�C�}�[�����B
	Fade* m_fade = nullptr;
	std::vector<prefab::CDirectionLight*>	m_dirLights;	//�f�B���N�V�������C�g�̃��X�g�B	
	GameCamera* m_gameCamera = nullptr;	//�Q�[���J�����B
	CFont m_font;		//�t�H���g�B
	std::wstring m_fontText;
	prefab::CSoundSource* m_bgm = nullptr;
};

