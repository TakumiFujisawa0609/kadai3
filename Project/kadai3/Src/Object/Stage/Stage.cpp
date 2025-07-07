#include <string>
#include "Block.h"
#include "Stage.h"
#include <fstream>
#include "../../Utility/AsoUtility.h"
#include "../../Application/Application.h"

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(void)
{
}

void Stage::Load(void)
{
	// �e��u���b�N���f���̃��[�h
	blockOriginModelId_[static_cast<int>(Block::TYPE::GRASS)]
		= MV1LoadModel("Data/Model/Blocks/Block_Grass.mv1");
	blockOriginModelId_[static_cast<int>(Block::TYPE::METAL)]
		= MV1LoadModel("Data/Model/Blocks/Block_Metal.mv1");
	blockOriginModelId_[static_cast<int>(Block::TYPE::ICE)]
		= MV1LoadModel("Data/Model/Blocks/Block_Ice.mv1");

	// �}�b�v�ǂݍ���
	LoadMapCsvData();
}

void Stage::LoadEnd(void)
{
	// ������
	Init();
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	// �}�b�v�̕`��
	for (int y = 0; y < BLOCK_NUM_Z; y++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			blocks_[y][x]->Draw();
		}
	}
}

void Stage::Release(void)
{
	// ���f���̃��������
	for (int i = 0; i < BLOCK_MODEL_NUM; i++)
	{
		MV1DeleteModel(blockOriginModelId_[i]);
	}
}

void Stage::LoadMapCsvData(void)
{
	// �t�@�C���̓Ǎ�
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");
	if (!ifs)
	{
		// �G���[������
		return;
	}

	// �t�@�C�����P�s���ǂݍ���
	std::string line;					// 1�s�̕������
	std::vector<std::string> strSplit;	// 1�s��1�����̓��I�z��ɕ���
	int chipNo = 0;
	int z = 0;

	while (getline(ifs, line))
	{
		// �P�s���J���}��؂�ŕ���
		strSplit = AsoUtility::Split(line, ',');

		for (int x = 0; x < strSplit.size(); x++) 
		{
			// string����int�ɕϊ�
			chipNo = stoi(strSplit[x]);

			Block::TYPE type = static_cast<Block::TYPE>(chipNo);

			int baseModelId = blockOriginModelId_[chipNo];

			// �u���b�N�𐶐�
			Block* block = new Block();
			block->Create(type, baseModelId, x, z);

			// �Q�����z��Ƀu���b�N���i�[			
			blocks_[z][x] = block;
		}

		z++;
	}
}
