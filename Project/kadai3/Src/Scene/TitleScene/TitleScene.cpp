#include <DxLib.h>

#include "TitleScene.h"
#include "../../Application/Application.h"
#include "../../UI/UIButton.h"
#include "../../Input/InputManager.h"
#include "../../Scene/SceneManager/SceneManager.h"

// �R���X�g���N�^
TitleScene::TitleScene(void)
{}

// �f�X�g���N�^
TitleScene::~TitleScene(void)
{}

// ������
void TitleScene::Init(void)
{
}

// �ǂݍ���
void TitleScene::Load(void)
{
	handle_ = LoadGraph("Data/Image/Title.png");
	
	// �{�^���쐬
	button_ = new UIButton(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 + 240,
		258,
		88
	);

	button_->Load();
}

// �ǂݍ��݌�̏���
void TitleScene::LoadEnd(void)
{
	// ������
	Init();
	button_->Init();
}

// �X�V
void TitleScene::Update(void)
{
	button_->Update();

	// ���̃V�[���֑J�ڂ���֐�
	toNextScene();
}

// �`��
void TitleScene::Draw(void)
{
	DrawExtendGraph(
		0,
		0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		handle_,
		true
	);

	button_->Draw();
}

// ���
void TitleScene::Release(void)
{
	DeleteGraph(handle_);
}

// ���̃V�[���֑J��
void TitleScene::toNextScene(void)
{
	// �V�[���J��
	// �X�y�[�X�L�[������ �������� �{�^�����N���b�N������ƑJ�ڂ���I
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_SPACE) ||
		button_->GetButtonState() == BUTTON_STATE::AFTER_CLICK)
	{
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}
