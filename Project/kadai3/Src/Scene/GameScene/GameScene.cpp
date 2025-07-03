#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"

// �R���X�g���N�^
GameScene::GameScene()
{
}

// �f�X�g���N�^
GameScene::~GameScene()
{
}

// ������
void GameScene::Init(void)
{
	// �O���b�h������
	grid_->Init();

	// �J����������
	camera_->Init();
}

// �ǂݍ���
void GameScene::Load(void)
{
	// �O���b�h�̐���
	grid_ = new Grid();

	// �J�����̐���
	camera_ = new Camera();
}

// �ǂݍ��݌�̏�����
void GameScene::LoadEnd(void)
{
	// ������
	Init();
}

// �X�V
void GameScene::Update(void)
{
	// �O���b�h�X�V
	grid_->Update();

	// �J�����X�V
	camera_->Update();
}

// �`��
void GameScene::Draw(void)
{
	// �O���b�h�`��
	grid_->Draw();

	// �J�����`��
	camera_->SetBeforeDraw();
	camera_->DrawDebug();
}

// ���
void GameScene::Release(void)
{
	// �O���b�h���
	grid_->Release();
	delete grid_;

	// �J�������
	camera_->Release();
	delete camera_;
}
