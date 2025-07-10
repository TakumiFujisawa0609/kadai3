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
	// 各種ブロックモデルのロード
	blockOriginModelId_[static_cast<int>(Block::TYPE::GRASS)]
		= MV1LoadModel("Data/Model/Blocks/Block_Grass.mv1");
	blockOriginModelId_[static_cast<int>(Block::TYPE::METAL)]
		= MV1LoadModel("Data/Model/Blocks/Block_Metal.mv1");
	blockOriginModelId_[static_cast<int>(Block::TYPE::ICE)]
		= MV1LoadModel("Data/Model/Blocks/Block_Ice.mv1");

	// マップ読み込み
	LoadMapCsvData();
}

void Stage::LoadEnd(void)
{
	// 初期化
	Init();
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	// マップの描画
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
	// モデルのメモリ解放
	for (int i = 0; i < BLOCK_MODEL_NUM; i++)
	{
		MV1DeleteModel(blockOriginModelId_[i]);
	}
}

bool Stage::IsCollisionLine(VECTOR topPos, VECTOR downPos, MV1_COLL_RESULT_POLY* result)
{
	bool ret = false;

	for (int z = 0; z < BLOCK_NUM_Z; z++)
	{
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			// 2次元配列からBlock情報を取り出す
			Block* block = blocks_[z][x];

			// 線分とモデルの衝突判定
			MV1_COLL_RESULT_POLY res =
				MV1CollCheck_Line(block->GetModelId(), -1, topPos, downPos);

			// 当たった
			if (res.HitFlag)
			{
				// 結果を返す
				*result = res;
				return true;
			}
		}
	}

	return ret;
}

void Stage::LoadMapCsvData(void)
{
	// ファイルの読込
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");
	if (!ifs)
	{
		// エラーが発生
		return;
	}

	// ファイルを１行ずつ読み込む
	std::string line;					// 1行の文字情報
	std::vector<std::string> strSplit;	// 1行を1文字の動的配列に分割
	int chipNo = 0;
	int z = 0;

	while (getline(ifs, line))
	{
		// １行をカンマ区切りで分割
		strSplit = AsoUtility::Split(line, ',');

		for (int x = 0; x < strSplit.size(); x++) 
		{
			// stringからintに変換
			chipNo = stoi(strSplit[x]);

			Block::TYPE type = static_cast<Block::TYPE>(chipNo);

			int baseModelId = blockOriginModelId_[chipNo];

			// ブロックを生成
			Block* block = new Block();
			block->Create(type, baseModelId, x, z);

			// ２次元配列にブロックを格納			
			blocks_[z][x] = block;
		}

		z++;
	}
}
