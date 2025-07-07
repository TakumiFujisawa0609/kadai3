#pragma once
#include <DxLib.h>

class Player
{

public:

	// ���f���̑傫��
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	// �����ʒu
	static constexpr VECTOR INIT_POS = { 300.0f, 10.0f, 300.0f };
	// �W���̎��Ȕ����F
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 0.5f };

	// �ړ��X�s�[�h
	static constexpr float MOVE_SPEED = 10.0f;

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

private:
	// �ړ�����
	void ProcessMove(void);

private:
		
	int modelId_;	// ���f���̃n���h��ID
	VECTOR pos_;	// ���W
	VECTOR angle_;	// ����
	VECTOR scale_;	// �傫��
};
