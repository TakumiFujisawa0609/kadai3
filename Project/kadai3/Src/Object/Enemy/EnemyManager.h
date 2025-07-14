#pragma once
#include <vector>
#include "EnemyBase.h"

class EnemyBase;
class Player;

class EnemyManager
{
public:
	// �萔
	// �ő�̓G�̐�
	static constexpr int ENEMY_MAX_NUM = 10;

	// �G�̏o�����o
	static constexpr int SPAWN_INTERVAL = 200;

public:
	EnemyManager(void);		// �R���X�g���N�^
	~EnemyManager(void);	// �f�X�g���N�^

	void Init(Player* player);		// ������
	void Load(void);		// �ǂݍ���
	void LoadEnd(void);		// �ǂݍ��݌�
	void Update(void);		// �X�V
	void Draw(void);		// �`��
	void Release(void);		// ���

private:
	// �G�l�~�[�p�̃��f���n���h��ID
	int originModelId_[static_cast<int>(EnemyBase::TYPE::MAX)];

	// �G�l�~�[���܂Ƃ߂铮�I�z��
	std::vector<EnemyBase*> enemys_;

	// �v���C���[�̏��A�h���X
	Player* player_;

	// �o���Ԋu
	int spawnInterval_;

};
