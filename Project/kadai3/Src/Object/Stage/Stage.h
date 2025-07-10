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
	static constexpr int BLOCK_NUM_X = 20;
	static constexpr int BLOCK_NUM_Z = 20;

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

	// 線分とブロックの衝突判定
	bool IsCollisionLine(
		VECTOR topPos, VECTOR downPos, MV1_COLL_RESULT_POLY* result);

private:
	// マップデータ
	void LoadMapCsvData(void);

private:
	// ブロックのオリジナルハンドル
	int blockOriginModelId_[BLOCK_MODEL_NUM];

	// ブロッククラス格納用
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];

};
