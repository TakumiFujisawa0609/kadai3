#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyBase.h"

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

	// �G�l�~�[�̏�����
	enemy_->Init();
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

	// �G�l�~�[�̐���
	enemy_ = new EnemyBase();
	enemy_->Load();
}

// �ǂݍ��݌�̏�����
void GameScene::LoadEnd(void)
{
	// ������
	Init();

	stage_->LoadEnd();
	player_->LoadEnd();
	enemy_->LoadEnd();
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

	// �G�l�~�[�̍X�V
	enemy_->Update();

	// �Փ˔���
	Collision();
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

	// �G�l�~�[�̕`��
	enemy_->Draw();

	// �f�o�b�O�`��
	DebugDraw();
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

	// �G�l�~�[�̉��
	enemy_->Release();
	delete enemy_;
}

void GameScene::DebugDraw(void)
{
	// �n�ʂƂ̏Փ˗p����
	DrawSphere3D(lineTopPos_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
	DrawSphere3D(lineDownPos_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
	DrawLine3D(lineTopPos_, lineDownPos_, 0xff0000);
}

void GameScene::Collision(void)
{
	// �X�e�[�W�u���b�N�ƃv���C���[�̏Փ�
	CollisionStage();
}

void GameScene::CollisionStage(void)
{
	// �X�e�[�W�u���b�N�ƃv���C���[�̏Փ�
	VECTOR playerPos = player_->GetPos();

	// �����̏���W
	VECTOR topPos = playerPos;
	topPos.y = playerPos.y + (Player::COLL_LEN * 2.0f);
	lineTopPos_ = topPos;

	// �����̉����W
	VECTOR downPos = playerPos;
	downPos.y = playerPos.y - Player::COLL_LEN;
	lineDownPos_ = downPos;

	// �����ƃu���b�N���f���̏Փ˔���
	MV1_COLL_RESULT_POLY result;
	if (stage_->IsCollisionLine(topPos, downPos, &result))
	{
		// �v���C���[�ɏՓˍ��W��n��
		player_->CollisionStage(result.HitPosition);
	}
}
