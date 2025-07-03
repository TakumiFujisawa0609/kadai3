#pragma once
#include "../SceneBase.h"

// �O���錾
class Grid;
class Camera;

// �x�[�X���p��
class GameScene : public SceneBase
{
public:

	GameScene();			// �R���X�g���N�^
	~GameScene() override;	// �f�X�g���N�^

public:
	void Init(void)		override;	// ������
	void Load(void)		override;	// �ǂݍ���
	void LoadEnd(void)	override;	// �ǂݍ��݌�̏�����
	void Update(void)	override;	// �X�V
	void Draw(void)		override;	// �`��
	void Release(void)	override;	// ���

private:
	Grid* grid_;		// �O���b�h�N���X(�f�o�b�O�p)
	Camera* camera_;	// �J�����N���X
};
