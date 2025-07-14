#include "EnemyManager.h"
#include "EnemyBase.h"

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
	// �G�l�~�[�̐���
	// �G�l�~�[�̍ő吔���m�ۂ��Ă���
	for (int i = 0; i < ENEMY_MAX_NUM; i++)
	{
		EnemyBase* enemy = new EnemyBase();
		enemy->Load();

		// �쐬�����G�l�~�[��z��ɓ����
		enemys_.push_back(enemy);
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
