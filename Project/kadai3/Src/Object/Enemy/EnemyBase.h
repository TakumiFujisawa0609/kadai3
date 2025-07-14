#pragma once
#include <DxLib.h>

// �N���X�̑O���錾
class Player;

class EnemyBase
{
public:
	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		WALK = 6,	// ����
	};

public:

	// �R���X�g���N�^
	EnemyBase(void);

	// �f�X�g���N�^
	~EnemyBase(void);

	// ��������
	void Init(Player* player);

	// �ǂݍ���
	void Load(void);

	// �ǂݍ��݌�
	void LoadEnd(void);

	// �X�V����
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �������
	void Release(void);

private:
	// �v���C���[�̕���������
	void LookPlayer(void);

	// �ړ�
	void Move(void);

	// �A�j���[�V�����Đ�
	void UpdateAnim(void);
private:
	// �v���C���[�̏��A�h���X
	Player* player_;

	// ���f���̃n���h��ID
	int modelId_;

	// ���W
	VECTOR pos_;
	// �p�x
	VECTOR angle_;
	// �傫��
	VECTOR scale_;
	// �ړ�����
	VECTOR moveDir_;
	// �ړ����x
	float speed_;

	// �A�j���[�V����
	ANIM_TYPE prevAnimType_;	// �O��̃A�j���[�V�������
	ANIM_TYPE nowAnimType_;		// ���݂̃A�j���[�V�������

	int attachNo_;				// �A�^�b�`No
	float nowAnimTime_;			// �Đ����̎���
	float totalAnimTime_;		// ���Đ�����

};


