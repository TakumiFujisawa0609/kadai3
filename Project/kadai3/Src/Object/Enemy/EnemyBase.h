#pragma once
#include <DxLib.h>
#include <vector>


// �N���X�̑O���錾
class Player;
class BulletBase;

class EnemyBase
{
public:
	// �G�l�~�[���
	enum class TYPE
	{
		DEMON,	// ����
		WIZARD,	// ���@�g��
		GIANT,	// ���l
		MAX,
	};

	// ���
	enum class STATE
	{
		IDLE,	// �ҋ@
		MOVING,	// �ړ�
		ATTACK,	// �U��
	};

	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		ATTACK,	// �U��
		DEAD,	// ���S
		HIT,	// �q�b�g
		IDLE,	// �ҋ@
		JUMP,	// �W�����v
		RUN,	// ����
		WALK,	// ����
		MAX
	};

public:
	// �萔
	// ���Ȕ���
	static constexpr COLOR_F EMI_COLOR = { 0.6f,0.6f,0.6f,1.0f };

public:

	// �R���X�g���N�^
	EnemyBase(void);

	// �f�X�g���N�^
	virtual ~EnemyBase(void);

	// ��������
	void Init(Player* player);

	// �ǂݍ���
	void Load(TYPE type, int originModelId);

	// �ǂݍ��݌�
	void LoadEnd(void);

	// �X�V����
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �������
	void Release(void);

	// �����t���O�𗧂Ă�
	void SetIsAlive(bool isAlive);

	// �����t���O���擾����
	bool GetIsAlive(void);

	// ��ԑJ��
	void ChangeState(STATE state);

private:
	// �v���C���[�̕���������
	void LookPlayer(void);

	// �ړ�
	void Move(void);

	// �A�j���[�V�����Đ�
	void UpdateAnim(void);

	// �o�����W�̐ݒ�
	void SetSpawnPosition(void);

protected:
	// �p�����[�^�̐ݒ�(�������z�֐�)
	virtual void SetParam(void) = 0;

	// ��ԑJ��
	virtual void ChangeMoving(void);
	virtual void ChangeAttack(void);

	// ��ԕʍX�V
	virtual void UpdateMoving(void);
	virtual void UpdateAttack(void);

	// ��ԕʕ`��
	virtual void DrawMoving(void);
	virtual void DrawAttack(void);

	// �e�̍X�V
	void UpdateBullet(void);

	// �e�̕`��
	void DrawBullet(void);

	// �L���Ȓe���擾
	BulletBase* GetValidBullet(void);

protected:
	// �Փ˔���p���a
	float collRadius_;

	// �o���͈�(���a)
	float spawnRange_;

	// �̗�
	int hp_;

	// �ړ����x
	float speed_;

	// �v���C���[�̏��A�h���X
	Player* player_;

	// ���f���̃n���h��ID
	int modelId_;

	// �����t���O
	bool isAlive_;

	// ���
	TYPE type_;

	// ���
	STATE state_;

	// ���W
	VECTOR pos_;
	// �p�x
	VECTOR angle_;
	// �傫��
	VECTOR scale_;
	// �ړ�����
	VECTOR moveDir_;

	// �A�j���[�V����
	ANIM_TYPE prevAnimType_;	// �O��̃A�j���[�V�������
	ANIM_TYPE nowAnimType_;		// ���݂̃A�j���[�V�������

	int attachNo_;				// �A�^�b�`No
	float nowAnimTime_;			// �Đ����̎���
	float totalAnimTime_;		// ���Đ�����

	// �U��
	int attackCount_;

	// �e
	std::vector<BulletBase*> bullets_;

	// �G�t�F�N�g�p���f���n���h��ID
	int baseAttackEffectModelId_;

};


