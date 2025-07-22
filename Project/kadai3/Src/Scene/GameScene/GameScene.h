#pragma once
#include "../SceneBase.h"

// �O���錾
class Grid;
class Stage;
class Player;
class EnemyManager;

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

	// �G�l�~�[�ƃv���C���[�̏Փ˔���
	void CollisionEnemy(void);

private:
	Grid* grid_;		// �O���b�h�N���X(�f�o�b�O�p)

	EnemyManager* enemyManager_;	// �G�l�~�[�Ǘ�
	Stage* stage_;					// �X�e�[�W�Ǘ�
	Player* player_;				// �v���C���[

	// �n�ʂƂ̏Փ˗p����
	VECTOR lineTopPos_;
	VECTOR lineDownPos_;
};
