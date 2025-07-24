#pragma once
#include <DxLib.h>

class Player
{
public:
	// ���
	enum class STATE
	{
		NONE,
		MOVE,
		KNOCKBACK,
		ATTACK,
		DEAD,
		END,
		VICTORY,
	};

	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		DEAD,			// ���S
		DUCK,
		HIT_REACT,
		IDLE,			// �ҋ@
		IDLE_ATTACK,
		IDLE_HOLD,
		JUMP,			// �W�����v
		JUMP_IDLE,
		JUMP_LAND,
		NO,
		PUNCH,
		RUN,
		RUN_ATTACK,
		RUN_HOLD,
		WALK,			// ����
		WALK_HOLD,
		WAVE,
		YES,
		MAX,
	};

public:

	// ���f���̑傫��
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	// �����ʒu
	static constexpr VECTOR INIT_POS = { 300.0f, 10.0f, 300.0f };
	// �W���̎��Ȕ����F
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 0.5f };

	// �ړ��X�s�[�h
	static constexpr float MOVE_SPEED = 10.0f;

	// �d��
	static constexpr float GRAVITY = 0.8f;

	// �n�ʏՓ˔���p�̐����̒���
	static constexpr float COLL_LEN = 10.0f;

	// �����蔻��̔��a
	static constexpr float COLL_RADIUS = 50.0f;

	// �m�b�N�o�b�N�̃X�s�[�h
	static constexpr float KNOCKBACK_SPEED = 10.0f;

	// �W�����v��
	static constexpr float JUMP_POW = 20.0f;

	// ���X�|�[�����苗��
	static constexpr float RESPAWN_DIS = -1500.0f;

	// �W���̊g�U���F
	static constexpr COLOR_F DIF_COLOR_DEF = { 1.0f, 1.0f, 1.0f, 1.0f };

	// �_�Ŏ��̊g�U���F
	static constexpr COLOR_F DIF_COLOR_BLINK = { 1.0f, 0.5f, 0.5f, 1.0f };

	// �_�ŊԊu
	static constexpr int BLINK_INTERVAL = 8;

	// �U���̓����蔻��̔��a
	static constexpr float ATTACK_RADIUS = 100.0f;

	// �R���X�g���N�^
	Player(void);

	// �f�X�g���N�^
	~Player(void);

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ��Ԃ̎擾
	STATE GetState(void);

	// ���W�̎擾
	VECTOR GetPos(void);

	// �U�����W�̎擾
	VECTOR GetAttackPos(void);

	// �Փ˔���
	void CollisionStage(VECTOR pos);

	// �w��̕����Ƀm�b�N�o�b�N����
	void KnockBack(VECTOR dirXZ, float jumpPow);

private:
	// �ړ�����
	void ProcessMove(void);

	// �W�����v����
	void ProcessJump(void);

	// �U������
	void ProcessAttack(void);

	// �A�j���[�V�����Đ�
	void UpdateAnim(void);

	// ��ԑJ��
	void ChangeState(STATE state);

	// ��ԕʑJ��
	void ChangeMove(void);
	void ChangeKnockback(void);
	void ChangeAttack(void);
	void ChangeDead(void);
	void ChangeEnd(void);
	void ChangeVictory(void);

	// ��ԕʍX�V
	void UpdateMove(void);
	void UpdateKnockback(void);
	void UpdateAttack(void);
	void UpdateDead(void);
	void UpdateEnd(void);
	void UpdateVictory(void);

	// ��ԕʕ`��
	void DrawMove(void);
	void DrawKnockback(void);
	void DrawAttack(void);
	void DrawDead(void);
	void DrawEnd(void);
	void DrawVictory(void);

private:

	// ���
	STATE state_;
		
	int modelId_;	// ���f���̃n���h��ID
	VECTOR pos_;	// ���W
	VECTOR angle_;	// ����
	VECTOR scale_;	// �傫��
	float jumpPow_;	// �W�����v��
	bool isJump_;	// �W�����v����
	VECTOR moveDir_;// �ړ�����

	// �U�����W
	VECTOR attackPos_;

	// �m�b�N�o�b�N����
	VECTOR knockBackDir_;

	// �m�b�N�o�b�N�J�E���^(�_�ŗp)
	int knockBackCount_;

	// �A�j���[�V����
	ANIM_TYPE prevAnimType_;	// �O��̃A�j���[�V�������
	ANIM_TYPE nowAnimType_;		// ���݂̃A�j���[�V�������

	int attachNo_;				// �A�^�b�`No
	float nowAnimTime_;			// �Đ����̎���
	float totalAnimTime_;		// ���Đ�����
};
