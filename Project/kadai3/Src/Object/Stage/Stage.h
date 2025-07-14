#pragma once
#include <DxLib.h>
#include "Block.h"

class Block;

class Stage
{

public:

	// �u���b�N�p�̃��f�����
	static constexpr int BLOCK_MODEL_NUM = static_cast<int>(Block::TYPE::MAX);

	// �u���b�N�̐�(�}�b�v�̃T�C�Y)
	static constexpr int BLOCK_NUM_X = 20;
	static constexpr int BLOCK_NUM_Z = 20;

	// �X�e�[�W�S�̂�X�T�C�Y
	static constexpr float STAGE_SIZE_X =
		Block::SIZE * static_cast<float>(BLOCK_NUM_X);

	// �X�e�[�W�S�̂�Z�T�C�Y
	static constexpr float STAGE_SIZE_Z =
		Block::SIZE * static_cast<float>(BLOCK_NUM_Z);

	// �R���X�g���N�^
	Stage(void);

	// �f�X�g���N�^
	~Stage(void);

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �����ƃu���b�N�̏Փ˔���
	bool IsCollisionLine(
		VECTOR topPos, VECTOR downPos, MV1_COLL_RESULT_POLY* result);

private:
	// �}�b�v�f�[�^
	void LoadMapCsvData(void);

private:
	// �u���b�N�̃I���W�i���n���h��
	int blockOriginModelId_[BLOCK_MODEL_NUM];

	// �u���b�N�N���X�i�[�p
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];

};
