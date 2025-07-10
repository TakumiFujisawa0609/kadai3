#pragma once
#include "../SceneBase.h"

// �O���錾
class Grid;
class Stage;
class Player;

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

	Stage* stage_;		// �X�e�[�W�Ǘ�
	Player* player_;	// �v���C���[
};
