#pragma once

// グリッド線の表示
class Grid
{

public:
	// 定数定義

	// 線の長さ
	static constexpr float LEN = 3000.0f;

	// 線の長さの半分
	static constexpr float HLEN = LEN / 2.0f;

	// 線の間隔
	static constexpr float DISTANCE = 100.0f;

	// 線の数
	static const int NUM = static_cast<int>(LEN / DISTANCE);

	// 線の数の半分
	static const int HNUM = NUM / 2;

	// コンストラクタ
	Grid(void);

	// デストラクタ
	~Grid(void);

	void Init(void);		// 初期化
	void Update(void);		// 更新
	void Draw(void);		// 描画
	void Release(void);		// 更新

};
