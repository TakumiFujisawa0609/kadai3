#include <DxLib.h>
#include "SceneManager.h"
#include "../../Scene/TitleScene/TitleScene.h"
#include "../../Scene/GameScene/GameScene.h"

SceneManager* SceneManager::instance_ = nullptr;

// �R���X�g���N�^
SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	scene_ = nullptr;
	isGameEnd_ = false;
}

// �f�X�g���N�^
SceneManager::~SceneManager(void)
{
}

// ������
void SceneManager::Init(void)
{
	// 3D���̏�����
	Init3D();

	// �ŏ��̓^�C�g����ʂ���
	ChangeScene(SCENE_ID::TITLE);
}

// 3D���̏�����
void SceneManager::Init3D(void)
{
	// �w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g�̐ݒ�
	SetUseLighting(true);

	// ���ʂ���΂߉��Ɍ����������C�g
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });
}

// �X�V
void SceneManager::Update(void)
{
	// �V�[�����Ȃ���ΏI��
	if (scene_ == nullptr) { return; }

	// ���݂̃V�[���̍X�V
	scene_->Update();
}

// �`��
void SceneManager::Draw(void)
{
	// ���݂̃V�[���̕`��
	scene_->Draw();
}

// ���
void SceneManager::Release(void)
{
	// ���݂̃V�[���̉���E�폜
	scene_->Release();
	delete scene_;
}

// ��ԑJ�ڊ֐�
void SceneManager::ChangeScene(SCENE_ID nextId)
{
	// �V�[����ύX����
	sceneId_ = nextId;

	// ���݂̃V�[�������
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	// �e�V�[���ɐ؂�ւ�
	switch (sceneId_)
	{
	case SceneManager::SCENE_ID::NONE:
		break;
	case SceneManager::SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case SceneManager::SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	default:
		break;
	}

	// �ǂݍ���(�񓯊�)
	scene_->Load();
}
