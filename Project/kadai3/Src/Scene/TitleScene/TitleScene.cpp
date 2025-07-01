#include <DxLib.h>

#include "TitleScene.h"
#include "../../Application/Application.h"

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
}

// �ǂݍ��݌�̏���
void TitleScene::LoadEnd(void)
{
	// ������
	Init();
}

// �X�V
void TitleScene::Update(void)
{
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
}

// ���
void TitleScene::Release(void)
{
	DeleteGraph(handle_);
}

// ���̃V�[���֑J��
void TitleScene::toNextScene(void)
{
}
