#pragma once
#include "../SceneBase.h"

// クラスの前方宣言
class UIButton;

// ベースを継承
class TitleScene : public SceneBase
{
public:

	TitleScene(void);				// コンストラクタ
	~TitleScene(void) override;		// デストラクタ

public:

	void Init(void)		override;	// 初期化
	void Load(void)		override;	// 読み込み
	void LoadEnd(void)	override;	// 読み込み後の処理
	void Update(void)	override;	// 更新
	void Draw(void)		override;	// 描画
	void Release(void)	override;	// 解放

	void toNextScene(void);			// 次のシーンへ

private:
	int handle_;
	UIButton *button_;
};
