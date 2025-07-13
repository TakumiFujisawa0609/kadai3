#pragma once
#include "../SceneBase.h"

// �O���錾
class Grid;
class Stage;
class Player;
class EnemyBase;

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
	// �f�o�b�O�`��
	void DebugDraw(void);

	// �Փ˔���
	void Collision(void);

	// �X�e�[�W�ƃv���C���[�̏Փ˔���
	void CollisionStage(void);

private:
	Grid* grid_;		// �O���b�h�N���X(�f�o�b�O�p)

	Stage* stage_;		// �X�e�[�W�Ǘ�
	Player* player_;	// �v���C���[
	EnemyBase* enemy_;	// �G�l�~�[

	// �n�ʂƂ̏Փ˗p����
	VECTOR lineTopPos_;
	VECTOR lineDownPos_;
};
