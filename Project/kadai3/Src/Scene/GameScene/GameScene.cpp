#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyManager.h"
#include "../../Utility/AsoUtility.h"


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

	// �G�l�~�[�Ǘ��̏�����
	enemyManager_->Init(player_);
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

	// �G�l�~�[�Ǘ��̐���
	enemyManager_ = new EnemyManager();
	enemyManager_->Load();
}

// �ǂݍ��݌�̏�����
void GameScene::LoadEnd(void)
{
	// ������
	Init();

	stage_->LoadEnd();
	player_->LoadEnd();
	enemyManager_->LoadEnd();
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

	// �G�l�~�[�Ǘ��̍X�V
	enemyManager_->Update();

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

	// �G�l�~�[�Ǘ��̕`��
	enemyManager_->Draw();

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

	// �G�l�~�[�Ǘ��̉��
	enemyManager_->Release();
	delete enemyManager_;
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

	// �G�l�~�[�ƃv���C���[�̏Փ�
	CollisionEnemy();

	// �G�l�~�[�ƃv���C���[�̍U���̏Փ�
	CollisionAttack();
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

void GameScene::CollisionEnemy(void)
{
	// �v���C���[�̍��W
	VECTOR playerPos = player_->GetPos();

	// �G�̏����擾
	std::vector<EnemyBase*> enemys = enemyManager_->GetEnemys();

	// �G��S�Č���
	for (EnemyBase* enemy : enemys)
	{
		// �G���������Ă��Ȃ��Ȃ疳������
		if (!enemy->GetIsAlive())
			continue;

		// �G�̍��W
		VECTOR enemyPos = enemy->GetPos();

		// �G�ƃv���C���[�̏Փ˔���(����)
		if (AsoUtility::IsHitSpheres(
			playerPos,
			Player::COLL_RADIUS,
			enemyPos,
			enemy->GetCollRadius()
		))
		{
			// �m�b�N�o�b�N����XZ���������߂�
			VECTOR diff = VSub(playerPos, enemyPos);
			diff.y = 0.0f;
			VECTOR dir = VNorm(diff);
			// �v���C���[���m�b�N�o�b�N������
			player_->KnockBack(dir, 20.0f);
		}

		// �e���擾
		std::vector<BulletBase*> bullets = enemy->GetBullets();

		// �S�Ă̒e������
		for (BulletBase* bullet : bullets)
		{
			// �e�̍��W
			VECTOR bulletPos = bullet->GetPos();

			// �G�̒e�ƃv���C���[�̏Փ˔���(����)
			if (AsoUtility::IsHitSpheres(
				playerPos,
				Player::COLL_RADIUS,
				bulletPos,
				bullet->GetCollisionRadius()
			))
			{
				// �m�b�N�o�b�N����XZ���������߂�
				VECTOR diff = VSub(playerPos, bulletPos);
				diff.y = 0.0f;
				VECTOR dir = VNorm(diff);
				// �v���C���[���m�b�N�o�b�N������
				player_->KnockBack(dir, 20.0f);
			}
		}
	}
}

void GameScene::CollisionAttack(void)
{
	// �v���C���[���U����ԂłȂ��Ȃ珈�����Ȃ�
	if (player_->GetState() != Player::STATE::ATTACK)
		return;

	// �G�̏����擾
	auto enemys = enemyManager_->GetEnemys();

	// �G��S�Č���
	for (auto enemy : enemys)
	{
		// �G���������Ă��Ȃ��Ȃ疳������
		if (!enemy->GetIsAlive())
			continue;

		// �G�̍��W���擾
		VECTOR enemyPos = enemy->GetPos();

		// �Փ˔���(����)
		if (AsoUtility::IsHitSpheres(
			player_->GetAttackPos(),
			Player::ATTACK_RADIUS,
			enemyPos,
			enemy->GetCollRadius())
			)
		{
			// �G�l�~�[�Ƀ_���[�W��^����
			enemy->SetIsAlive(false);
		}
	}
}
