#pragma once
#include <DxLib.h>

class Block
{
public:

	// ブロックモデルの自己発光色
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

	// ブロックモデルの大きさ
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };

	// 1ブロックあたりのサイズ
	static constexpr float SIZE = 100.0f;

	// ブロック種別
	enum class TYPE
	{
		NONE = -1,
		GRASS,
		METAL,
		ICE,

		MAX
	};

	// コンストラクタ
	Block(void);

	// デストラクタ
	~Block(void);

	// ブロックを生成する
	void Create(TYPE type, int baseModelId, int mapX, int mapZ);
	void Update(void);
	void Draw(void);
	void Release(void);

	// モデルのハンドルIDを取得する
	int GetModelId(void);

private:

	// ブロック種別
	TYPE type_;

	// モデルのハンドルID
	int modelId_;

	// 座標
	VECTOR pos_;

	// 大きさ
	VECTOR scale_;

};
