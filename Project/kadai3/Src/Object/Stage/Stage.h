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
	static constexpr int BLOCK_NUM_X = 5;
	static constexpr int BLOCK_NUM_Z = 5;

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

private:

	// �u���b�N�̃I���W�i���n���h��
	int blockOriginModelId_[BLOCK_MODEL_NUM];

	// �}�b�v�f�[�^
	int mapData_[BLOCK_NUM_Z][BLOCK_NUM_X] =
	{
		{ 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1 }
	};

	// �u���b�N�N���X�i�[�p
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];

};
