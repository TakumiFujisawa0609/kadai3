#pragma once
#include <DxLib.h>
#include "Block.h"

class Block;

class Stage
{

public:

	// ブロック用のモデル種類
	static constexpr int BLOCK_MODEL_NUM = static_cast<int>(Block::TYPE::MAX);

	// ブロックの数(マップのサイズ)
	static constexpr int BLOCK_NUM_X = 5;
	static constexpr int BLOCK_NUM_Z = 5;

	// コンストラクタ
	Stage(void);

	// デストラクタ
	~Stage(void);

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// ブロックのオリジナルハンドル
	int blockOriginModelId_[BLOCK_MODEL_NUM];

	// マップデータ
	int mapData_[BLOCK_NUM_Z][BLOCK_NUM_X] =
	{
		{ 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1 }
	};

	// ブロッククラス格納用
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];

};
