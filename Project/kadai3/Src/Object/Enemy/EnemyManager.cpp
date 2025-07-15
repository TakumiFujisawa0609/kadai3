#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Demon/Demon.h"
#include "Wizard/Wizard.h"

EnemyManager::EnemyManager(void)
{
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(Player* player)
{
	player_ = player;

	// �o���Ԋu�̏�����
	spawnInterval_ = 0;

	// ���ׂẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		// ������
		enemy->Init(player_);
	}
}

void EnemyManager::Load(void)
{
	// �I���W�i���n���h���̍쐬
	originModelId_[static_cast<int>(EnemyBase::TYPE::DEMON)] = 
		MV1LoadModel("Data/Model/Enemy/Demon.mv1");
	originModelId_[static_cast<int>(EnemyBase::TYPE::WIZARD)] =
		MV1LoadModel("Data/Model/Enemy/Wizard.mv1");
	originModelId_[static_cast<int>(EnemyBase::TYPE::GIANT)] =
		MV1LoadModel("Data/Model/Enemy/Giant.mv1");

	// �G�l�~�[�̐���
	// �G�l�~�[�̍ő吔���m�ۂ��Ă���
	for (int i = 0; i < ENEMY_MAX_NUM; i++)
	{
		// �Ƃ肠�����A�������ɃE�B�U�[�h��
		if (i % 2 == 0)
		{
			// �f�[�����𐶐�
			EnemyBase* enemy = new Demon();

			// �ǂݍ���
			enemy->Load(
				EnemyBase::TYPE::DEMON,
				originModelId_[static_cast<int>(EnemyBase::TYPE::DEMON)]);

			// �쐬�����G�l�~�[��z��ɓ����
			enemys_.push_back(enemy);
		}
		else
		{
			// �E�B�U�[�h�𐶐�
			EnemyBase* enemy = new Wizard();

			// �ǂݍ���
			enemy->Load(
				EnemyBase::TYPE::WIZARD,
				originModelId_[static_cast<int>(EnemyBase::TYPE::WIZARD)]);

			// �쐬�����G�l�~�[��z��ɓ����
			enemys_.push_back(enemy);
		}

	}
}

void EnemyManager::LoadEnd(void)
{
	// ���ׂẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		// �X�V
		enemy->LoadEnd();
	}
}

void EnemyManager::Update(void)
{
	// �o���C���^�[�o�������Z
	spawnInterval_++;

	// ���Ԋu�ŃG�l�~�[���o��������
	if (spawnInterval_ > SPAWN_INTERVAL)
	{
		// �G�l�~�[�̐����t���O�𗧂Ă�
		// ���ׂẴG�l�~�[����
		for (EnemyBase* enemy : enemys_)
		{
			// �������Ă��Ȃ��G������
			if (!enemy->GetIsAlive())
			{
				// �����t���O�𗧂Ă�
				enemy->SetIsAlive(true);

				// �o���C���^�[�o����������
				spawnInterval_ = 0;

				// ���[�v�𔲂���
				break;
			}
		}
	}

	// ���ׂẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		// �������Ă��Ȃ��Ȃ珈�����Ȃ�
		if (!enemy->GetIsAlive())
			continue;

		// �X�V
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	// ���ׂẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		// �������Ă��Ȃ��Ȃ珈�����Ȃ�
		if (!enemy->GetIsAlive())
			continue;

		// �`��
		enemy->Draw();
	}
}

void EnemyManager::Release(void)
{
	// ���ׂẴG�l�~�[����
	for (EnemyBase* enemy : enemys_)
	{
		// ���
		enemy->Release();
	}
}
