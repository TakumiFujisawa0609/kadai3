#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"

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

	// �X�e�[�W������
	stage_->Init();

	// �v���C���[�̏�����
	player_->Init();
}

// �ǂݍ���
void GameScene::Load(void)
{
	// �O���b�h�̐���
	grid_ = new Grid();

	// �J�����̐���
	camera_ = new Camera();

	// �X�e�[�W�̐���
	stage_ = new Stage();
	stage_->Load();

	// �v���C���[�̐���
	player_ = new Player();
	player_->Load();
}

// �ǂݍ��݌�̏�����
void GameScene::LoadEnd(void)
{
	// ������
	Init();

	stage_->LoadEnd();
	player_->LoadEnd();
}

// �X�V
void GameScene::Update(void)
{
	// �O���b�h�X�V
	grid_->Update();

	// �J�����X�V
	camera_->Update();

	// �X�e�[�W�X�V
	stage_->Update();

	// �v���C���[�̍X�V
	player_->Update();
}

// �`��
void GameScene::Draw(void)
{
	// �O���b�h�`��
	grid_->Draw();

	// �J�����`��
	camera_->SetBeforeDraw();
	camera_->DrawDebug();

	// �X�e�[�W�`��
	stage_->Draw();

	// �v���C���[�̕`��
	player_->Draw();
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

	// �X�e�[�W���
	stage_->Release();
	delete stage_;

	// �v���C���[�̉��
	player_->Release();
	delete player_;
}
