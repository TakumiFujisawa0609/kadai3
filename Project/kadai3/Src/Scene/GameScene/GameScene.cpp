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
	Camera::GetInstance()->Init();

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
	Camera::CreateInstance();

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
	Camera::GetInstance()->Update();

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
	Camera::GetInstance()->SetBeforeDraw();
	Camera::GetInstance()->DrawDebug();

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
	Camera::GetInstance()->Release();
	Camera::DeleteInstance();

	// �X�e�[�W���
	stage_->Release();
	delete stage_;

	// �v���C���[�̉��
	player_->Release();
	delete player_;
}
