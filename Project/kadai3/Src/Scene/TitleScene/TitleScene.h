#pragma once
#include "../SceneBase.h"

// �N���X�̑O���錾
class UIButton;

// �x�[�X���p��
class TitleScene : public SceneBase
{
public:

	TitleScene(void);				// �R���X�g���N�^
	~TitleScene(void) override;		// �f�X�g���N�^

public:

	void Init(void)		override;	// ������
	void Load(void)		override;	// �ǂݍ���
	void LoadEnd(void)	override;	// �ǂݍ��݌�̏���
	void Update(void)	override;	// �X�V
	void Draw(void)		override;	// �`��
	void Release(void)	override;	// ���

	void toNextScene(void);			// ���̃V�[����

private:
	int handle_;
	UIButton *button_;
};
