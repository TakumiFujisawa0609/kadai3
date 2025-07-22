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
		DEAD = 0,	// ���S
		IDEL = 3,	// �ҋ@
		WALK = 14,	// ����
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

	// ���W�̎擾
	VECTOR GetPos(void);

	// �Փ˔���
	void CollisionStage(VECTOR pos);

private:
	// �ړ�����
	void ProcessMove(void);

	// �W�����v����
	void ProcessJump(void);

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

	// �A�j���[�V����
	ANIM_TYPE prevAnimType_;	// �O��̃A�j���[�V�������
	ANIM_TYPE nowAnimType_;		// ���݂̃A�j���[�V�������

	int attachNo_;				// �A�^�b�`No
	float nowAnimTime_;			// �Đ����̎���
	float totalAnimTime_;		// ���Đ�����
};
